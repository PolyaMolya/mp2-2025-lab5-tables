#pragma once

#include <vector>
#include <string>
#include <utility>
#include "Polinom.h"

class UnsortTable {
private:
	std::vector<std::pair<std::string, Polinom>> data;

public:
	UnsortTable();
	~UnsortTable();
	int insert(const std::string& key, const Polinom& pol);
	const Polinom* find(const std::string& key, int& comparisons) const;
	bool remove(const std::string& key, Polinom& removedPol, int& comparisons);
	void print() const;
};