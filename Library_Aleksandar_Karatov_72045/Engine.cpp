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

		if (commandInStrings[0].toLower() == "users" && commandInStrings.getSize() > 1)
		{
			if (commandInStrings[1].toLower() == "add" && currentUser.get_auth() == true && commandInStrings.getSize() == 2)
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
			else if (commandInStrings[1].toLower() == "add" && currentUser.get_auth() == false)
			{
				std::cout << "You are unauthorized to create users!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "add" && commandInStrings.getSize() != 2)
			{
				std::cout << "Invalid input!" << std::endl;
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
			else if (commandInStrings[1].toLower() == "remove" && currentUser.get_auth() == false)
			{
				std::cout << "You are unauthorized to remove users!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "remove" && commandInStrings.getSize() != 3)
			{
				std::cout << "Invalid input!" << std::endl;
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
			else if (commandInStrings[1].toLower() == "all" && currentUser.get_auth() == false)
			{
				std::cout << "You are unauthorized to view users!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "all" && commandInStrings.getSize() != 2)
			{
				std::cout << "Invalid input!" << std::endl;
			}
		}

		


		//login
		else if (commandInStrings[0].toLower() == "login" && currentUser.get_username()==nullptr)
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
		else if (commandInStrings[0].toLower() == "login" && currentUser.get_username() != nullptr)
		{
			std::cout << "You are currently logged in!" << std::endl;
		}


		//logout
		else if (commandInStrings[0].toLower() == "logout" && currentUser.get_username() != nullptr)
		{
			currentUser.~User();
			//currentUser = User();
			std::cout << "You have logged out!" << std::endl;
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
			else if (commandInStrings[1].toLower() == "info" &&  currentUser.get_username() == nullptr)
			{
				std::cout << "You need to login to see the books in the library!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "info" && commandInStrings.getSize() != 3)
			{
				std::cout << "Invalid input!" << std::endl;
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
						if (title == vectorBooks[i].get_title())
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
						if (author == vectorBooks[i].get_author())
						{
							std::cout << vectorBooks[i] << std::endl;;
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
			else if (commandInStrings[1].toLower() == "find" && currentUser.get_username() == nullptr)
			{
				std::cout << "You need to login to see the books in the library!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "find" && commandInStrings.getSize() < 4)
			{
				std::cout << "Incomplete command!" << std::endl;
			}


			// books add
			if (commandInStrings[1].toLower() == "add" && currentUser.get_auth() == true && commandInStrings.getSize() == 2)
			{
				Book temp;
				std::cout << "Enter title:";
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
				temp.set_title(command);
				std::cout << "Enter author:";
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
				temp.set_author(command);
				std::cout << "Enter genre:";
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
				temp.set_genre(command);
				std::cout << "Enter description:";
				char* description = new char[100];
				std::cin.getline(description, 100);
				command = trimEmptySpaces(description);
				temp.set_description(description);
				delete[] description;
				description = nullptr;
				std::cout << "Enter ISBN:";
				std::cin.getline(command, 30);
				command = trimEmptySpaces(command);
				for (size_t i = 0; i < vectorBooks.getSize(); i++)
				{
					if (strcmp(command, vectorBooks[i].get_isbn()) == 0)
					{
						std::cout << "ISBN is taken! Chose another: ";
						std::cin.getline(command, 30);
						command = trimEmptySpaces(command);
						i = -1;
					}
				}
				temp.set_isbn(command);
				
				double rating;
				std::cout << "Enter rating:";
				std::cin >> rating;
				while (rating > 10 || rating < 0)
				{
					std::cout << "Enter a rating between 0 and 10:";
					std::cin >> rating;
				}
				temp.set_rating(rating);
				int yearofPublish;
				std::cout << "Enter year of publishing:";
				std::cin >> yearofPublish;
				time_t t = time(NULL);
				tm* timePtr = localtime(&t);
				while (yearofPublish > timePtr->tm_year + 1900)
				{
					std::cout << "Enter a valid year of publishing (before or equal to " << timePtr->tm_year + 1900 << "): ";
					std::cin >> yearofPublish;
				}
				temp.set_yearOfPublishing(yearofPublish);
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
			else if (commandInStrings[1].toLower() == "add" && currentUser.get_auth() == false)
			{
				std::cout << "You are unauthorized to add books!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "add" && commandInStrings.getSize() != 2)
			{
				std::cout << "Invalid input!" << std::endl;
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
			else if (commandInStrings[1].toLower() == "remove" && currentUser.get_auth() == false )
			{
				std::cout << "You are unauthorized to remove books!" << std::endl;
			}
			else if (commandInStrings[1].toLower() == "remove" && commandInStrings.getSize() < 3)
			{
				std::cout << "Incomplete command!" << std::endl;
			}

		}
		// file commands
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
		
		else if (commandInStrings[0].toLower() == "help" && fileNameBooks.isEmpty())
		{
			std::cout << "The following commands are supported:" << std::endl <<
				"open <file>	opens <file>" << std::endl <<
				"close			closes currently opened file" << std::endl <<
				"save			saves the currently open file" << std::endl <<
				"saveas <file>	saves the currently open file in <file>" << std::endl <<
				"help			prints this information" << std::endl <<
				"exit			exists the program" << std::endl;
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
			vectorUsers.pushBack(temp);
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
	}
	
	std::cout << "File is now closed!" << std::endl;
}


// a method used to check if a password or username is chosen according to the security policy
bool Engine:: validatePassAndUsername(const char* str)
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
