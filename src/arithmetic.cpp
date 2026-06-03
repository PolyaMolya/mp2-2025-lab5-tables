// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include "stack.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

ArithmeticCalculator::ArithmeticCalculator() {
	variables["pi"] = 3.14159265358979323846;
	variables["e"] = 2.71828182845904523536;
}

ArithmeticCalculator::~ArithmeticCalculator() {
	variables.clear();
}

bool ArithmeticCalculator::isValidExpression(const std::string& expression, size_t* errorPos) const {
	if (errorPos) *errorPos = 0;
	return checkExpression(expression, errorPos);
}

bool ArithmeticCalculator::checkExpression(const std::string& expression, size_t* errorPos) const {
	if (expression.empty()) {
		if (errorPos) *errorPos = 0;
		return false;
	}

	int balance = 0;
	bool lastWasOperator = true;
	bool lastWasOperand = false;
	size_t currentPos = 0;

	for (size_t i = 0; i < expression.length(); ++i) {
		char c = expression[i];

		if (isspace(c)) {
			currentPos++;
			continue;
		}
		
		if (i + 1 < expression.length()) {
			string twoCharOp = expression.substr(i, 2);
			if (twoCharOp == "==" || twoCharOp == "!=" ||
				twoCharOp == "<=" || twoCharOp == ">=") {
				if (lastWasOperator) {
					if (errorPos) *errorPos = currentPos;
					return false;
				}
				lastWasOperator = true;
				lastWasOperand = false;
				i++;
				currentPos++;
				continue;
			}
		}

		if (c == '(') {
			balance++;
			lastWasOperator = true;
			lastWasOperand = false;
		}
		else if (c == ')') {
			if (balance <= 0) {
				if (errorPos) *errorPos = currentPos;
				return false;
			}
			balance--;
			lastWasOperator = false;
			lastWasOperand = true;
		}
		else if (isOperator(string(1, c))) {
			if (lastWasOperator && c != '-' && c != '+') {
				if (errorPos) *errorPos = currentPos;
				return false;
			}
			lastWasOperator = true;
			lastWasOperand = false;
		}
		else if (isdigit(c) || c == '.' || isalpha(c) || c == '_') {
			lastWasOperator = false;
			lastWasOperand = true;

			if (isdigit(c) || c == '.') {
				bool hasDot = (c == '.');
				while (i + 1 < expression.length() &&
					(isdigit(expression[i + 1]) || expression[i + 1] == '.')) {
					i++;
					currentPos++;
					if (expression[i] == '.') {
						if (hasDot) {
							if (errorPos) *errorPos = currentPos;
							return false;
						}
						hasDot = true;
					}
				}
			}
			else if (isalpha(c) || c == '_') {
				while (i + 1 < expression.length() &&
					(isalnum(expression[i + 1]) || expression[i + 1] == '_')) {
					i++;
					currentPos++;
				}
			}
		}
		else {
			if (errorPos) *errorPos = currentPos;
			return false;
		}

		currentPos++;
	}

	if (balance != 0) {
		if (errorPos) *errorPos = expression.length() - 1;
		return false;
	}

	if (lastWasOperator) {
		if (errorPos) *errorPos = expression.length() - 1;
		return false;
	}

	return true;
}

std::vector<std::string>ArithmeticCalculator::tokenize(const string& expression) const {
	vector<string> tokens;

	for (size_t i = 0; i < expression.length(); ++i) {
		char c = expression[i];

		if (isspace(c)) continue;

		if (i + 1 < expression.length()) {
			string twoCharOp = expression.substr(i, 2);
			if (twoCharOp == "<=" || twoCharOp == ">=" || twoCharOp == "==" || twoCharOp == "!=") {
				tokens.push_back(twoCharOp);
				i++;
				continue;
			}
		}

		if (isOperator(string(1, c)) || c == '(' || c == ')' || c == ',') {
			tokens.push_back(string(1, c));
			continue;
		}

		if (isdigit(c) || c == '.' || isalpha(c) || c == '_') {
			string token;
			token += c;
			i++;
			while (i < expression.length()) {
				char next = expression[i];
				if (isalnum(next) || next == '_' || next == '.') {
					token += next;
					i++;
				}
				else {
					break;
				}
			}
			i--;
			tokens.push_back(token);
		}
	}
	return tokens;
}

bool ArithmeticCalculator::isUnaryMinus(const vector<string>& tokens, size_t index) const {
	if (tokens[index] != "-") return false;
	if (index == 0) return true;
	string prev = tokens[index - 1];
	return prev == "(" || isOperator(prev) || isFunction(prev);
}

vector<string> ArithmeticCalculator::toRPN(const std::string& expression) const {
	vector<string> tokens = tokenize(expression);
	vector<string> output;
	Stack<string> operators;

	for (size_t i = 0; i < tokens.size(); ++i) {
		const string& token = tokens[i];

		if (isNumber(token) || isVariable(token))
			output.push_back(token);
		else if (isFunction(token))
			operators.push(token);
		else if (token == ",")
			while (!operators.isEmpty() && operators.peek() != "(")
				output.push_back(operators.pop());
		else if (token == "(")
			operators.push(token);
		else if (token == ")") {
			while (!operators.isEmpty() && operators.peek() != "(")
				output.push_back(operators.pop());
			if (!operators.isEmpty() && operators.peek() == "(")
				operators.pop();
			if (!operators.isEmpty() && isFunction(operators.peek()))
				output.push_back(operators.pop());
		}
		else if (isOperator(token)) {
			if (token == "-" && isUnaryMinus(tokens, i))
				operators.push("~");
			else {
				while (!operators.isEmpty() && operators.peek() != "(" &&
					getPriority(operators.peek()) >= getPriority(token))
					output.push_back(operators.pop());
				operators.push(token);
			}
		}
	}
	while (!operators.isEmpty())
		output.push_back(operators.pop());
	
	return output;
}

