#include "Engine.h"

void Engine::Run() // used as a core for functionality
{
	char* command = new char[100];
	std::cout << "Enter command:";
	std::cin.getline(command, 100);
	command = trimEmptySpaces(command);
	commandInStrings = splitCommand(command);
	int incorrectLogins = 0;
	
	while (commandInStrings[0].toLower() != "exit") // main menu
	{
		//users
		if (commandInStrings[0].toLower() == "users" && commandInStrings.getSize() > 1)
		{
			//users add
			if (commandInStrings[1].toLower() == "add" && currentUser.get_auth() == true && commandInStrings.getSize() == 2)
			{
				User temp;
				std::cout << "Enter username (special symbols allowed: ! _ - . @ $ % & * < > +):";
				std::cin.getline(command, 30);
				temp.set_username(command);
				while (temp.get_username() == nullptr)
				{
					std::cout << "Enter a valid username (special symbols allowed: ! _ - . @ $ % & * < > +):";
					std::cin.getline(command, 30);
					temp.set_username(command);
				}
				temp.set_username(command);
				std::cout << "Enter password (special symbols allowed: ! _ - . @ $ % & * < > +):";
				String pass = new char[20];
				char ch;
				
				ch = getch();
				int lenPass = 0;
				for (; ch != 13; lenPass++)
				{
					pass[lenPass] = ch;
					std::cout << '*';
					ch = getch();
				}
				std::cin.sync();
				pass[lenPass] = '\0';
				temp.set_password(pass.get_str());
				pass.~String();
				pass = new char[20];
				while (temp.get_password()==nullptr)
				{
					std::cout << std::endl << "Enter a valid password (special symbols allowed: ! _ - . @ $ % & * < > +):";
					ch = getch();
					lenPass = 0;
					for (; ch != 13; lenPass++)
					{
						pass[lenPass] = ch;
						std::cout << '*';
						ch = getch();
					}
					std::cin.sync();
					pass[lenPass] = '\0';
					temp.set_password(pass.get_str());
					pass.~String();
					pass = new char[20];
				}
				std::cin.sync();
				std::cout << std::endl << "Enter authorization: admin or user: ";
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
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
				command = trimEmptySpaces(command);
				if (strcmp(command, "y") == 0 || strcmp(command, "Y") == 0)
				{
					vectorUsers.pushBack(temp);
				}
				else if (strcmp(command, "n") == 0 || strcmp(command, "N") == 0)
				{
					std::cout << "Operation cancelled!" << std::endl;
				}
				else
				{
					std::cout << "Invalid input! Operation is cancelled!" << std::endl;
				}
				temp.~User();
			}
			else if (commandInStrings[1].toLower() == "add" && commandInStrings.getSize() != 2)
			{
				std::cout << "Invalid input!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "add" && currentUser.get_auth() == false)
			{
				std::cout << "You are unauthorized to create users!" << std::endl;
			}
			


			//users remove
			else if (commandInStrings[1].toLower() == "remove" && currentUser.get_auth() == true && commandInStrings.getSize() == 3)
			{
				std::cout << "Enter username of the user you want to delete:";
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
				size_t size = vectorUsers.getSize();
				for (size_t i = 0; i < size; i++)
				{
					if (strcmp(vectorUsers[i].get_username(), command) == 0)
					{
						std::cout << "Are you sure you want to delete " << command << "? [y/n]: ";
						std::cin.getline(command, 30);
						command = trimEmptySpaces(command);
						if (strcmp(command, "y") == 0 || strcmp(command, "Y") == 0)
						{
							vectorUsers.deleteAtIndex(i);
							vectorUsers[vectorUsers.getSize()].~User();
							std::cout << "You have succesfully deleted the user!" << std::endl;
						}
						else if (strcmp(command, "n") == 0 || strcmp(command, "N") == 0)
						{
							std::cout << "Operation cancelled!" << std::endl;
						}
						else
						{
							std::cout << "Invalid input! Operation is cancelled!" << std::endl;
						}
						break;
					}
				}
				if (size == vectorUsers.getSize())
				{
					std::cout << "User could not be found!";
				}

			}
			else if (commandInStrings[1].toLower() == "remove" && commandInStrings.getSize() != 3)
			{
				std::cout << "Invalid input!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "remove" && currentUser.get_auth() == false)
			{
				std::cout << "You are unauthorized to remove users!" << std::endl;
			}
			


			//users all
			else if (commandInStrings[1].toLower() == "all" && currentUser.get_auth() == true && commandInStrings.getSize() == 2)
			{
				for (size_t i = 0; i < vectorUsers.getSize(); i++)
				{
					std::cout << vectorUsers[i].get_username() << " | " << vectorUsers[i].get_password() << " | ";
					if (vectorUsers[i].get_auth() == true)
					{
						std::cout << "admin" << std::endl;
					}
					else
					{
						std::cout << "user" << std::endl;
					}
				}
			}
			else if (commandInStrings[1].toLower() == "all" && commandInStrings.getSize() != 2)
			{
				std::cout << "Invalid input!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "all" && currentUser.get_auth() == false)
			{
				std::cout << "You are unauthorized to view users!" << std::endl;
			}
		}

		


		//login
		else if (commandInStrings[0].toLower() == "login" && currentUser.get_username()==nullptr && commandInStrings.getSize() == 1)
		{
			char* temp = new char[30];
			std::cout << "Enter username:";
			std::cin.getline(command, 30);
			std::cout << "Enter password:";
			String pass = new char[20];
			char ch;

			ch = getch();
			size_t i = 0;
			for (; ch != 13; i++)
			{
				pass[i] = ch;
				std::cout << '*';
				ch = getch();
			}
			pass[i] = '\0';
			std::cin.sync();
			for (size_t i = 0; i < vectorUsers.getSize(); i++)
			{
				if (strcmp(command,vectorUsers[i].get_username())==0 && strcmp(pass.get_str(), vectorUsers[i].get_password())==0)
				{
					currentUser = vectorUsers[i];
					std::cout << std::endl << "Welcome, " << currentUser.get_username() << "!" << std::endl;
					incorrectLogins = 0;
					break;
				}
			}
			if (currentUser.get_username() == nullptr)
			{
				incorrectLogins++;
				std::cout << std::endl <<"Incorrect login details!" << std::endl;
			}
			if (incorrectLogins > 2)
			{
				std::cout << std::endl << "Three incorrect logins! Exiting..." << std::endl;;
				break;
			}
		}
		else if (commandInStrings[0].toLower() == "login" && commandInStrings.getSize() != 1)
		{
			std::cout << "Invalid command!" << std::endl;
		}
		else if (commandInStrings[0].toLower() == "login" && currentUser.get_username() != nullptr)
		{
			std::cout << "You are currently logged in!" << std::endl;
		}


		//logout
		else if (commandInStrings[0].toLower() == "logout" && currentUser.get_username() != nullptr && commandInStrings.getSize() == 1)
		{
			currentUser.~User();
			std::cout << "You have logged out!" << std::endl;
		}
		else if (commandInStrings[0].toLower() == "logout" && commandInStrings.getSize() != 1)
		{
			std::cout << std::endl << "Invalid command!" << std::endl;
		}
		else if (commandInStrings[0].toLower() == "logout" && currentUser.get_username() == nullptr)
		{
			std::cout << "Action impossible! You are not logged in" << std::endl;
		}


		//books
		else if (commandInStrings[0].toLower() == "books" && commandInStrings.getSize() > 1)
		{
			//books all
			if (commandInStrings[1].toLower() == "all" && currentUser.get_username() != nullptr && commandInStrings.getSize() == 2)
			{
				std::cout << std::endl;
				for (size_t i = 0; i < vectorBooks.getSize(); i++)
				{
					std::cout << vectorBooks[i] << std::endl;;
				}
			}
			else if (commandInStrings[1].toLower() == "all" && currentUser.get_username() == nullptr)
			{
				std::cout << "You need to login to see the books in the library!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "all"  && commandInStrings.getSize() != 2)
			{
				std::cout << "Invalid input!" << std::endl;
			}

			//books info <isbn>
			else if (commandInStrings[1].toLower() == "info" && currentUser.get_username() != nullptr && commandInStrings.getSize() == 3)
			{
				bool isFound = false;
				for (size_t i = 0; i < vectorBooks.getSize(); i++)
				{
					if (commandInStrings[2] == vectorBooks[i].get_isbn())
					{
						std::cout << std::endl << "Title: " << vectorBooks[i].get_title() << std::endl <<
									"Author: " << vectorBooks[i].get_author() << std::endl <<
									"Genre: "  << vectorBooks[i].get_genre()  << std::endl <<
									"Rating: " << vectorBooks[i].get_rating() << "/10" << std::endl << std::endl;
						isFound = true;
						break;
					}
				}
				if (!isFound)
				{
					std::cout << "There isn`t a book with such ISBN!" << std::endl;
				}
			}
			else if (commandInStrings[1].toLower() == "info" && commandInStrings.getSize() != 3)
			{
				std::cout << "Invalid input!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "info" &&  currentUser.get_username() == nullptr)
			{
				std::cout << "You need to login to see the books in the library!" << std::endl;
			}
			
			//books find
			else if (commandInStrings[1].toLower() == "find" && currentUser.get_username() != nullptr && commandInStrings.getSize() >= 4)
			{
				bool isFound = false;
				
				if (commandInStrings[2].toLower() == "title")
				{
					String title = commandInStrings[3];
					for (size_t i = 4; i < commandInStrings.getSize(); i++)
					{
						title = title + " " + commandInStrings[i];
					}
					for (size_t i = 0; i < vectorBooks.getSize(); i++)
					{
						String temp = vectorBooks[i].get_title();
						if (title.toLower() == temp.toLower())
						{
							std::cout << vectorBooks[i];
							isFound = true;
							break;
						}
					}
				}
				else if (commandInStrings[2].toLower() == "author")
				{
					String author = commandInStrings[3];
					for (size_t i = 4; i < commandInStrings.getSize(); i++)
					{
						author = author + " " + commandInStrings[i];
					}
					for (size_t i = 0; i < vectorBooks.getSize(); i++)
					{
						String temp = vectorBooks[i].get_author();
						if (author.toLower() == temp.toLower())
						{
							std::cout << vectorBooks[i] << std::endl;
							isFound = true;
						}
					}
				}
				else if (commandInStrings[2].toLower() == "tag")
				{
					String tag = commandInStrings[3];
					for (size_t i = 4; i < commandInStrings.getSize(); i++)
					{
						tag = tag + " " + commandInStrings[i];
					}
					for (size_t i = 0; i < vectorBooks.getSize(); i++)
					{
						for (size_t j = 0; j < vectorBooks[i].get_keywords().getSize(); j++)
						{
							String temp = vectorBooks[i].get_keywords()[j];

							if (tag.toLower() == temp.toLower())
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
			else if (commandInStrings[1].toLower() == "find" && commandInStrings.getSize() < 4)
			{
				std::cout << "Invalid command!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "find" && currentUser.get_username() == nullptr)
			{
				std::cout << "You need to login to see the books in the library!" << std::endl;
			}



			// books add
			if (commandInStrings[1].toLower() == "add" && currentUser.get_auth() == true && commandInStrings.getSize() == 2)
			{
				Book temp;
				std::cout << "Enter title:";
				std::cin.getline(command, 100);
				command = trimEmptySpaces(command);
				temp.set_title(command);
				while (temp.get_title() == nullptr)
				{
					std::cout << "Enter a valid title (up to 30 symbols):";
					std::cin.getline(command, 100);
					command = trimEmptySpaces(command);
					temp.set_title(command);
				}

				std::cout << "Enter author:";
				std::cin.getline(command, 100);
				command = trimEmptySpaces(command);
				temp.set_author(command);
				while (temp.get_author() == nullptr)
				{
					std::cout << "Enter a valid name (up to 30 symbols):";
					std::cin.getline(command, 100);
					command = trimEmptySpaces(command);
					temp.set_author(command);
				}

				std::cout << "Enter genre:";
				std::cin.getline(command, 100);
				command = trimEmptySpaces(command);
				temp.set_genre(command);
				while (temp.get_genre() == nullptr)
				{
					std::cout << "Enter a valid genre (up to 20 symbols):";
					std::cin.getline(command, 100);
					command = trimEmptySpaces(command);
					temp.set_genre(command);
				}

				std::cout << "Enter description:";
				char* description = new char[200];
				std::cin.getline(description, 200);
				command = trimEmptySpaces(description);
				temp.set_description(description);
				while (temp.get_description() == nullptr)
				{
					std::cout << "Enter a valid description (up to 100 symbols):";
					std::cin.getline(command, 200);
					command = trimEmptySpaces(command);
					temp.set_description(command);
				}

				delete[] description;
				description = nullptr;
				std::cout << "Enter ISBN:";
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
				while (temp.get_isbn() == nullptr || checkIfISBNIsTaken(command))
				{
					
					if (temp.get_isbn() == nullptr)
					{
						std::cout << "Enter a valid ISBN (exactly 13 numbers, no letters, no spaces):";
						std::cin.getline(command, 30);
						command = trimEmptySpaces(command);
					}
					while (checkIfISBNIsTaken(command))
					{
						std::cout << "ISBN is taken! Chose another: ";
						std::cin.getline(command, 30);
						command = trimEmptySpaces(command);
					}
					temp.set_isbn(command);

				}

				double rating;
				std::cout << "Enter rating:";
				std::cin >> rating;
				temp.set_rating(rating);
				while (temp.get_rating() == NULL)
				{
					std::cout << "Enter a rating between 0 and 10:";
					std::cin >> rating;
					temp.set_rating(rating);
				}
				
				int yearofPublish;
				std::cout << "Enter year of publishing:";
				std::cin >> yearofPublish;
				temp.set_yearOfPublishing(yearofPublish);
				time_t t = time(NULL);
				tm* timePtr = localtime(&t);
				while (temp.get_yearOfPublishing() == NULL)
				{
					std::cout << "Enter a valid year of publishing (before or equal to " << timePtr->tm_year + 1900 << "): ";
					std::cin >> yearofPublish;
					temp.set_yearOfPublishing(yearofPublish);
				}
				std::cout << "Enter keywords (reads until empty line):";
				std::cin.sync();
				std::cin.ignore();
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
				Vector<String> tempTags;
				for (size_t i = 0; strcmp(command, "") != 0; i++)
				{
					tempTags.pushBack(command);
					std::cin.getline(command, 30);
					command = trimEmptySpaces(command);
				}
				temp.set_keywords(tempTags);
				std::cout << "Save changes [y/n]: ";
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
				if ((strcmp(command, "y") == 0) || (strcmp(command, "Y") == 0) || (strcmp(command, "yes") == 0))
				{
					vectorBooks.pushBack(temp);
				}
				else if (strcmp(command, "n") == 0 || strcmp(command, "N") == 0)
				{
					std::cout << "Operation cancelled!" << std::endl;
				}
				else
				{
					std::cout << "Invalid input! Operation is cancelled!" << std::endl;
				}
			}
			else if (commandInStrings[1].toLower() == "add" && commandInStrings.getSize() != 2)
			{
				std::cout << "Invalid input!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "add" && currentUser.get_auth() == false)
			{
				std::cout << "You are unauthorized to add books!" << std::endl;
			}
			

			//books remove
			else if (commandInStrings[1].toLower() == "remove" && currentUser.get_auth() == true && commandInStrings.getSize() >=3)
			{
				String title = commandInStrings[2];
				for (size_t i = 3; i < commandInStrings.getSize(); i++)
				{
					title = title + " " + commandInStrings[i];
				}
				size_t size = vectorBooks.getSize();
				for (size_t i = 0; i < size; i++)
				{
					if (title == vectorBooks[i].get_title())
					{
						std::cout << "Are you sure you want to delete " << command << "? [y/n]: ";
						std::cin.getline(command, 30);
						command = trimEmptySpaces(command);
						if (strcmp(command, "y") == 0 || strcmp(command, "Y") == 0 || strcmp(command, "yes") == 0)
						{
							vectorBooks.deleteAtIndex(i);
							vectorBooks[vectorBooks.getSize()].~Book();
							std::cout << "You have succesfully deleted the book!" << std::endl;
						}
						else if (strcmp(command, "n") == 0 || strcmp(command, "N") == 0)
						{
							std::cout << "Operation cancelled!" << std::endl;
						}
						else
						{
							std::cout << "Invalid input! Operation is cancelled!" << std::endl;
						}
						break;
					}
				}
				if (size == vectorBooks.getSize())
				{
					std::cout << "Book could not be found!" << std::endl;
				}

			}
			else if (commandInStrings[1].toLower() == "remove" && commandInStrings.getSize() < 3)
			{
				std::cout << "Invalid command!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "remove" && currentUser.get_auth() == false )
			{
				std::cout << "You are unauthorized to remove books!" << std::endl;
			}


		}
		// file commands
		//open
		else if (commandInStrings[0].toLower() == "open" && commandInStrings.getSize() == 3 )
		{
			if (commandInStrings[1].toLower() == "books" && fileNameBooks.isEmpty())
			{
				open(commandInStrings[2], true);
			}
			else if ((commandInStrings[1].toLower() == "books" && !fileNameBooks.isEmpty()) ||
			(commandInStrings[1].toLower() == "users" && !fileNameUsers.isEmpty()))
			{
				std::cout << "File already openned!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "users" && fileNameUsers.isEmpty())
			{
				open(commandInStrings[2], false);
			}
			else
			{
				std::cout << "Invalid command! Try using 'help'!" << std::endl;
			}
		}
		else if (commandInStrings[0].toLower() == "open" && commandInStrings.getSize() != 3)
		{
			std::cout << "Invalid command! Try using 'help'!" << std::endl;
		}
		//save
		else if (commandInStrings[0].toLower() == "save" && commandInStrings.getSize() == 2)
		{
			if (commandInStrings[1].toLower() == "books" && !fileNameBooks.isEmpty())
			{
				save(true);
			}
			else if (commandInStrings[1].toLower() == "users" && !fileNameUsers.isEmpty())
			{
				save(false);
			}
			else if ((commandInStrings[1].toLower() == "books" && fileNameBooks.isEmpty()) ||
				(commandInStrings[1].toLower() == "users" && fileNameUsers.isEmpty()))
			{
				std::cout << "File is not loaded!" << std::endl;
			}
			else
			{
				std::cout << "Invalid command! Try using 'help'!" << std::endl;
			}
		}
		else if (commandInStrings[0].toLower() == "save" && commandInStrings.getSize() != 2)
		{
			std::cout << "Invalid command! Try using 'help'!" << std::endl;
		}
		//save as
		else if (commandInStrings[0].toLower() == "saveas" && commandInStrings.getSize() == 3)
		{
			if (commandInStrings[1].toLower() == "books")
			{
				saveAs(commandInStrings[2],true);
			}
			else if (commandInStrings[1].toLower() == "users" )
			{
				saveAs(commandInStrings[2], false);
			}
			else
			{
				std::cout << "Invalid command! Try using 'help'!" << std::endl;
			}
		}
		else if (commandInStrings[0].toLower() == "saveas" && commandInStrings.getSize() != 3)
		{
			std::cout << "Invalid command! Try using 'help'!" << std::endl;
		}

		//close
		else if (commandInStrings[0].toLower() == "close" && commandInStrings.getSize() == 2 )
		{
			if (commandInStrings[1].toLower() == "books" && !fileNameBooks.isEmpty())
			{
				close(true);
			}
			else if(commandInStrings[1].toLower() == "users" && !fileNameUsers.isEmpty())
			{
				close(false);
			}
			else
			{
				std::cout << "Invalid command! Try using 'help'!" << std::endl;
			}

		}
		else if (commandInStrings[0].toLower() == "close" && commandInStrings.getSize() != 2)
		{
			std::cout << "Invalid command! Try using 'help'!" << std::endl;
		}
		
		else if (commandInStrings[0].toLower() == "help"  && commandInStrings.getSize() ==1)
		{
			std::cout << "The following commands are supported:" << std::endl <<
				"open <file>	opens <file>" << std::endl <<
				"close			closes currently opened file" << std::endl <<
				"save			saves the currently open file" << std::endl <<
				"saveas <file>	saves the currently open file in <file>" << std::endl <<
				"help			prints this information" << std::endl <<
				"exit			exists the program" << std::endl;
		}
		else if (commandInStrings[0].toLower() == "help" && commandInStrings.getSize() != 1)
		{
			std::cout << "Invalid command! Try using 'help'!" << std::endl;
		}
		//sort title, author, year, rating
		else if (commandInStrings[0].toLower() == "sort" && commandInStrings.getSize()>=2 && currentUser.get_username() != nullptr)
		{
			if ((commandInStrings.getSize() == 2) || (commandInStrings.getSize() == 3 && commandInStrings[2].toLower() == "asc"))
			{
				sortBooks(commandInStrings[1].toLower(), true);
			}
			else if (commandInStrings.getSize() == 3 && commandInStrings[2].toLower() == "desc")
			{
				sortBooks(commandInStrings[1].toLower(), false);
			}
		}
		else if (commandInStrings[0].toLower() == "sort" && currentUser.get_username() == nullptr)
		{
			std::cout << "You have to be logged in to use this function!" << std::endl;
		}
		else if (commandInStrings[0].toLower() == "sort" && (commandInStrings.getSize() >= 3 || commandInStrings.getSize() < 2))
		{
			std::cout << "Invalid input!" << std::endl;
		}
		else
		{
			std::cout << "Invalid input!" << std::endl;
		}
		std::cout << "Enter new command:";
		std::cin.getline(command, 100);
		command = trimEmptySpaces(command);
		commandInStrings = splitCommand(command);
	}
	std::cout << "Exiting.... Have a great day!";
	delete[] command;
}

//true for Books false for Users
void Engine:: save(const bool isBooksOrUsers)
{
	std::ofstream output_file;

	if (isBooksOrUsers)
	{
		output_file.open(fileNameBooks.get_str(), std::ofstream::out | std::ofstream::trunc);
		for (size_t i = 0; i < vectorBooks.getSize(); i++)
		{
			output_file << vectorBooks[i] << std::endl;
		}
	}
	else
	{
		output_file.open(fileNameUsers.get_str(), std::ofstream::out | std::ofstream::trunc);
		for (size_t i = 0; i < vectorUsers.getSize(); i++)
		{
			output_file << vectorUsers[i] << std::endl;
		}

	}
	output_file.close();
	std::cout << "File is now saved!" << std::endl;

}
void Engine::saveAs(const String nameOfFile, const bool isBooksOrUsers)
{
	std::ofstream output_file;

	output_file.open(nameOfFile.get_str(), std::ofstream::out | std::ofstream::trunc);
	if (isBooksOrUsers)
	{
		for (size_t i = 0; i < vectorBooks.getSize(); i++)
		{
			output_file << vectorBooks[i] << std::endl;
		}
		fileNameBooks = nameOfFile;
	}
	else
	{
		for (size_t i = 0; i < vectorUsers.getSize(); i++)
		{
			output_file << vectorUsers[i] << std::endl;
		}
		fileNameUsers = nameOfFile;
	}
	
	std::cout << "File \""<< nameOfFile << "\" is now saved!" << std::endl;
	output_file.close();
}
void Engine::open(const String nameOfFile, const bool isBooksOrUsers)
{
	char* buffer = new char[10000];
	std::ifstream input(nameOfFile.get_str());
	if (isBooksOrUsers)
	{
		while (input.getline(buffer, 10000))
		{
			Book temp;
			temp.setFromFile(buffer);
			vectorBooks.pushBack(temp);
		}
		fileNameBooks = nameOfFile;
	}
	else
	{
		while (input.getline(buffer, 10000))
		{
			User temp;
			temp.setFromFile(buffer);
			bool isInVector = false;
			for (size_t i = 0; i < vectorUsers.getSize(); i++)
			{
				if (temp == vectorUsers[i])
				{
					isInVector = true;
					break;
				}
			}
			if (!isInVector)
			{
				vectorUsers.pushBack(temp);
			}
		}
		fileNameUsers = nameOfFile;
	}
	
	delete[] buffer;
	input.close();
	std::cout << "File \"" << nameOfFile << "\" is now open!" << std::endl;
}
void Engine::close(const bool isBooksOrUsers)
{
	if (isBooksOrUsers)
	{
		fileNameBooks.~String();
		for (size_t i = 0; i < vectorBooks.getSize(); i++)
		{
			vectorBooks[i].~Book();
		}
		vectorBooks = Vector<Book>();
	}
	else
	{
		fileNameUsers.~String();
		for (size_t i = 0; i < vectorUsers.getSize(); i++)
		{
			vectorUsers[i].~User();
		}
		vectorUsers = Vector<User>();
		vectorUsers.pushBack(currentUser);
	}
	
	std::cout << "File is now closed!" << std::endl;
}


char* Engine:: trimEmptySpaces(char* input)
{
	while (input[0] == ' ' )
	{
		for (size_t i = 0; i < strlen(input) -1; i++)
		{
			input[i] = input[i + 1];
			
		}
		input[strlen(input) - 1] = '\0';
	}
	while (input[strlen(input) - 1] == ' ' || input[strlen(input) - 1] == 9)
	{
		input[strlen(input) - 1] = '\0';
	}
	input[strlen(input)] = '\0';
	return input;
}

Vector<String> Engine:: splitCommand(char* command)
{
	Vector<String> splitCommand;
	
	char* word = new char[30];
	size_t j = 0;
	for (size_t i = 0; i <= strlen(command); i++)
	{
		if (command[i] == ' ' || command[i] == '\0')
		{
			word[j] = '\0';
			splitCommand.pushBack(word);
			word = new char[30];
			j = 0;
		}
		else 
		{
			word[j] = command[i];
			j++;
		}
		
	}
	return splitCommand;
	
}

//when isAsc true -> ascending
void Engine::sortBooks( const String command, const bool isAsc)
{
	Vector<Book> temp = vectorBooks;
	if (command == "title")
	{
		int i, j;
		Book key;
		for (i = 1; i < temp.getSize(); i++)
		{
			key = temp[i];
			j = i - 1;
			while (j >= 0 && compareStrings(temp[j].get_title(), key.get_title()))
			{
				temp[j + 1] = temp[j];
				j = j - 1;
			}
			temp[j + 1] = key;
		}
	}
	else if (command == "author")
	{
		int i, j;
		Book key;
		for (i = 1; i < temp.getSize(); i++)
		{
			key = temp[i];
			j = i - 1;
			while (j >= 0 && compareStrings(temp[j].get_author(), key.get_author()))
			{
				temp[j + 1] = temp[j];
				j = j - 1;
			}
			temp[j + 1] = key;
		}
	}
	else if (command == "rating")
	{
		int i, j;
		Book key;
		for (i = 1; i < temp.getSize(); i++)
		{
			key = temp[i];
			j = i - 1;
			while (j >= 0 && temp[j].get_rating() > key.get_rating())
			{
				temp[j + 1] = temp[j];
				j = j - 1;
			}
			temp[j + 1] = key;
		}
	}
	else if (command == "year")
	{
		int i, j;
		Book key;
		for (i = 1; i < temp.getSize(); i++)
		{
			key = temp[i];
			j = i - 1;
			while (j >= 0 && temp[j].get_yearOfPublishing()> key.get_yearOfPublishing())
			{
				temp[j + 1] = temp[j];
				j = j - 1;
			}
			temp[j + 1] = key;
		}
	}
	if (isAsc)
	{
		for (size_t i = 0; i < temp.getSize(); i++)
		{
			std::cout << "|N: " << i + 1 << "| " << temp[i] << std::endl;
		}
	}
	else
	{
		for (int i = temp.getSize() - 1; i >=0 ; i--)
		{
			std::cout << "|N: " << temp.getSize() - i << "| " << temp[i] << std::endl;
		}
	}
	
}

bool Engine:: compareStrings(const char* str1,const char* str2)
{
	char* temp1 = new char[strlen(str1) + 1];
	strcpy_s(temp1, strlen(str1) + 1, str1);
	char* temp2 = new char[strlen(str2) + 1];
	strcpy_s(temp2, strlen(str2) + 1, str2);
	size_t maxLength = std::max<size_t>(strlen(temp1), strlen(temp1));
	for (size_t i = 0; i < maxLength; i++)
	{
		
		if (temp1[i] != '\0' && temp2[i] == '\0')
		{
			return true;
		}
		else if (temp1[i] == '\0' && temp2[i] != '\0')
		{
			return false;
		}
		if (temp1[i] >= 'A' && temp1[i] <= 'Z')
		{
			temp1[i] += 32;
		}
		if (temp2[i] >= 'A' && temp2[i] <= 'Z')
		{
			temp2[i] += 32;
		}
		if (temp1[i] > temp2[i])
		{
			return true;
		}
		else if (temp1[i] < temp2[i])
		{
			return false;
		}
	}
	return false;
}
bool Engine::checkIfISBNIsTaken(const char* command) 
{
	for (size_t i = 0; i < vectorBooks.getSize(); i++)
	{
		if (strcmp(command, vectorBooks[i].get_isbn()) == 0)
		{
			return true;
		}
	}
	return false;
}

