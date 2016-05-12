#pragma once

namespace utility{
namespace datastructures{

template <class T>
class ObjectPool {

private:
	class PooledObject {
	public:
		PooledObject();
		PooledObject(const T& obj_in);
		PooledObject(unsigned int next);
		PooledObject(const T& obj_in, unsigned int next);

		unsigned int getNext();
		void setNext(unsigned int next);
		T* getObj();
		void setObj(const T& obj_);

	private:
		//stores the next available slot after this one; NULL if not available
		T obj;
		unsigned int nextAvailable;
	};

public:
	ObjectPool();
	ObjectPool(unsigned int size);
	ObjectPool(const ObjectPool& other);
	~ObjectPool();

	ObjectPool& operator=(const ObjectPool& other);

	T* new_item(T item);
	T* new_item();
	void free_item(T* item);
	void free_all();

	unsigned int size() const { return size_; }

private:
	static const unsigned int DEFAULT_POOL_SIZE = 50;
	unsigned int size_;

	PooledObject* pool;

	unsigned int firstAvailable;
};

//IMPLEMENTATION
template <class T>
ObjectPool<T>::ObjectPool() : size_(DEFAULT_POOL_SIZE), pool(new PooledObject[size_]), firstAvailable(0) {
	for (unsigned int i = 0; i < size_; i++) {
		pool[i].setNext(i + 1);
	}
}

template <class T>
ObjectPool<T>::ObjectPool(unsigned int size) : size_(size), pool(new PooledObject[size_]), firstAvailable(0) {
	for (unsigned int i = 0; i < size_; i++) {
		pool[i].setNext(i + 1);
	}
}

//copy constructor, creates a deep copy of another ObjectPool
template <class T>
ObjectPool<T>::ObjectPool(const ObjectPool<T>& other) : size_(other.size_), pool(new PooledObject[size_]), firstAvailable(0) {
	for (unsigned int i = 0; i < size_; i++) {
		pool[i] = other.pool[i];
		pool[i].setNext(other.pool[i].getNext());
	}
	firstAvailable = other.firstAvailable;
}

template <class T>
ObjectPool<T>::~ObjectPool() {
	delete [] pool;
}

//assignment operator, creates a deep copy of another ObjectPool
template <class T>
ObjectPool<T>& ObjectPool<T>::operator=(const ObjectPool<T>& other) {
	free_all();
	delete [] pool;

	size_ = other.size_;
	pool = new PooledObject[size_];

	for (unsigned int i = 0; i < size_; i++) {
		pool[i] = other.pool[i];
		pool[i].setNext(other.pool[i].getNext());
	}

	return *this;
}

template <class T>
T* ObjectPool<T>::new_item() {
	unsigned int slot = firstAvailable;
	if (slot != size_) {
		firstAvailable = pool[slot].getNext();

		///std::cout << "ObjectPool " << this << " Allocated: " << pool[slot].getObj() << std::endl;
		return pool[slot].getObj();
	}

	return NULL;
}

template <class T>
T* ObjectPool<T>::new_item(T item) {
	T* alloc = new_item();
	if (alloc != NULL) {
		(*alloc) = item;
		return alloc;
	}

	return NULL;
}

template <class T>
void ObjectPool<T>::free_item(T* item) {
	unsigned int itemAddress = (unsigned int)item;
	unsigned int poolAddress = (unsigned int)pool;

	unsigned int slot = (itemAddress - poolAddress) / sizeof(PooledObject);

	/**
	std::cout << "when freeing from ObjectPool "  << this << ": " << std::endl
	<< "  T* item: " << item << std::endl
	<< "  T* &pool: " << &pool << std::endl
	<< "  int itemAddress: " << itemAddress << std::endl
	<< "  int poolAddress: " << poolAddress << std::endl
	<< "  int difference: " << (itemAddress - poolAddress) << std::endl
	<< "  sizeof: " << sizeof(PooledObject) << std::endl
	<< "  slot: " << slot << std::endl;
	**/

	if (slot < size_) {
		pool[slot].setNext(firstAvailable);
		firstAvailable = slot;
	}
	else {
		std::cerr << "ERROR: Tried to free item not part of this object pool: " << item << std::endl;
	}
}

template <class T>
void ObjectPool<T>::free_all() {
	for (unsigned int i = 0; i < size_; i++) {
		pool[i].setNext(i + 1);
	}
	firstAvailable = 0;
}

//POOLED OBJECT IMPLEMENTATION
template <class T>
ObjectPool<T>::PooledObject::PooledObject() : nextAvailable(0) {

}

template <class T>
ObjectPool<T>::PooledObject::PooledObject(const T& obj_in) : obj(obj_in), nextAvailable(0) {

}

template <class T>
ObjectPool<T>::PooledObject::PooledObject(unsigned int next) : nextAvailable(next) {

}

template <class T>
ObjectPool<T>::PooledObject::PooledObject(const T& obj_in, unsigned int next) : obj(obj_in), nextAvailable(next) {

}

template <class T>
unsigned int ObjectPool<T>::PooledObject::getNext() {
	return nextAvailable;
}

template <class T>
void ObjectPool<T>::PooledObject::setNext(unsigned int next) {
	nextAvailable = next;
}

template <class T>
T* ObjectPool<T>::PooledObject::getObj() {
	return &obj;
}

template <class T>
void ObjectPool<T>::PooledObject::setObj(const T& obj_) {
	obj = obj_;
}

}
}