#include "arithmetic.h"
#include <gtest.h>

TEST(ArithmeticTest, BasicAddition) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("2 + 3"), 5.0);
}

TEST(ArithmeticTest, BasicSubtraction) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("10 - 4"), 6.0);
}

TEST(ArithmeticTest, BasicMultiplication) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("3 * 4"), 12.0);
}

TEST(ArithmeticTest, BasicDivision) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("15 / 3"), 5.0);
}

TEST(ArithmeticTest, BasicPower) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("2 ^ 3"), 8.0);
}

TEST(ArithmeticTest, MultiplicationBeforeAddition) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("2 + 3 * 4"), 14.0);
}

TEST(ArithmeticTest, ParenthesesChangePrecedence) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("(2 + 3) * 4"), 20.0);
}

TEST(ArithmeticTest, UnaryMinus) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("-5"), -5.0);
}

TEST(ArithmeticTest, DivisionByZeroThrows) {
    ArithmeticCalculator calc;
    EXPECT_THROW(calc.calculate("5 / 0"), std::runtime_error);
}

TEST(ArithmeticTest, VariableAssignment) {
    ArithmeticCalculator calc;
    calc.setVariable("x", 10.0);
    EXPECT_DOUBLE_EQ(calc.calculate("x"), 10.0);
}

TEST(ArithmeticTest, VariableExpression) {
    ArithmeticCalculator calc;
    calc.setVariable("x", 5.0);
    calc.setVariable("y", 3.0);
    EXPECT_DOUBLE_EQ(calc.calculate("x + y"), 8.0);
}

TEST(ArithmeticTest, SinFunctionZero) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("sin(0)"), 0.0, 1e-10);
}

TEST(ArithmeticTest, CosFunctionZero) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("cos(0)"), 1.0, 1e-10);
}

TEST(ArithmeticTest, SqrtFunction) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("sqrt(4)"), 2.0, 1e-10);
}

TEST(ArithmeticTest, PiConstant) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("pi"), 3.141592653589793, 1e-10);
}

TEST(ArithmeticTest, EConstant) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("e"), 2.718281828459045, 1e-10);
}

TEST(ArithmeticTest, ComplexExpressionWithVariable) {
    ArithmeticCalculator calc;
    calc.setVariable("x", 2.0);
    EXPECT_NEAR(calc.calculate("sin(3.141592653589793/2) + x * 3"), 7.0, 1e-10);
}

TEST(ArithmeticTest, GreaterThanTrue) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 > 3"), 1.0);
}

TEST(ArithmeticTest, GreaterThanFalse) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("3 > 5"), 0.0);
}

TEST(ArithmeticTest, EqualTrue) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 == 5"), 1.0);
}

TEST(ArithmeticTest, EqualFalse) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 == 3"), 0.0);
}

TEST(ArithmeticTest, NotEqualTrue) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 != 3"), 1.0);
}

TEST(ArithmeticTest, NotEqualFalse) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 != 5"), 0.0);
}

TEST(ArithmeticTest, GreaterOrEqualTrue1) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 >= 5"), 1.0);
}

TEST(ArithmeticTest, GreaterOrEqualTrue2) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 >= 3"), 1.0);
}

TEST(ArithmeticTest, GreaterOrEqualFalse) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("3 >= 5"), 0.0);
}

TEST(ArithmeticTest, LessOrEqualTrue) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("3 <= 5"), 1.0);
}

TEST(ArithmeticTest, LessOrEqualFalse) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 <= 3"), 0.0);
}

TEST(ArithmeticTest, UndefinedVariableThrows) {
    ArithmeticCalculator calc;
    EXPECT_THROW(calc.calculate("undefined"), std::invalid_argument);
}

TEST(ArithmeticTest, RPNConversionSimple) {
    ArithmeticCalculator calc;
    std::vector<std::string> rpn = calc.toRPN("2 + 3 * 4");
    EXPECT_EQ(rpn.size(), 5);
}

TEST(ArithmeticTest, RPNCalculationSimple) {
    ArithmeticCalculator calc;
    std::vector<std::string> rpn = { "2", "3", "4", "*", "+" };
    EXPECT_DOUBLE_EQ(calc.calculateRPN(rpn), 14.0);
}

TEST(ArithmeticTest, ValidExpressionPasses) {
    ArithmeticCalculator calc;
    EXPECT_TRUE(calc.isValidExpression("2 + 3"));
}

TEST(ArithmeticTest, InvalidExpressionFails) {
    ArithmeticCalculator calc;
    EXPECT_FALSE(calc.isValidExpression("2 + "));
}

TEST(ArithmeticTest, FunctionRPNNotEmpty) {
    ArithmeticCalculator calc;
    std::vector<std::string> rpn = calc.toRPN("sin(0)");
    EXPECT_FALSE(rpn.empty());
}

TEST(ArithmeticTest, TanFunctionZero) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("tan(0)"), 0.0, 1e-10);
}

TEST(ArithmeticTest, AsinFunctionZero) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("asin(0)"), 0.0, 1e-10);
}

