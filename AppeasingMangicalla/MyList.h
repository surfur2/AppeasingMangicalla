#pragma once
#include <typeinfo>
//Macro definition for max size of the list
#define MAX_SIZE 1000
//Macro function definition that return the larger value of the two
#define GET_MAX(a,b) (a > b) ? a : b

//MyList is a generic data structure list.

template <typename T>
class MyList
{

public:
	//array of objects
	T* objects;
	//size of the list
	int size;
	//Top index of list
	int top;

	//Constructors
	MyList(int s);
	MyList();

	//Destructors
	~MyList();

	//Copy constructor
	MyList(const MyList& other);

	//Copy assignment operator overload
	MyList& operator=(const MyList& other)
	{
		if (this != &other)
		{
			this->size = other.size;
			this->top = other.top;

			if (this->objects == nullptr)
			{
				this->objects = new T[size];
			}

			for (int i = 0; i < size; i++)
				this->objects[i] = other.objects[i];
		}
		// TODO: insert return statement here
		return *this;
	}

	//Member functions
	void push(T& t);			//push Template object to top
	T pop();					//pop Template object from top
	T begin() const;			//return the first object
	T end() const;				//return the last object
	bool find(const T& t);		//find object return true if exists
	void remove(const T& t);	//remove a specific T object that exists in the list
	int& listEnd();				//return the a refeernce to top
};

template<typename T>
inline MyList<T>::MyList() : MyList<T>::MyList(100)
{
}

template<typename T>
inline MyList<T>::MyList(int s)
{
	try
	{
		if (GET_MAX(s, MAX_SIZE) > MAX_SIZE)
			throw - 1;
		size = s;
	}
	catch (int exception)
	{
		size = MAX_SIZE;
	}

	objects = new T[size];
	top = 0;
}

template<typename T>
inline MyList<T>::~MyList()
{
	delete[] objects;
}

template<typename T>
inline MyList<T>::MyList(const MyList & other)
{
	this->size = other.size;
	this->top = other.top;

	if (this->objects == nullptr)
	{
		this->objects = new T[size];
	}

	for (int i = 0; i < size; i++)
		this->objects[i] = other.objects[i];
}


template<typename T>
inline void MyList<T>::push(T & t)
{
	if (top > size)
		abort();
	objects[++top] = t;
}

template<typename T>
inline T MyList<T>::pop()
{
	if (top < 0)
		abort();
	return objects[top--];
}

template<typename T>
inline T MyList<T>::begin() const
{

	return objects[0];
}

template<typename T>
inline T MyList<T>::end() const
{
	return objects[top];
}

template<typename T>
inline void MyList<T>::remove(const T& t)
{
	for (int iterator = 0; iterator <= top; iterator++)
	{
		if (objects[iterator] == t)
		{
			int jterator = iterator;
			while (jterator <= top)
			{
				objects[jterator] = objects[++jterator];
			}
			top--;
		}

	}
}

template<typename T>
inline int & MyList<T>::listEnd()
{
	// TODO: insert return statement here
	return top;
}

template<typename T>
inline bool MyList<T>::find(const T & t)
{
	for (int i = 0; i <= top; i++)
	{
		if (objects[i] == t)
			return true;
	}

	return false;
}
