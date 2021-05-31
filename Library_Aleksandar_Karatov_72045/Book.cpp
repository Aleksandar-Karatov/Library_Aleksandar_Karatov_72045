#include "Book.h"
#include<fstream>

Book::Book()
{
	author = nullptr;
	title = nullptr;
	genre = nullptr;
	yearOfPublishing = 0;
	keywords = Vector<String>();
	rating = -1;
	isbn = nullptr;
}
Book::Book(const char* Author, const char* Title, const char* Genre, const char* Description,  const int YearOfPublishing,
	const Vector<String> Keywords, const double Rating, const char* Isbn)
{
	set_author(Author);
	set_title(Title);
	set_genre(Genre);
	yearOfPublishing = YearOfPublishing;
	set_keywords(Keywords);
	rating = Rating;
	set_isbn(Isbn);
	set_description(Description);
}
Book::Book(const Book& other)
{
	copy(other);
}


void Book::set_author(const char* other )
{
	author = new char[strlen(other) + 1];
	strcpy_s(author, strlen(other) + 1, other);
}
void Book::set_description(const char* other)
{
	description = new char[strlen(other) + 1];
	strcpy_s(description, strlen(other) + 1, other);
}
void Book::set_title(const char* other)
{
	title = new char[strlen(other) + 1];
	strcpy_s(title, strlen(other) + 1, other);
}
void Book::set_genre(const char* other)
{
	genre = new char[strlen(other) + 1];
	strcpy_s(genre, strlen(other) + 1, other);
}
void Book::set_yearOfPublishing(const int other)
{
	yearOfPublishing = other;
}
void Book::set_keywords(const Vector<String> other)
{
	keywords = other;
}
void Book::set_rating(const double other)
{
	rating = other;
}
void Book::set_isbn(const char* other)
{
	isbn = new char[strlen(other) + 1];
	strcpy_s(isbn, strlen(other) + 1, other);
}


const char* Book::get_author()
{
	return author;
}
const char* Book::get_title()
{
	return title;
}
const char* Book::get_genre()
{
	return genre;
}
const char* Book:: get_description()
{
	return description;
}
const int Book::get_yearOfPublishing()
{
	return yearOfPublishing;
}
const Vector<String> Book::get_keywords()
{
	return keywords;
}
const double Book::get_rating()
{
	return rating;
}
const char* Book::get_isbn()
{
	return isbn;
}

bool Book:: operator==(const Book& other)
{		
	if (keywords.getSize() != other.keywords.getSize())
	{
		return false;
	}
	for (size_t i = 0; i < other.keywords.getSize(); i++)
	{
		if (keywords[i] != other.keywords[i])
		{
			return false;
		}
	}
	
	return (strcmp(author, other.author) == 0) && (strcmp(title, other.title) == 0) &&
		(strcmp(genre, other.genre) == 0) && (yearOfPublishing == other.yearOfPublishing) &&
		(rating == other.rating) && (strcmp(isbn, other.isbn) == 0) && (strcmp(description, other.description) == 0) == true;
}
bool Book:: operator!=(const Book& other)
{
	if (keywords.getSize() != other.keywords.getSize())
	{
		return true;
	}
	for (size_t i = 0; i < other.keywords.getSize(); i++)
	{
		if (keywords[i] != other.keywords[i])
		{
			return true;
		}
	}
	return (strcmp(author, other.author) == 0) && (strcmp(title, other.title) == 0) &&
		(strcmp(genre, other.genre) == 0) && (yearOfPublishing == other.yearOfPublishing) &&
		(rating == other.rating) && (strcmp(isbn, other.isbn) == 0) && (strcmp(description, other.description) == 0) == false;
}
Book& Book:: operator= (const Book& other)
{
	copy(other);
	return *this;
}
std::ostream& operator<<(std::ostream& output, const Book& object)
{
	output << "Title: " <<object.title << std::endl
		<< "Author: " << object.author << std::endl
		<< "Genre: " << object.genre << std::endl
		<< "Year of publishing: " << object.yearOfPublishing << std::endl
		<< "Rating: " << object.rating << "/10" << std::endl
		<< "Description: " << object.description << std::endl;
	std::cout << "Keywords: ";
	for (size_t j = 0; j < object.keywords.getSize() - 1; j++)
	{
		std::cout << object.keywords[j] << ", ";
	}
	std::cout << object.keywords[object.keywords.getSize() - 1] << std::endl;
	std::cout << "ISBN: " << object.isbn << std::endl;
	return output;
}
void Book::copy(const Book& other)
{
	if (this != &other)
	{
		set_author(other.author);
		set_genre(other.genre);
		set_isbn(other.isbn);
		set_keywords(other.keywords);
		set_title(other.title);
		set_description(other.description);
		rating = other.rating;
		yearOfPublishing = other.yearOfPublishing;
	}
	
}
void Book::destroy()
{
	delete[] author;
	delete[] title;
	delete[] genre;
	delete[] isbn;
	delete[] description;
	author = nullptr;
	title = nullptr;
	genre = nullptr;
	isbn = nullptr;
	description = nullptr;
	rating = -1;
	yearOfPublishing = 0;

}
char* spaceToEqualSign(char* input)
{
	for (size_t i = 0; i < strlen(input); i++)
	{
		if (input[i] == ' ')
		{
			input[i] = '=';
		}
	}
	return input;
}

