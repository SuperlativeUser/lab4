#pragma once
#include "mapcreator.h"
#include <vector>

MapCreator::MapCreator(const std::string filename) {
	this->filename = filename;
}
bool MapCreator::readData() {
	try {
		readFile();
		return true;
	}
	catch (std::ifstream::failure e) {
		std::cerr << "Error reading file" << std::endl;
	}
	return false;
}

std::vector<Book> MapCreator::findByString(const std::string value) {
	std::vector<Book> result;
	std::set<int> indexes = stringKeyMap[value];

	for (int it : indexes) {
		result.push_back(books[it]);
	}

	return result;
}
std::vector<Book> MapCreator::findByInt(const int value) {
	std::vector<Book> result;
	std::set<int> indexes = intKeyMap[value];

	for (int it : indexes) {
		result.push_back(books[it]);
	}

	return result;
}


void MapCreator::readFile() {
	std::ifstream fin(filename);
	Book booker;
	
	while (fin >> booker.name >> booker.surname >> booker.midlename >> booker.title >> booker.year >> booker.count) {
		books.push_back(booker);
	}
	
	for (auto& v : books) {
		std::set<int> nameSet;
		std::set<int> surnameSet;
		std::set<int> midlenameSet;
		std::set<int> titleSet;

		std::set<int> yearSet;
		std::set<int> countSet;

		for (unsigned int i = 0; i < books.size(); i++) {
			if (books[i].name == v.name) {
				nameSet.insert(i);
			}

			if (books[i].surname == v.surname) {
				surnameSet.insert(i);
			}

			if (books[i].midlename == v.midlename) {
				midlenameSet.insert(i);
			}

			if (books[i].title == v.title) {
				titleSet.insert(i);
			}

			if (books[i].year == v.year) {
				yearSet.insert(i);
			}
			if (books[i].count == v.count) {
				countSet.insert(i);
			}
		}
		stringKeyMap.insert(std::pair<std::string, std::set<int>>(v.name, nameSet));
		stringKeyMap.insert(std::pair<std::string, std::set<int>>(v.surname, surnameSet));
		stringKeyMap.insert(std::pair<std::string, std::set<int>>(v.midlename, midlenameSet));
		stringKeyMap.insert(std::pair<std::string, std::set<int>>(v.title, titleSet));

		intKeyMap.insert(std::pair<int, std::set<int>>(v.year, yearSet));
		intKeyMap.insert(std::pair<int, std::set<int>>(v.count, countSet));
	}
	
	fin.close();
}
