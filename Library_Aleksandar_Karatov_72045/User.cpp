#include "User.h"
#include <cstring>
#include <fstream>
User::User()
{
	username = nullptr;
	password = nullptr;
	isAdmin = false;
}
User::User(const char* Username, const char* Password, bool IsAdmin)
{
	set_username(Username);
	set_password(Password);
	set_auth(IsAdmin); 
}
User::User(const User& other)
{
	copy(other);
}

User::~User()
{
	destroy();
}
void User:: set_username(const char* other)
{
	username = new char[strlen(other) + 1];
	strcpy_s(username, strlen(other) + 1, other);
}
const char* User::get_username()
{
	return username;
}
const bool User::get_auth()
{
	return isAdmin;
}
void User:: set_password(const char* other)
{
	password = new char[strlen(other) + 1];
	strcpy_s(password, strlen(other) + 1, other);
}
const char* User::get_password()
{
	return password;
}
void User:: set_auth(bool other)
{
	isAdmin = other;
}
bool User:: operator==(const User& other)
{
	return (strcmp(username, other.username) == 0) &&
		(strcmp(password, other.password) == 0) &&
		(isAdmin == other.isAdmin) == true;
}
bool User:: operator!=(const User& other)
{
	return (strcmp(username, other.username) == 0) &&
		(strcmp(password, other.password) == 0) &&
		(isAdmin == other.isAdmin) == false;
}
User& User:: operator=(const User& other)
{
	copy(other);
	return *this;
}

std::ofstream& operator<<(std::ofstream& out, const User& object)
{
	 out << object.username << ";" << object.password << ";"<<object.isAdmin;
	 return out;
}
void User:: setFromFile(char* input)
{
	for (size_t i = 0; i < strlen(input); i++)
	{
		char* temp = new char[30];
		for (size_t j = 0; input[i] != ';'; j++)
		{
			temp[j] = input[i];
			i++;
			if (input[i] == ';')
			{
				temp[j+1] = '\0';
				break;
			}
		}
		set_username(temp);
		i++;

		delete[] temp;
		temp = new char[30];
		temp = new char[30];
		for (size_t j = 0; input[i] != ';'; j++)
		{
			temp[j] = input[i];
			i++;
			if (input[i] == ';')
			{
				temp[j+1] = '\0';
				break;
			}
		}
		set_password(temp);
		i++;
		delete[] temp;
		if (input[i] == '0')
		{
			set_auth(false);
		}
		else
		{
			set_auth(true);
		}
		break;
	}

}



void User::destroy()
{
	delete[] username;
	delete[] password;
	username = nullptr;
	password = nullptr;
	isAdmin = false;
}
void User::copy(const User& other)
{
	if (this != &other)
	{
		username = new char[strlen(other.username) + 1];
		strcpy_s(username, strlen(other.username) + 1, other.username);
		password = new char[strlen(other.password) + 1];
		strcpy_s(password, strlen(other.password) + 1, other.password);
		isAdmin = other.isAdmin;
	}
	
}