#pragma once
#include <iostream>
template <typename T>
class Vector
{
public:
	Vector()
	{
		size = 0;
		capacity = 8;
		data = new T[capacity];
	}
	Vector(const Vector<T>& other);
	Vector(const T*);
	size_t getSize()const
	{
		return size;
	}
	size_t getCapacity()const
	{
		return capacity;
	}
	T* getData()const
	{
		return data;
	}
	Vector<T>& operator= (const Vector<T>& other);
	T& operator[] (const size_t index)const;
	void pushBack(const T& toAdd);
	void deleteAtIndex(const size_t);
	~Vector()
	{
		data = nullptr;
		size = 0;
		capacity = 8;
	}

private:
	T* data;
	size_t size;
	size_t capacity;
	void copy(const Vector<T>& other)
	{
		
		size = other.size;
		capacity = other.capacity;
		data = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = other.data[i];
		}
		
	}
	void resize()
	{
		capacity *= 2;
		T* buffer = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			buffer[i] = data[i];
		}
		data = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = buffer[i];
		}

	}

};
template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copy(other);
}
template<typename T>
Vector<T>::Vector(const T* Data)
{
	size_t Size = 0;
	while (Data[Size] != NULL)
	{
		Size++;
	}
	size_t Capacity = 8;
	while (Capacity < Size)
	{
		Capacity *= 2;
	}
	size = Size;
	capacity = Capacity;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = Data[i];
	}
}
template<typename T>
Vector<T>& Vector<T> :: operator= (const Vector<T>& other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}
template <typename T>
T& Vector<T>:: operator[] (const size_t index)const
{
	if (index > size)
	{
		std::cout << "Index out of range";
		exit(1);
	}
	return data[index];
}
template<typename T>
void Vector<T>::pushBack(const T& toAdd)
{
	if (size + 1 >= capacity)
	{
		resize();
	}
	data[size] = toAdd;
	size++;
}
template<typename T>
void Vector<T>::deleteAtIndex(const size_t index)
{
	if (index > size)
	{
		std::cout << "Index out of range";
		exit(1);
	}
	for (size_t i = index; i < size-1; i++)
	{
		data[i] = data[i + 1];
	}
	size--;
}