TEST(ArithmeticTest, LogFunctionE) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("log(2.718281828459045)"), 1.0, 1e-10);
}

TEST(ArithmeticTest, ExpFunctionZero) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("exp(0)"), 1.0, 1e-10);
}

TEST(ArithmeticTest, AbsFunctionNegative) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("abs(-5)"), 5.0, 1e-10);
}

TEST(ArithmeticTest, FloorFunction) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("floor(3.7)"), 3.0);
}

TEST(ArithmeticTest, CeilFunction) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("ceil(3.2)"), 4.0);
}

TEST(ArithmeticTest, RoundFunction) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("round(3.5)"), 4.0);
}

TEST(ArithmeticTest, AsinOutOfRangeThrows) {
    ArithmeticCalculator calc;
    EXPECT_THROW(calc.calculate("asin(2)"), std::invalid_argument);
}

TEST(ArithmeticTest, SqrtNegativeThrows) {
    ArithmeticCalculator calc;
    EXPECT_THROW(calc.calculate("sqrt(-1)"), std::invalid_argument);
}

TEST(ArithmeticTest, LogZeroThrows) {
    ArithmeticCalculator calc;
    EXPECT_THROW(calc.calculate("log(0)"), std::invalid_argument);
}

TEST(ArithmeticTest, VariableOverwrite) {
    ArithmeticCalculator calc;
    calc.setVariable("x", 10.0);
    calc.setVariable("x", 20.0);
    EXPECT_DOUBLE_EQ(calc.calculate("x"), 20.0);
}

TEST(ArithmeticTest, RPNForFunctionContainsSin) {
    ArithmeticCalculator calc;
    std::vector<std::string> rpn = calc.toRPN("sin(pi/2)");
    bool containsSin = false;
    for (const auto& token : rpn) {
        if (token == "sin") containsSin = true;
    }
    EXPECT_TRUE(containsSin);
}

TEST(ArithmeticTest, RPNForUnaryMinusContainsTilde) {
    ArithmeticCalculator calc;
    std::vector<std::string> rpn = calc.toRPN("-5");
    bool containsTilde = false;
    for (const auto& token : rpn) {
        if (token == "~") containsTilde = true;
    }
    EXPECT_TRUE(containsTilde);
}

TEST(ArithmeticTest, CalculateRPNForFunction) {
    ArithmeticCalculator calc;
    std::vector<std::string> rpn = { "0", "sin" };
    EXPECT_NEAR(calc.calculateRPN(rpn), 0.0, 1e-10);
}

TEST(ArithmeticTest, InvalidRPNThrows) {
    ArithmeticCalculator calc;
    std::vector<std::string> rpn = { "2", "+" };
    EXPECT_THROW(calc.calculateRPN(rpn), std::invalid_argument);
}

TEST(ArithmeticTest, EmptyRPNThrows) {
    ArithmeticCalculator calc;
    std::vector<std::string> rpn;
    EXPECT_THROW(calc.calculateRPN(rpn), std::invalid_argument);
}

TEST(ArithmeticTest, UnclosedStringFailsValidation) {
    ArithmeticCalculator calc;
    EXPECT_FALSE(calc.isValidExpression("\"unclosed"));
}

TEST(ArithmeticTest, NestedFunctionsWork) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("sin(cos(0))"), 0.8414709848, 1e-10);
}

TEST(ArithmeticTest, ComplexTrigonometricExpression) {
    ArithmeticCalculator calc;
    EXPECT_NEAR(calc.calculate("sin(3.141592653589793/2) + cos(0)"), 2.0, 1e-10);
}

TEST(ArithmeticTest, ExpressionWithVariablesAndFunctions) {
    ArithmeticCalculator calc;
    calc.setVariable("x", 4.0);
    EXPECT_NEAR(calc.calculate("sqrt(x) * 2"), 4.0, 1e-10);
}

TEST(ArithmeticTest, LessThanTrue) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("3 < 5"), 1.0);
}

TEST(ArithmeticTest, LessThanFalse) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("5 < 3"), 0.0);
}

TEST(ArithmeticTest, CalculateWithInvalidExpressionThrowsWithPosition) {
    ArithmeticCalculator calc;

    try {
        calc.calculate("(2 + 3");
        FAIL() << "Expected ParseException";
    }
    catch (const ParseException& e) {
        EXPECT_NE(std::string(e.what()).find("position"), std::string::npos);
    }

    try {
        calc.calculate("2 + * 3");
        FAIL() << "Expected ParseException";
    }
    catch (const ParseException& e) {
        EXPECT_NE(std::string(e.what()).find("position"), std::string::npos);
    }
}

TEST(ArithmeticTest, SimpleExpressionNoSpaces) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("1+1"), 2.0);
}

TEST(ArithmeticTest, SimpleExpressionWithSpaces) {
    ArithmeticCalculator calc;
    EXPECT_DOUBLE_EQ(calc.calculate("1 + 1"), 2.0);
}