char* equalSignToSpace(char* input)
{
	for (size_t i = 0; i < strlen(input); i++)
	{
		if (input[i] == '=')
		{
			input[i] = ' ';
		}
	}
	return input;
}
std::ofstream& operator<<(std::ofstream& output, const Book& object)
{
	output << spaceToEqualSign(object.author) << ";" <<
			spaceToEqualSign(object.title) << ";" << 
			spaceToEqualSign(object.genre) << ";" <<
			spaceToEqualSign(object.description) << ";" <<
			object.yearOfPublishing <<";" << object.rating << ";"<< object.isbn << ";";
	String tempKeyword;
	for (size_t i = 0; i < object.keywords.getSize() ; i++)
	{
		tempKeyword = object.keywords[i];
		for (size_t j = 0; j < tempKeyword.get_len(); j++)
		{
			if (tempKeyword[j] == ' ')
			{
				tempKeyword[j] = '=';
			}
		}
		output << tempKeyword << "|";
	}

	return output;
}
void Book:: setFromFile(char* input)
{
	String buffer;
	
	buffer = input;
	for (size_t i = 0; i < buffer.get_len(); i++)
	{
		char* temp = new char[100];
		for (size_t j = 0; buffer[i]!= ';' ; j++)
		{
			temp[j] = buffer[i];
			i++;
			if (buffer[i] == ';')
			{
				temp[j + 1] = '\0';
				break;
			}
		}
		i++;
		set_author(equalSignToSpace(temp));

		delete[] temp;
		temp = new char[100];
		for (size_t j = 0; buffer[i] != ';'; j++)
		{
			temp[j] = buffer[i];
			i ++;
			if (buffer[i] == ';')
			{
				temp[j + 1] = '\0';
				break;
			}
		}
		i++;
		set_title(equalSignToSpace(temp));

		delete[] temp;
		temp = new char[100];
		for (size_t j = 0; buffer[i] != ';'; j++)
		{
			temp[j] = buffer[i];
			i ++;
			if (buffer[i] == ';')
			{
				temp[j + 1] = '\0';
				break;
			}
		}
		i++;
		set_genre(equalSignToSpace(temp));

		delete[] temp;
		temp = new char[100];
		for (size_t j = 0; buffer[i] != ';'; j++)
		{
			temp[j] = buffer[i];
			i ++;
			if (buffer[i] == ';')
			{
				temp[j + 1] = '\0';
				break;
			}
		}
		i++;
		set_description(equalSignToSpace(temp));

		delete[] temp;
		temp = new char[100];
		int intTemp = 0;
		for (size_t j = 0; buffer[i] != ';'; j++)
		{
			temp[j] = buffer[i];
			i++;
			if (buffer[i] == ';')
			{
				temp[j + 1] = '\0';
				break;
			}
		}

		for (size_t j = 0; j < strlen(temp) ; j++)
		{
			if (j == 0 && temp[j] == '-')
			{
				intTemp = - (temp[j + 1] - '0' );
				j++;
 			}
			else if (temp[0] == '-')
			{
				intTemp = intTemp * 10 - (temp[j] - '0');
			}
			else
			{
				intTemp = intTemp * 10 + (temp[j] - '0');
			}
		}
		set_yearOfPublishing(intTemp);

		i++;
		delete[] temp;
		temp = new char[100];
		intTemp = 0;
		for (size_t j = 0; buffer[i] != ';'; j++)
		{
			temp[j] = buffer[i];
			i++;
			if (buffer[i] == ';')
			{
				temp[j + 1] = '\0';
				break;
			}
		}

		for (size_t j = 0; j < strlen(temp); j++)
		{
			intTemp = intTemp * 10 + (temp[j] - '0');
		}
		set_rating(intTemp);
		i++;
		delete[] temp;
		temp = new char[100];

		for (size_t j = 0; buffer[i] != ';'; j++)
		{
			temp[j] = buffer[i];
			i ++;
			if (buffer[i] == ';')
			{
				temp[j + 1] = '\0';
				break;
			}
		}
		i++;
		set_isbn(temp);
		delete[] temp;
		temp = new char[100];
		Vector<String> tempKeys;
		for (size_t k = i; k < buffer.get_len() ;k++)
		{
			for (size_t j = 0; buffer[k] != '|'; j++)
			{
				temp[j] = buffer[k];
				k++;
				if (buffer[k] == '|')
				{
					temp[j + 1] = '\0';
					break;
				}
			}
			
			tempKeys.pushBack(equalSignToSpace(temp));
			delete[] temp;
			temp = new char[100];
			i = k;
		}
		set_keywords(tempKeys);
		


	}

}




Book::~Book()
{
	destroy();
}