#include "Table_array.h"
#include <iostream>

UnsortTable::UnsortTable(){}
UnsortTable::~UnsortTable() {}

int UnsortTable::insert(const std::string& key, const Polinom& pol) {
	data.push_back({ key,pol });
	return 1;
}

const Polinom* UnsortTable::find(const std::string& key, int& comparisons) const{
	comparisons = 0;
	for (const auto item : data) {
		++comparisons;
		if (item.first == key) {
			return &item.second;
		}
	}
	return nullptr;
}

bool UnsortTable::remove(const std::string& key, Polinom& removedPol, int& comparisons) {
	comparisons = 0;
	for (auto it = data.begin(); it != data.end(); ++it) {
		++comparisons;
		if (it->first == key) {
			removedPol = it->second;
			int sh = static_cast<int>(data.end() - it - 1);
			data.erase(it);
			comparisons += sh;
			return true;
		}
	}
	return false;
}

void UnsortTable::print() const {
	std::cout << "Unsorted Table:\n";
	for (const auto& item : data) {
		std::cout << " " << item.first << " = ";
		item.second.print();
		std::cout << "\n";
	}
}