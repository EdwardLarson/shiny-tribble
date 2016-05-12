#pragma once

#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include "ObjectPool.h"

namespace utility{
namespace datastructures{

template <class T>
class PooledList {

	//NODE
private:
	struct Node {
		Node();
		Node(const T& val);
		Node(const Node& other);
		~Node();

		Node& operator=(const Node& other);

		T value;
		Node* next;
		Node* prev;
	};

	//ITERATOR
public:
	class Iterator {
		friend PooledList<T>;
	public:
		Iterator();
		Iterator(PooledList* list_);
		Iterator(const Iterator& other);
		~Iterator();

		Iterator& operator=(const Iterator& other);

		T& operator*() { return node->value; }
		T* operator->() { return &(node->value); }

		bool operator==(const Iterator& other) { return node == other.node && mList == other.mList; }
		bool operator!=(const Iterator& other) { return node != other.node; }

		Iterator& operator++();
		Iterator operator++(int n);

		Iterator& operator--();
		Iterator operator--(int n);
	private:
		Iterator(Node* node_, PooledList* mList_);

		Node* node;
		PooledList* mList;
	};

	typedef Iterator iterator;

public:
	PooledList(unsigned int poolSize);
	PooledList(const PooledList& other);
	virtual ~PooledList();

	PooledList& operator=(const PooledList& other);

	unsigned int size() { return size_; }
	iterator begin();
	iterator end();
	void push_back(const T& val);
	void push_front(const T& val);
	iterator insert(Iterator iter, const T& val);
	iterator erase(Iterator iter);
	void clear();

protected:
private:
	ObjectPool<Node> pool;
	Node* head;
	Node* tail;

