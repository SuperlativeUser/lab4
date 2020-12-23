#pragma once

#include <iostream>
#include <Windows.h>
#include "mapcreator.h"
#include "book.h"

class Console {
public:
	Console();
	void onConsoleCall();
	~Console();
private:
	std::vector<Book> books;
	MapCreator* creator;
	static const int _COMMANDS_LENGS = 6;
	std::string strings[_COMMANDS_LENGS] = { "Get all by author or title", "Get all book from year or count",  "Delete book", "Add Book", "Show all books", "Exit" };

	bool onConversationStart();

	void setColor(const int text);
	
	void openFile();

	bool getData();

	std::vector<Book> getByString();

	std::vector<Book> getByInteger();

	void deleteBook();

	void addBook();

	void showAllBooks();

	void printBook(const Book book);

	void showBooks(const std::vector<Book> books);

	void showBooks(const std::vector<Book> books, const bool numbering);

	template <typename T>
	void colorPrint(const T word, const int color);

	template <typename T>
	void colorPrint(const T word, const int color, const bool endl);
};