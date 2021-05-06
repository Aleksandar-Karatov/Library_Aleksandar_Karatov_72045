#include "String.h"

void String::copy(const String& other)
{
	
	str = new char[strlen(other.str) + 1];
	strcpy_s(str, strlen(other.str) + 1, other.str);
}
void String::destroy()
{
	delete[] str;
	str = nullptr;
}
String::String()
{
	str = nullptr;
}
String::String(const char* other)
{
	set_str(other);
}
String::String(const String& other)
{
	copy(other);
}
String:: ~String()
{
	destroy();
}
void String::set_str(const char* other)
{
	str = new char[strlen(other) + 1];
	strcpy_s(str, strlen(other) + 1, other);
}
const char* String::get_str()const
{
	return str;
}
const bool String::isEmpty() const
{
	if (str == nullptr)
	{
		return true;
	}
	return false;
}
int String::get_len() const
{
	return strlen(str);
}
String& String:: operator=(const String& other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}

bool String:: operator==(const String& other) const
{
	return strcmp(str, other.str) == 0;
}
bool String:: operator!=(const String& other) const
{
	return strcmp(str, other.str) != 0;
}

char& String::operator[](const int i) const
{
	if (i < 0 || i >= strlen(str))
	{
		std::cout << "Index out of range!" << std::endl;
		exit(1);
	}
	else
		return str[i];
}

std::ostream& operator<<(std::ostream& output, const String& object) {

	output << object.str;
	return output;
}

std::istream& operator>>(std::istream& input, String& object) {

	char* buffer = new char[50];
	input >> buffer;
	object = String(buffer);
	delete[] buffer;

	return input;
}

