#pragma once
#include <iostream>

class User
{
public:
	User();
	User(const char*, const char*, bool);
	User(const User&);
	void set_username(const char*);
	const char* get_username();
	const char* get_password();
	void set_password(const char*);
	void set_auth(bool);
	const bool get_auth();
	bool operator==(const User&);
	bool operator!=(const User&);
	User& operator= (const User&);
	friend std::ofstream& operator<<(std::ofstream&, const User&);
	void setFromFile(char* input);
	~User();

private:
	char* username;
	char* password;
	bool isAdmin;
	void copy(const User& other);
	void destroy();
};

