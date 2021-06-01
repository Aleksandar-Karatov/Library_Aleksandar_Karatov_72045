#pragma once
#include <conio.h>
#include "Vector.h"
#include "User.h"
#include <iostream>
#include "Book.h"
#include "String.h"
#include <fstream>
#include <ctime>
class Engine
{
	private:
		User currentUser;
		Vector<User> vectorUsers;
		Vector<Book> vectorBooks;
		Vector<String> commandInStrings;
		String fileNameBooks;
		String fileNameUsers;
		void save(const bool);
		void saveAs(const String, const bool);
		void open(const String, const bool);
		void close(const bool);
		bool checkIfISBNIsTaken(const char*);
		char* trimEmptySpaces(char*);
		Vector<String> splitCommand(char*);
		void sortBooks(const String, const bool);
		bool compareStrings( const char* str1, const char* str2);
public:

	void Run();
};

