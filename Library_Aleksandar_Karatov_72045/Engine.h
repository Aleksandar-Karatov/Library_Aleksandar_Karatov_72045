#pragma once

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
		bool validatePassAndUsername(const char*);
		char* trimEmptySpaces(char*);
		Vector<String> splitCommand(char*);
public:

	void Run();
};

