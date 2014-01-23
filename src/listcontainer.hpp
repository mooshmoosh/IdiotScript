/*
 * listcontainer.hpp
 * 
 * Copyright 2014 mooshmoosh <developerwill1@gmail.com>
 * 
 */


#ifndef LISTCONTAINER_HPP
#define LISTCONTAINER_HPP

#include <iostream>

template <class T>
class ListContainer {
	public:
		ListContainer();
		~ListContainer();
		T&  operator[] (int n);
		void append(T& value);
		
		void remove(int n);
		int length();
	private:
		int mLength;
		struct ContainedList {
			ContainedList() {
				next = NULL;
			}
			~ContainedList() {
				if(next!=NULL) {
					delete next;
				}
			}
			T element;
			ContainedList * next;
		} *first, *last, *lastAccessed;
		int lastAccessedNumber;
};

template <class T>
ListContainer<T>::ListContainer()
{
	first = NULL;
	last = NULL;
	lastAccessed = NULL;
	lastAccessedNumber = 0;
	mLength = 0;
}

template <class T>
int ListContainer<T>::length() {
	return mLength;
}

template <class T>
void ListContainer<T>::append(T& value) {
	if(first==NULL) {
		first = new ContainedList;
		last = first;
	}
	else {
		last->next = new ContainedList;
		last = last->next;
	}
	last->element = value;
	mLength++;
	
}

template <class T>
T &ListContainer<T>::operator[] (int n) {
	if(first==NULL) {
		first = new ContainedList;
		last = first;
		for(int i=1;i<n;i++) {
			last->next = new ContainedList;
			last = last->next;
		}
		mLength = n+1;
		return last->element;
	}
	else if(n >= mLength) {
		for(int i=mLength-1;i<n;i++) {
			last->next = new ContainedList;
			last = last->next;
		}
		mLength = n+1;
		return last->element;
	}
	
	ContainedList *p;
	
	if(lastAccessed!=NULL && n > lastAccessedNumber) {
		p = lastAccessed;
		for(int i=lastAccessedNumber;i<n;i++) {
			p = p->next;
		}
		
	}
	else {
		p = first;
		for(int i=0;i<n;i++) {
			p = p->next;
		}
	}
	lastAccessed = p;
	lastAccessedNumber = n;
	return p->element;
}

template <class T>
ListContainer<T>::~ListContainer() {
	if(first!=NULL) {
		delete first;
	}
}

#endif /* LISTCONTAINER_HPP */ 
