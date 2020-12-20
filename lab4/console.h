#pragma once
#define _COMMANDS_LENGS 4
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
	std::string strings[_COMMANDS_LENGS] = { "Get all by author or title", "Get all book from year or count", "Refresh data" ,"Exit" };

	bool onConversationStart();

	void setColor(const int text);

	bool getData();

	void getByString();

	void getByInteger();

	bool updateBooks();

	void printBook(const Book book);

	template <typename T>
	void colorPrint(const T word, const int color);

	template <typename T>
	void colorPrint(const T word, const int color, const bool endl);
};