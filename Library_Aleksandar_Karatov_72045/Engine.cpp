#include "Engine.h"
#include "Vector.h"
#include "User.h"
#include <iostream>
#include "Book.h"
#include "String.h"
bool validatePassAndUsername(const char*);
void Engine::Run()
{
	User currentUser;
	Vector<User> vectorUsers;
	Vector<Book> vectorBooks;
	vectorUsers.pushBack(User("Admin", "i<3c++", true));
	vectorUsers.pushBack(User("pepi", "123", false));
	vectorUsers.pushBack(User("pepi2", "123", false));
	vectorUsers.pushBack(User("pepi3", "123", false));

	Vector<String> keywords;
	keywords.pushBack("metro");
	keywords.pushBack("mutants");
	keywords.pushBack("radiation");
	vectorBooks.pushBack(Book("Dmitrii Glukhovski", "Metro 2033", "Distopia", "A tale about a man, fighting for his home", 2014, keywords, 10, "12345"));
	keywords = Vector<String>();
	keywords.pushBack("superpowers");
	keywords.pushBack("fire");
	keywords.pushBack("revenge");
	vectorBooks.pushBack(Book("Stephen King", "Firestarter","Triller", "A story about a father, protecting his child", 1980, keywords,7,"23456" ));
	char* command = new char[30];
	std::cout << "Enter command:";
	std::cin.getline(command, 30);
	int incorrectLogins = 0;
	while (strcmp(command,"exit") != 0)
	{
		//users add
		if (strcmp(command, "users add") == 0 && currentUser.get_auth() == true)
		{
			User temp;
			std::cout << "Enter username (special symbols allowed: ! _ - . @ $ % & * < > +):";
			std::cin.getline(command, 30);
			bool isStrValid = validatePassAndUsername(command);
			while (!isStrValid)
			{
				std::cout << "Enter a valid username (special symbols allowed: ! _ - . @ $ % & * < > +):";
				std::cin.getline(command, 30);
				isStrValid = validatePassAndUsername(command);
			}
			temp.set_username(command);
			std::cout << "Enter password (special symbols allowed: ! _ - . @ $ % & * < > +):";
			std::cin.getline(command, 30);
			isStrValid = validatePassAndUsername(command);
			while (!isStrValid)
			{
				std::cout << "Enter a valid password (special symbols allowed: ! _ - . @ $ % & * < > +):";
				std::cin.getline(command, 30);
				isStrValid = validatePassAndUsername(command);
			}
			temp.set_password(command);
			std::cout << "Enter authorization: admin or user: ";
			std::cin.getline(command, 30);
			while (strcmp(command, "admin") != 0 && strcmp(command, "user") != 0 && strcmp(command, "") != 0)
			{
				std::cout << "Enter a valid authorization value: admin or user: ";
				std::cin.getline(command, 30);
			}
			if (strcmp(command, "admin") == 0)
			{
				temp.set_auth(true);
			}
			else
			{
				temp.set_auth(false);
			}
			std::cout << temp.get_username() << " | " << temp.get_auth() << std::endl << "Save changes? [y/n]";
			std::cin.getline(command, 30);
			if (strcmp(command, "y") == 0 || strcmp(command, "Y") == 0 || strcmp(command, "yes") == 0)
			{
				vectorUsers.pushBack(temp);
			}
			temp.~User();
		}
		else if (strcmp(command, "users add") == 0 && currentUser.get_auth() == false)
		{
			std::cout << "You are unauthorized to create users!" << std::endl;
		}


		//users remove
		else if (strcmp(command, "users remove") == 0 && currentUser.get_auth() == true)
		{
			std::cout << "Enter username of the user you want to delete:";
			std::cin.getline(command,30);
			size_t size = vectorUsers.getSize();
			for (size_t i = 0; i < size; i++)
			{
				if (strcmp(vectorUsers[i].get_username(), command) == 0)
				{
					std::cout << "Are you sure you want to delete " << command << "? [y/n]: ";
					std::cin.getline(command, 30);
					if (strcmp(command, "y") == 0 || strcmp(command, "Y") == 0 || strcmp(command, "yes") == 0)
					{
						vectorUsers.deleteAtIndex(i);
						vectorUsers[vectorUsers.getSize()].~User();
						std::cout << "You have succesfully deleted the user!" << std::endl;
					}
					break;
				}
			}
			if (size == vectorUsers.getSize())
			{
				std::cout << "User could not be found!";
			}
			
		}
		else if (strcmp(command, "users remove") == 0 && currentUser.get_auth() == false)
		{
			std::cout << "You are unauthorized to remove users!" << std::endl;
		}


		//users all
		else if (strcmp(command, "users all") == 0 && currentUser.get_auth() == true)
		{
			for (size_t i = 0; i < vectorUsers.getSize(); i++)
			{
				std::cout << vectorUsers[i].get_username() << " | " << vectorUsers[i].get_password() << " | ";
				if (vectorUsers[i].get_auth()==true)
				{
					std::cout << "admin" << std::endl;
				}
				else
				{
					std::cout << "user" << std::endl;
				}
			}
		}
		else if (strcmp(command, "show users") == 0 && currentUser.get_auth() == false)
		{
			std::cout << "You are unauthorized to view users!" << std::endl;
		}


		//login
		else if (strcmp(command, "login") == 0 && currentUser.get_username()==nullptr)
		{
			char* temp = new char[30];
			std::cout << "Enter username:";
			std::cin.getline(command, 30);
			std::cout << "Enter password:";
			std::cin.getline(temp, 30);

			for (size_t i = 0; i < vectorUsers.getSize(); i++)
			{
				if (strcmp(command,vectorUsers[i].get_username())==0 && strcmp(temp, vectorUsers[i].get_password())==0)
				{
					currentUser = vectorUsers[i];
					std::cout << "Welcome, " << currentUser.get_username() << "!" << std::endl;
					incorrectLogins = 0;
					break;
				}
			}
			if (currentUser.get_username() == nullptr)
			{
				incorrectLogins++;
				std::cout << "Incorrect login details!" << std::endl;
			}
			if (incorrectLogins > 2)
			{
				std::cout << "Three incorrect logins! Exiting..." << std::endl;;
				break;
			}
		}
		else if (strcmp(command, "login") == 0 && currentUser.get_username() != nullptr)
		{
			std::cout << "You are currently logged in!" << std::endl;
		}


		//logout
		else if (strcmp(command, "logout") == 0 && currentUser.get_username() != nullptr)
		{
			currentUser.~User();
			//currentUser = User();
			std::cout << "You have logged out!" << std::endl;
		}
		else if (strcmp(command, "logout") == 0 && currentUser.get_username() == nullptr)
		{
			std::cout << "Action impossible! You are not logged in" << std::endl;
		}


		//books all
		else if (strcmp(command, "books all") == 0 && currentUser.get_username() != nullptr)
		{
			for (size_t i = 0; i < vectorBooks.getSize(); i++)
			{
				std::cout << vectorBooks[i] << std::endl;;
			}
		}
		else if (strcmp(command, "books all") == 0 && currentUser.get_username() == nullptr)
		{
			std::cout << "You need to login to see the books in the library!" << std::endl;
		}


		//books info <isbn>
		else if (strcmp(command, "books info") == 0 && currentUser.get_username() != nullptr)
		{
			std::cout << "Enter ISBN: ";
			std::cin.getline(command,30);
			bool isFound = false;
			for (size_t i = 0; i < vectorBooks.getSize(); i++)
			{
				if (strcmp(command, vectorBooks[i].get_isbn()) == 0)
				{
					std::cout << vectorBooks[i];
					isFound = true;
					break;
				}
			}
			if (!isFound)
			{
				std::cout << "There isn`t a book with such ISBN!" << std::endl;
			}
		}
		else if (strcmp(command, "books info") == 0 && currentUser.get_username() == nullptr)
		{
			std::cout << "You need to login to see the books in the library!" << std::endl;
		}


		//books find
		if (strcmp(command, "books find") == 0 && currentUser.get_username() != nullptr)
		{
			std::cout << "Enter option [title, author, tag]: ";
			std::cin.getline(command, 30);
			bool isFound = false;
			if (strcmp(command, "title") == 0)
			{
				std::cout << "Enter title: ";
				std::cin.getline(command, 30);
				for (size_t i = 0; i < vectorBooks.getSize(); i++)
				{
					if (strcmp(command, vectorBooks[i].get_title()) == 0)
					{
						std::cout << vectorBooks[i];
						isFound = true;
						break;
					}
				}
			}
			else if (strcmp(command, "author") == 0)
			{
				std::cout << "Enter author: ";
				std::cin.getline(command, 30);
				for (size_t i = 0; i < vectorBooks.getSize(); i++)
				{
					if (strcmp(command, vectorBooks[i].get_author()) == 0)
					{
						std::cout << vectorBooks[i] << std::endl;;
						isFound = true;
					}
				}
			}
			else if (strcmp(command, "tag") == 0)
			{
				std::cout << "Enter tag: ";
				std::cin.getline(command, 30);
				String tag = command;
				for (size_t i = 0; i < vectorBooks.getSize(); i++)
				{
					for (size_t j = 0; j < vectorBooks[i].get_keywords().getSize(); j++)
					{
						if (tag == vectorBooks[i].get_keywords()[j])
						{
							std::cout << vectorBooks[i] << std::endl;
							isFound = true;
						}
					}
				}
			}
			if (!isFound)
			{
				std::cout << "There isn`t a book with such parameters!" << std::endl;
			}
		}
		else if (strcmp(command, "books find") == 0 && currentUser.get_username() == nullptr)
		{
			std::cout << "You need to login to see the books in the library!" << std::endl;
		}


		// books add
		if (strcmp(command, "books add") == 0 && currentUser.get_auth() == true)
		{
			Book temp;
			std::cout << "Enter title:";
			std::cin.getline(command, 30);
			temp.set_title(command);
			std::cout << "Enter author:";
			std::cin.getline(command, 30);
			temp.set_author(command);
			std::cout << "Enter genre:";
			std::cin.getline(command, 30);
			temp.set_genre(command);
			std::cout << "Enter description:";
			char* description = new char[100];
			std::cin.getline(description, 100);
			temp.set_description(description);
			delete[] description;
			description = nullptr;
			std::cout << "Enter ISBN:";
			std::cin.getline(command, 30);
			temp.set_isbn(command);
			double rating;
			std::cout << "Enter rating:";
			std::cin >> rating;
			temp.set_rating(rating);
			int yearofPublish;
			std::cout << "Enter year of publishing:";
			std::cin >> yearofPublish;
			temp.set_yearOfPublishing(yearofPublish);
			std::cout << "Enter keywords (reads until empty line):";
			std::cin.sync();
			std::cin.ignore();
			std::cin.getline(command,30);
			Vector<String> tempTags;
			for (size_t i = 0; strcmp(command, "") != 0; i++)
			{
				tempTags.pushBack(command);
				std::cin.getline(command, 30);
			}
			temp.set_keywords(tempTags);
			std::cout << "Save changes [y/n]: ";
			std::cin.getline(command, 30);
			if ((strcmp(command,"y")==0) || (strcmp(command, "Y") == 0) || (strcmp(command, "yes") == 0))
			{
				vectorBooks.pushBack(temp);
			}
		}
		else if (strcmp(command, "books add") == 0 && currentUser.get_auth() == false)
		{
			std::cout << "You are unauthorized to add books!" << std::endl;
		}


		//books remove
		else if (strcmp(command, "books remove") == 0 && currentUser.get_auth() == true)
		{
			std::cout << "Enter the title of the book you want to delete:";
			std::cin.getline(command, 30);
			size_t size = vectorBooks.getSize();
			for (size_t i = 0; i < size; i++)
			{
				if (strcmp(vectorBooks[i].get_title(), command) == 0)
				{
					std::cout << "Are you sure you want to delete " << command << "? [y/n]: ";
					std::cin.getline(command, 30);
					if (strcmp(command, "y") == 0 || strcmp(command, "Y") == 0 || strcmp(command, "yes") == 0)
					{
						vectorBooks.deleteAtIndex(i);
						vectorBooks[vectorBooks.getSize()].~Book();
						std::cout << "You have succesfully deleted the book!" << std::endl;
					}
					break;
				}
			}
			if (size == vectorBooks.getSize())
			{
				std::cout << "Book could not be found!";
			}

		}
		else if (strcmp(command, "books remove") == 0 && currentUser.get_auth() == false)
		{
			std::cout << "You are unauthorized to remove books!" << std::endl;
		}


		std::cout << "Enter new command:";
		std::cin.getline(command, 30);
	}
	std::cout << "Exiting.... Have a great day!";
	delete[] command;
}

bool validatePassAndUsername(const char* str)
{
	int specialCnt = 0;
	int capitalCnt = 0;
	int numberCnt = 0;
	int smallLetterCnt = 0;
	if (strlen(str) < 8)
	{
		std::cout << "Input shorter than 8 symbols" << std::endl;
		return false;
	}
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			numberCnt++;
		}
		else if (str[i] == '!' || str[i] == '_' || str[i] == '-' || str[i] == '.' ||
				 str[i] == '@' || str[i] == '$' || str[i] == '%' || str[i] == '&' || 
				 str[i] == '*' || str[i] == '<' || str[i] == '>' || str[i] == '+')
		{
			specialCnt++;
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			smallLetterCnt++;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			capitalCnt++;
		}
		else
		{
			std::cout << "Invalid symbol : " << str[i] << std::endl;
			return false;
		}
	}
	if (numberCnt == 0 || capitalCnt == 0 || smallLetterCnt == 0 || specialCnt == 0)
	{
		std::cout << "Input has to contain at least one capital letter, one small letter, one special symbol and one number!" << std::endl;
		return false;
	}
	return true;
}

