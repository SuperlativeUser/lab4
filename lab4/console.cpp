#pragma once
#include "console.h"
#include <vector>
Console::Console():creator(0) {};

void Console::onConsoleCall() {

	openFile();

	while (onConversationStart());
	
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
		showBooks(getByString());
		return true;

	case 2:
		showBooks(getByInteger());
		return true;
	case 3:
		deleteBook();
		return true;
	case 4:
		addBook();
		return true;
	case 5:
		showAllBooks();
		return true;
	default:
		std::cin.clear();
		std::cin.ignore();
		colorPrint("Try again...", 10);

		return true;
	}
}

void Console::openFile() {
	bool exitFlag = false;
	while (!exitFlag) {
		if (getData()) {
			exitFlag = true;
		}
		else {
			colorPrint("Try to fix file", 12);
			colorPrint("Do you want to continue? Y/N (Y by default)", 10);
			char answer;
			std::cin >> answer;
			answer = std::tolower(answer);
			switch (answer) {
			case 'n':
				exitFlag = true;
			default:
				break;
			}
		}
	}
}

bool Console::getData() {
	std::string filename;
	colorPrint("Enter a filename", 15);
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

std::vector<Book> Console::getByString() {
	
	colorPrint("Choose by which value we will search\n1. Name\n2. Surname\n3. Midlename\n4. Title", 14);
	int type;
	std::cin >> type;
	colorPrint("Enter value", 15);
	std::string value;
	std::cin >> value;
	books = creator->findByString(value, type);
	return books;
}

std::vector<Book> Console::getByInteger() {
	colorPrint("Choose by which value we will search\n1. Year\n2. Count", 14);
	int type;
	std::cin >> type;
	colorPrint("Enter integer value", 15);
	int value;
	std::cin >> value;
	books = creator->findByInt(value, type);
	return books;
}


void Console::deleteBook() {
	
	colorPrint("Let's find book. Find book by\n1.Author or title\n2.Year or count", 15);
	int answer;
	std::cin >> answer;

	std::vector<Book> books;
	switch (answer)
	{
	case 1:
		books = getByString();
		break;
	case 2:
		books = getByInteger();
		break;
	default:
		std::cout << "Unexpected value";
		break;
	}
	if (books.empty()) {
		showBooks(books);
	}
	else {
		showBooks(books, true);
		colorPrint("Enter number of book what you would like to delete", 12);
		int answer;
		std::cin >> answer;
		if (answer > 0 && answer < books.size()) {
			creator->deleteBook(books[answer - 1]);
			colorPrint("Ok. Book deleted", 14);
		}
		else {
			colorPrint("Book is not existed", 12);
		}

	}
}

void Console::showAllBooks() {
	std::vector<Book> books = creator->getAllBoks();
	if (books.empty()) {
		colorPrint("File is empty", 12);
	}
	else {
		showBooks(books);
	}
	
}

void Console::addBook() {
	Book book;
	colorPrint("Enter name:", 10);
	std::cin >> book.name;
	colorPrint("Enter surname:", 10);
	std::cin >> book.surname;
	colorPrint("Enter midlename:", 10);
	std::cin >> book.midlename;
	colorPrint("Enter title:", 10);
	std::cin >> book.title;

	colorPrint("Enter year:", 10);
	std::cin >> book.year;
	colorPrint("Enter count:", 10);
	std::cin >> book.count;

	creator->addBook(book);
	colorPrint("Book added", 14);
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

void Console::showBooks(const std::vector<Book> books) {
	if (books.empty()) {
		colorPrint("\nWe didn't find anything!", 12);
	}
	else {
		for (unsigned int i = 0; i < books.size(); i++) {
			printBook(books[i]);
		}
	}
	
}

void Console::showBooks(const std::vector<Book> books, const bool numbering) {
	if (books.empty()) {
		colorPrint("\nWe didn't find anything!", 12);
	}
	else {
		for (unsigned int i = 0; i < books.size(); i++) {
			std::cout << i + 1 << std::endl;
			printBook(books[i]);
		}
	}
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