#include "Engine.h"
#include "Vector.h"
#include "User.h"
#include <iostream>
#include "Book.h"
#include "String.h"
bool validateString(const char*);
void Engine::Run()
{
	User currentUser;
	Vector<User> vectorUsers;
	Vector<Book> vectorBooks;
	vectorUsers.pushBack(User("Admin", "123", true));
	vectorUsers.pushBack(User("pepi", "i<3c++", false));
	vectorUsers.pushBack(User("pepi2", "i<3c++", false));
	vectorUsers.pushBack(User("pepi3", "i<3c++", false));

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
	while (strcmp(command,"exit") != 0)
	{
		//users add
		if (strcmp(command, "users add") == 0 && currentUser.get_auth() == true)
		{
			User temp;
			std::cout << "Enter username (special symbols allowed: ! _ - . @ $ % & * < > +):";
			std::cin.getline(command, 30);
			bool isStrValid = validateString(command);
			while (!isStrValid)
			{
				std::cout << "Enter a valid username (special symbols allowed: ! _ - . @ $ % & * < > +):";
				std::cin.getline(command, 30);
				isStrValid = validateString(command);
			}
			temp.set_username(command);
			std::cout << "Enter password (special symbols allowed: ! _ - . @ $ % & * < > +):";
			std::cin.getline(command, 30);
			isStrValid = validateString(command);
			while (!isStrValid)
			{
				std::cout << "Enter a valid password (special symbols allowed: ! _ - . @ $ % & * < > +):";
				std::cin.getline(command, 30);
				isStrValid = validateString(command);
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
		//show users
		else if (strcmp(command, "show users") == 0 && currentUser.get_auth() == true)
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
					break;
				}
			}
			if (currentUser.get_username() == nullptr)
			{
				std::cout << "Incorrect login details!" << std::endl;
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

bool validateString(const char* str)
{
	for (size_t i = 0; i < strlen(str); i++)
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '!' && str[i] != '_' && str[i] !='-' && str[i] != '.' && (str[i] < '@' 
			|| str[i]> 'Z') && str[i] != '$' && str[i] != '%' && str[i] != '&' && str[i] != '*' && (str[i] < 'a' || str[i] > 'z')
			&& str[i] != '<' && str[i] != '>' && str[i] != '+')
		{
			return false;
		}
	}
	return true;
}