#pragma once
#include "console.h"
#include <vector>
Console::Console():creator(0) {};

void Console::onConsoleCall() {
	colorPrint("Hello, I'm your assistant. Let's start? Type Y/N", 3);
	char answer;
	std::cin >> answer;
	answer = tolower(answer);

	if (answer == 'y') {
		if (getData()) {
			while (onConversationStart());
		}
		else {
			colorPrint("Try to fix file", 12);
		}
		
	}
	colorPrint("See you!", 13);
}

bool Console::onConversationStart() {
	std::cout << std::endl << "-----------------------------" << std::endl;

	std::cout << "What do you want?" << std::endl;
	
	for (int i = 0; i < _COMMANDS_LENGS; i++) {
		if (i == _COMMANDS_LENGS - 1) {
			std::cout << "0. " << strings[i] << std::endl;
		}
		else {
			std::cout << i + 1 << ". " << strings[i] << std::endl;
		}
	}
	std::cout << std::endl << "-----------------------------" << std::endl;
	int answer{0};

	std::cin >> answer;
	
	switch (answer) {
	case 0:
		return false;

	case 1:
		getByString();
		return true;

	case 2:
		getByInteger();
		return true;
	case 3: 
		if (updateBooks()) {
			colorPrint("Data refreshed", 10);
		}
		return true;
	default:
		std::cin.clear();
		std::cin.ignore();
		colorPrint("Try again...", 10);
		
		return true;
	}



}
bool Console::getData() {
	std::string filename;
	colorPrint("Remember: file shoud have *.txt format", 13);
	colorPrint("Enter filename without '.txt'", 10);
	std::cin >> filename;
	filename = filename + ".txt";
	creator = new MapCreator(filename);
	if (creator->readData()) {
		return true;
	}
	return false;
}

void Console::setColor(const int text) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | text));
}

void Console::getByString() {
	colorPrint("Enter name or surname or midlename or title", 15);
	std::string value;
	std::cin >> value;
	books = creator->findByString(value);
	for (unsigned int i = 0; i < books.size(); i++) {
		printBook(books[i]);
	}
	
}

void Console::getByInteger() {
	colorPrint("Enter search year or count", 15);
	int value;
	std::cin >> value;
	books = creator->findByInt(value);
	for (unsigned int i = 0; i < books.size(); i++) {
		printBook(books[i]);
	}
}

bool Console::updateBooks() {
	if (creator->readData()) {
		colorPrint("Data update!", 14);
		return true;
	}
	return false;
}

void Console::printBook(const Book book) {
	colorPrint("Name: ", 3, false);
	std::cout << book.name << " " << book.surname << " " << book.midlename << std::endl;
	colorPrint("Title: ", 3, false);
	std::cout << book.title << std::endl;
	colorPrint("Year: ", 3, false);
	std::cout << book.year << std::endl;
	colorPrint("Count: ", 3, false);
	std::cout << book.count << std::endl << std::endl;
	
}

template <typename T>
void Console::colorPrint(const T word, const int color) {
	setColor(color);
	std::cout << word << std::endl;
	setColor(15);
}

template <typename T>
void Console::colorPrint(const T word, const int color, const bool endl) {
	if (endl) {
		setColor(color);
		std::cout << word << std::endl;
		setColor(15);
	} else {
		setColor(color);
		std::cout << word;
		setColor(15);
	}
}
Console::~Console() {
	delete creator;
}