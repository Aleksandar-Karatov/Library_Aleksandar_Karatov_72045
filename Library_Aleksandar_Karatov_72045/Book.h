#pragma once
#include "Vector.h"
#include "String.h"
class Book
{
public:
	Book();
	Book(const char*, const char*, const char*,const char* , const int, const Vector<String>, const double, const char*);
	Book(const Book&);
	void set_author(const char*);
	void set_title(const char*);
	void set_genre(const char*);
	void set_description(const char*);
	void set_yearOfPublishing(const int);
	void set_keywords(const Vector<String>);
	void set_rating(const double);
	void set_isbn(const char*);

	const char* get_author();
	const char* get_title();
	const char* get_description();
	const char* get_genre();
	const int get_yearOfPublishing();
	const Vector<String> get_keywords();
	const double get_rating();
	const char* get_isbn();

	bool operator==(const Book&);
	bool operator!=(const Book&);
	Book& operator= (const Book&);
	friend std::ostream& operator<<(std::ostream&, const Book&);
	~Book();

private:
	char* author;
	char* title;
	char* genre;
	char* description;
	int yearOfPublishing;
	Vector<String> keywords;
	double rating;
	char* isbn;
	void copy(const Book& other);
	void destroy();
};

