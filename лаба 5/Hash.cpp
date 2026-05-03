#include "Hash.h"
#include <iostream>
#include <functional>

Hash::Hash() :buck(size) {}

size_t Hash::hash(const std::string& key) const {
	return std::hash<std::string>{}(key) % size;
}

int Hash::insert(const std::string& key, const Polinom& pol) {
	size_t idx = hash(key);
	auto& buc = buck[idx];
	int comparisons = 0;
	for (auto& pair : buc) {
		++comparisons;
		if (pair.first == key) {
			pair.second = pol;
			return comparisons;
		}
	}

	buc.push_front({ key,pol });
	return comparisons;
}

const Polinom* Hash::find(const std::string& key, int& comparisons) const {
	size_t idx = hash(key);
	const auto& buc = buck[idx];
	comparisons = 0;

	for (const auto& pair : buc) {
		++comparisons;
		if (pair.first == key)
			return &pair.second;	
	}
	return nullptr;
}

bool Hash::remove(const std::string& key, Polinom& remPol, int& comparisons) {
	size_t idx = hash(key);
	auto& buc = buck[idx];
	comparisons = 0;
	for (auto it = buc.begin(); it != buc.end(); ++it) {
		++comparisons;
		if (it->first == key) {
			remPol = it->second;
			buc.erase(it);
			return true;
		}
	}
	return false;
}

void Hash::print() const {
	std::cout << "HashTable (std::hash, size = " << size << "):\n";
	for (size_t i = 0; i < buck.size(); ++i) {
		if (!buck[i].empty()) {
			std::cout << "  bucket " << i << ":\n";
			for (const auto& pair : buck[i]) {
				std::cout << "    " << pair.first << " = ";
				pair.second.print();  
				std::cout << "\n";
			}
		}
	}
}