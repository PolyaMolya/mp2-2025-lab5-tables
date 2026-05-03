#pragma once

#include <vector>
#include "Polinom.h"
#include <list>
#include <string>

class Hash {
private:
	static const size_t size = 101;
	std::vector<std::list<std::pair<::std::string, Polinom>>> buck;
	size_t hash(const std::string& key) const;
public:
	Hash();
	int insert(const std::string& key, const Polinom& pol);
	const Polinom* find(const std::string& key, int& comprisons) const;
	bool remove(const std::string& key, Polinom& remPol, int& comprisons);
	void print() const;
};
