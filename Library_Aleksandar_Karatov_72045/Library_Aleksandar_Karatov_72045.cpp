#include"Engine.h"
#include <iostream>
#include <fstream>
#include <limits>
#include "Engine.h"
#include "Vector.h"
#include "User.h"
#include <iostream>
#include "Book.h"
#include "String.h"
#include <fstream>
#include <ctime>
int main()
{
	Engine engine;
	engine.Run();

	/*User currentUser;
	Vector<User> vectorUsers;
	Vector<Book> vectorBooks;
	Vector<String> commandInStrings;
	vectorUsers.pushBack(User("Admin", "i<3c++", true));
	vectorUsers.pushBack(User("pepi", "123", false));
	vectorUsers.pushBack(User("pepi2", "123", false));
	vectorUsers.pushBack(User("pepi3", "123", false));

	Vector<String> keywords;
	keywords.pushBack("metro");
	keywords.pushBack("mutants");
	keywords.pushBack("radiation");
	keywords.pushBack("revenge");

	vectorBooks.pushBack(Book("Dmitrii Glukhovski", "Metro 2033",
		"Distopia", "A tale about a man, fighting for his home", 2014, keywords, 10, "12345"));

	keywords = Vector<String>();
	keywords.pushBack("superpowers");
	keywords.pushBack("fire");
	keywords.pushBack("revenge");

	vectorBooks.pushBack(Book("Stephen King", "Firestarter", "Triller",
		"A story about a father, protecting his child", 1980, keywords, 7, "23456"));


	std::ofstream output_file;
	output_file.open("Books.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	output_file << vectorBooks[0] << std::endl;
	output_file << vectorBooks[1];

	Book testBook;
	output_file.close();
	Vector<Book> TestVector;
	char* asr = new char[10000];
	std::ifstream input("Books.txt"); //open file
	while (input.getline(asr, 10000))
	{
		Book temp;
		temp.setFromFile(asr);
		TestVector.pushBack(temp);
	}
	input.close();
	for (size_t i = 0; i < TestVector.getSize(); i++)
	{
		std::cout << TestVector[i];
	}
	//std::cout << testBook;
	*/

	return 0;
}
