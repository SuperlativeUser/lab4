#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "book.h"
class MapCreator {
public:
	MapCreator(const std::string filename);
	bool readData();

	std::vector<Book> findByString(const std::string value);
	std::vector<Book> findByInt(const int value);

private:
	std::string filename;
	std::vector<Book> books;
	
	std::map < std::string, std::set <int >> stringKeyMap;
	std::map<int, std::set<int>> intKeyMap;
	
	void readFile();
};