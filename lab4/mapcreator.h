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

	std::vector<Book> findByString(const std::string value,  const int type);
	std::vector<Book> findByInt(const int value, const int type);
	std::vector<Book> getAllBoks();
	void deleteBook(const Book &book);
	void addBook(const Book& book);


	~MapCreator();

private:
	std::string filename;
	std::vector<Book> books;
	
	std::map < std::string, std::set <int >> nameKeyMap;
	std::map < std::string, std::set <int >> surnameKeyMap;
	std::map < std::string, std::set <int >> midlenameKeyMap;
	std::map < std::string, std::set <int >> titleKeyMap;
	std::map<int, std::set<int>> yearKeyMap;
	std::map<int, std::set<int>> countKeyMap;
	
	void readFile();

	void rewriteFile();

	void updateData();
};