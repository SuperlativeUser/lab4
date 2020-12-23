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

std::vector<Book> MapCreator::findByString(const std::string value, const int type) {
	std::vector<Book> result;
	switch (type)
	{
	case 1:
		if (nameKeyMap.find(value) != nameKeyMap.end()) {
			std::set<int> indexes = nameKeyMap[value];

			for (int it : indexes) {
				result.push_back(books[it]);
			}

			return result;
		}
		break;
	case 2:
		if (surnameKeyMap.find(value) != surnameKeyMap.end()) {
			std::set<int> indexes = surnameKeyMap[value];

			for (int it : indexes) {
				result.push_back(books[it]);
			}

			return result;
		}
		break;
	case 3:
		if (midlenameKeyMap.find(value) != midlenameKeyMap.end()) {
			std::set<int> indexes = midlenameKeyMap[value];

			for (int it : indexes) {
				result.push_back(books[it]);
			}

			return result;
		}
		break;
	case 4:
		if (titleKeyMap.find(value) != titleKeyMap.end()) {
			std::set<int> indexes = titleKeyMap[value];

			for (int it : indexes) {
				result.push_back(books[it]);
			}

			return result;
		}
		break;
	default:
		break;
	}

	return result;
}
std::vector<Book> MapCreator::findByInt(const int value, const int type) {
	std::vector<Book> result;
	
	switch (type)
	{
	case 1:
		if (yearKeyMap.find(value) != yearKeyMap.end()) {
			std::set<int> indexes = yearKeyMap[value];
			for (int it : indexes) {
				result.push_back(books[it]);
			}

			return result;
		}
		break;
	case 2:
		if (countKeyMap.find(value) != countKeyMap.end()) {
			std::set<int> indexes = countKeyMap[value];
			for (int it : indexes) {
				result.push_back(books[it]);
			}

			return result;
		}
	default:
		break;
	}
	return result;
}

std::vector<Book> MapCreator::getAllBoks() {
	return books;
}

void MapCreator::readFile() {
	std::ifstream fin(filename);
	Book booker;
	
	while (fin >> booker.name >> booker.surname >> booker.midlename >> booker.title >> booker.year >> booker.count) {
		books.push_back(booker);
	}

	fin.close();

	updateData();
}

void MapCreator::rewriteFile() {
	std::ofstream fout;
	fout.open(filename, std::ofstream::out | std::ofstream::trunc);
	
	for (auto& v : books) {
		fout << v.name << " " << v.surname << " " << v.midlename << " " << v.title << " " << v.year << " " << v.count << std::endl;
	}

	fout.close();
}

void MapCreator::deleteBook(const Book &book) {

	auto i = books.begin();
	for (i = books.begin(); i != books.end(); i++) {
		if (book.name == i->name && book.surname == i->surname && book.midlename == i->midlename &&
			book.title == i->title && book.year == i->year && book.count == i->count) {
			break;
		}
	}

	books.erase(i);
}

void MapCreator::addBook(const Book& book) {
	books.push_back(book);

	updateData();
}

void MapCreator::updateData() {
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
		nameKeyMap.insert(std::pair<std::string, std::set<int>>(v.name, nameSet));
		surnameKeyMap.insert(std::pair<std::string, std::set<int>>(v.surname, surnameSet));
		midlenameKeyMap.insert(std::pair<std::string, std::set<int>>(v.midlename, midlenameSet));
		titleKeyMap.insert(std::pair<std::string, std::set<int>>(v.title, titleSet));

		yearKeyMap.insert(std::pair<int, std::set<int>>(v.year, yearSet));
		countKeyMap.insert(std::pair<int, std::set<int>>(v.count, countSet));
	}
}

MapCreator::~MapCreator() {
	rewriteFile();
}