double ArithmeticCalculator::calculate(const string& expression) {
	size_t errorPos = 0;
	if (!checkExpression(expression, &errorPos))
		throw ParseException("Invalid expression", errorPos);
	vector<string> rpn = toRPN(expression);
	return calculateRPN(rpn);
}

double ArithmeticCalculator::calculateRPN(const vector<string>& rpn) {
	Stack<double> values;

	for (const string& token : rpn) {
		if (isNumber(token))
			values.push(stod(token));
		else if (isVariable(token)) {
			auto it = variables.find(token);
			if (it != variables.end())
				values.push(it->second);
			else
				throw std::invalid_argument("Undefined variable: " + token);
		}
		else if (isFunction(token)) {
			if (values.isEmpty())
				throw std::invalid_argument("Invalid RPN expression");
			double arg = values.pop();
			values.push(applyFunction(token, arg));
		}
		else if (token == "~") {
			if (values.isEmpty())
				throw std::invalid_argument("Invalid RPN expression");
			double a = values.pop();
			values.push(-a);
		}
		else if (isOperator(token)) {
			if (values.size() < 2)
				throw std::invalid_argument("Invalid RPN expression");
			double b = values.pop();
			double a = values.pop();
			values.push(applyOperator(a, b, token));
		}
	}
	if (values.size() != 1)
		throw std::invalid_argument("Invalid RPN expression");

	return values.pop();
}

double ArithmeticCalculator::applyOperator(double a, double b, const string& op) const {
	if (op == "+") return a + b;
	else if (op == "-") return a - b;
	else if (op == "*") return a * b;
	else if (op == "/") {
		if (b == 0) throw runtime_error("Division by zero");
		return a / b;
	}
	else if (op == "^") return pow(a, b);
	else if (op == "<") return a < b ? 1.0 : 0.0;
	else if (op == ">") return a > b ? 1.0 : 0.0;
	else if (op == "<=") return a <= b ? 1.0 : 0.0;
	else if (op == ">=") return a >= b ? 1.0 : 0.0;
	else if (op == "==") return a == b ? 1.0 : 0.0;
	else if (op == "!=") return a != b ? 1.0 : 0.0;

	throw invalid_argument("Unknown operator: " + op);
}

double ArithmeticCalculator::applyFunction(const string& func, double arg) const {
	if (func == "sin") return sin(arg);
	else if (func == "cos") return cos(arg);
	else if (func == "tan") return tan(arg);
	else if (func == "asin") {
		if (arg < -1.0 || arg > 1.0) throw invalid_argument("asin argument out of range [-1, 1]");
		return asin(arg);
	}
	else if (func == "acos") {
		if (arg < -1.0 || arg > 1.0) throw invalid_argument("acos argument out of range [-1, 1]");
		return acos(arg);
	}
	else if (func == "atan") return atan(arg);
	else if (func == "sqrt") {
		if (arg < 0) throw invalid_argument("sqrt of negative number");
		return sqrt(arg);
	}
	else if (func == "log") {
		if (arg <= 0) throw invalid_argument("log of non-positive number");
		return log(arg);
	}
	else if (func == "log10") {
		if (arg <= 0) throw invalid_argument("log10 of non-positive number");
		return log10(arg);
	}
	else if (func == "exp") return exp(arg);
	else if (func == "abs") return abs(arg);
	else if (func == "floor") return floor(arg);
	else if (func == "ceil") return ceil(arg);
	else if (func == "round") return round(arg);

	throw invalid_argument("Unknown function: " + func);
}

void ArithmeticCalculator::setVariable(const string& name, double value) {
	variables[name] = value;
}

double ArithmeticCalculator::getVariable(const string& name) const {
	auto it = variables.find(name);
	if (it != variables.end())
		return it->second;
	throw std::invalid_argument("Variable not foud: " + name);
}

bool ArithmeticCalculator::isNumber(const string& str) {
	if (str.empty()) return false;
	istringstream iss(str);
	double value;
	iss >> value;
	return !iss.fail() && iss.eof();
}

bool ArithmeticCalculator::isOperator(const string& str) {
	if (str.length() == 1) {
		char c = str[0];
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '<' || c == '>' || c == '=';
	}
	else if (str.length() == 2) {
		return str == "<=" || str == ">=" || str == "==" || str == "!=";
	}
	return false;
}

bool ArithmeticCalculator::isFunction(const string& str) {
	return str == "sin" || str == "cos" || str == "tan" ||
		str == "asin" || str == "acos" || str == "atan" ||
		str == "sqrt" || str == "log" || str == "log10" ||
		str == "exp" || str == "abs" || str == "floor" ||
		str == "ceil" || str == "round";
}

bool ArithmeticCalculator::isVariable(const string& str) {
	if (str.empty()) return false;
	if (isNumber(str)) return false;
	if (isFunction(str)) return false;

	if (!isalpha(str[0]) && str[0] != '_') return false;

	for (char c : str) {
		if (!isalnum(c) && c != '_') return false;
	}

	return true;
}

int ArithmeticCalculator::getPriority(const string& op) {
	if (op == "~") return 4;

	if (op == "^") return 3;
	if (op == "*" || op == "/") return 2;
	if (op == "+" || op == "-") return 1;
	if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "==" || op == "!=") return 0;

	return -1;
}