	unsigned int size_;
};

//POOLED LIST IMPLEMENTATION
//========================================

template <class T>
PooledList<T>::PooledList(unsigned int poolSize) : pool(poolSize), head(pool.new_item()), tail(pool.new_item()), size_(0) {
	head->next = tail;
	tail->prev = head;
}

template <class T>
PooledList<T>::PooledList(const PooledList<T>& other) : pool(other.pool.size()), head(pool.new_item()), tail(pool.new_item()), size_(0) {
	head->next = tail;
	tail->prev = head;

	for (PooledList<T>::iterator iter = other.begin(); iter != other.end(); ++iter) {
		push_back(*iter);
	}
}

template <class T>
PooledList<T>::~PooledList() {
	//because all of the pointers actually point to objects in the pool,
	//their memory will be freed when the ObjectPool goes out of scope,
	//so no manual memory deallocation necessary
}

//assignment operator, creates a deep copy of another PooledList
template<class T>
PooledList<T>& PooledList<T>::operator=(const PooledList<T>& other) {
	clear();
	ObjectPool<T> tmpPool(other.pool.size());
	pool = tmpPool;

	head = pool.new_item();
	tail = pool.new_item();

	head->next = tail;
	tail->prev = head;

	for (PooledList<T>::iterator iter = other.begin(); iter != other.end(); ++iter) {
		push_back(*iter);
	}

	return *this;
}

template <class T>
typename PooledList<T>::iterator PooledList<T>::begin() {
	return iterator(head->next, this);
}

template <class T>
typename PooledList<T>::iterator PooledList<T>::end() {
	return iterator(tail, this);
}

template <class T>
void PooledList<T>::push_front(const T& val) {
	Node* newNode = pool.new_item(Node(val));
	newNode->prev = head;
	newNode->next = head->next;
	head->next->prev = newNode;
	head->next = newNode;

	++size_;
}

template <class T>
void PooledList<T>::push_back(const T& val) {
	Node* newNode = pool.new_item(Node(val));
	newNode->next = tail;
	newNode->prev = tail->prev;
	tail->prev->next = newNode;
	tail->prev = newNode;

	++size_;
}

template <class T>
typename PooledList<T>::iterator PooledList<T>::insert(Iterator iter, const T& val) {
	if (iter.node == NULL) {
		std::cerr << "ERROR: Iterator with NULL node!" << std::endl;
		return iter;
	}
	else if (iter.mList != this) {
		std::cerr << "ERROR: Iterator doesn't belong to this list!" << std::endl;
		return iter;
	}
	else {
		Node* newNode = pool.new_item(val);

		if (iter.node == head) {
			newNode->next = head->next;
			newNode->prev = head;
			head->next = newNode;
		}
		else {
			newNode->next = iter.node;
			newNode->prev = iter.node->prev;
			iter.node->prev->next = newNode;
			iter.node->prev = newNode;
		}

		++size_;

		return iterator(newNode, this);
	}
}

template <class T>
typename PooledList<T>::iterator PooledList<T>::erase(Iterator iter) {
	if (iter.node == NULL) {
		std::cerr << "ERROR: Iterator with NULL node!" << std::endl;
		return iter;
	}
	else if (iter.mList != this) {
		std::cerr << "ERROR: This iterator doesn't belong to this list!" << std::endl;
		return iter;
	}
	else if (iter.node == head || iter.node == tail) {
		return iter;
	}
	else {
		//reroute linked list around this node
		iter.node->prev->next = iter.node->next;
		///else std::cerr << "ERROR: node->prev is null" << std::endl;
		iter.node->next->prev = iter.node->prev;
		///else std::cerr << "ERROR: node->next is null" << std::endl;

		//deallocate this node and decrement size
		Node* toReturn = iter.node->next;
		pool.free_item(iter.node);
		--size_;

		return iterator(toReturn, this);
	}
}

template <class T>
void PooledList<T>::clear() {
	Node* tmp;
	Node* currentNode = head->next;
	while (currentNode != tail) {
		tmp = currentNode->next;
		pool.free_item(currentNode);
		currentNode = tmp;
	}

	size_ = 0;
}

//ITERATOR IMPLEMENTATION
//========================================

template <class T>
PooledList<T>::Iterator::Iterator() : node(NULL), mList(NULL) {

}

template <class T>
PooledList<T>::Iterator::Iterator(const typename PooledList<T>::Iterator& other) : node(other.node), mList(other.mList) {

}

template <class T>
PooledList<T>::Iterator::Iterator(Node* node_, PooledList* mList_) : node(node_), mList(mList_) {

}

template <class T>
PooledList<T>::Iterator::~Iterator() {

}

template <class T>
typename PooledList<T>::Iterator& PooledList<T>::Iterator::operator=(const typename PooledList<T>::Iterator& other) {
	node = other.node;
	mList = other.mList;

	return *this;
}

template <class T>
typename PooledList<T>::Iterator& PooledList<T>::Iterator::operator++() {
	if (node != NULL && node->next != NULL) {
		node = node->next;
	}

	return *this;
}

template <class T>
typename PooledList<T>::Iterator PooledList<T>::Iterator::operator++(int n) {
	Iterator temp = *this;
	++(*this);

	return temp;
}

template <class T>
typename PooledList<T>::Iterator& PooledList<T>::Iterator::operator--() {
	if (node != NULL && node->prev != NULL) {
		node = node->prev;
	}

	return *this;
}

template <class T>
typename PooledList<T>::Iterator PooledList<T>::Iterator::operator--(int n) {
	Iterator temp = *this;
	--(*this);

	return temp;
}

//NODE IMPLEMENTATION
//========================================

template <class T>
PooledList<T>::Node::Node() : next(NULL), prev(NULL) {

}

template <class T>
PooledList<T>::Node::Node(const T& val) : value(val), next(NULL), prev(NULL) {

}

template <class T>
PooledList<T>::Node::Node(const typename PooledList<T>::Node& other) : value(other.value), next(other.next), prev(other.prev) {

}

template <class T>
PooledList<T>::Node::~Node() {

}

template <class T>
typename PooledList<T>::Node& PooledList<T>::Node::operator=(const typename PooledList<T>::Node& other) {
	value = other.value;
	next = other.next;
	prev = other.prev;

	return *this;
}

}
}

#endif