#pragma once

template <class T>
struct node {
	T value;
	node* next;
	node* prev;
};

template <class T>
class List {
public:
	List() 
		: next(nullptr)
		, prev(nullptr)
	{}

	List(const List&);
	List(const List&&);
	~List();

	size_t size() const;
	//explicit List(int size);


private:
	node* _next;
	node* _prev;
};
