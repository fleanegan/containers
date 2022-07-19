#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "gtest/gtest.h"
#include "../inc/IteratorTraits.hpp"
#include "../inc/Vector.hpp"
#include "../inc/VectorIterator.hpp"
#include "../inc/Stack.hpp"
#include "../inc/Utils.hpp"
#include "../inc/Pair.hpp"
#include "../inc/BinarySearchTree.hpp"
#include <iostream>
#define _DEBUG_SD 0

struct simpleDummy {
	int *i = NULL;
	int moves;

	simpleDummy() {
		_DEBUG_SD && std::cout << "default constructor" << std::endl;
		i = new int;
		moves = 0;
	}

	explicit simpleDummy(int in) {
		_DEBUG_SD && std::cout << "argument constructor. i is " << (void *) i << std::endl;
		i = new int;
		*i = in;
		moves = 0;
	}

	simpleDummy(const simpleDummy &other) {
		_DEBUG_SD && std::cout << "copy constructor. i is " << (void *) i << std::endl;
		i = new int;
		*i = *(other.i);
		moves = other.moves + 1;
	}

	simpleDummy &operator=(const simpleDummy &other) {
		_DEBUG_SD && std::cout << "assignment start, updating addr: " << (void *) i << " from addr: " << (void *) other.i << std::endl;
		*i = *(other.i);
		moves = other.moves + 1;
		_DEBUG_SD && std::cout << "assignment end" << std::endl;
		return *this;
	}

	bool operator==(const simpleDummy &rhs) const {
		return i == rhs.i;
	}

	bool operator!=(const simpleDummy &rhs) const {
		return !(rhs == *this);
	}

	int &operator*() {
		return *i;
	}

	void dummyFunction() {}

	~simpleDummy() {
		_DEBUG_SD && std::cout << "destructor" << std::endl;
		delete i;
	}
};

ft::vector<simpleDummy> createTestDummyVector() {
	ft::vector<simpleDummy> result;
	for (int i = 1; i < 6; ++i) {
		result.push_back(simpleDummy(i));
	}
	return result;
}
//
//template<class T>
//void testIterator(typename T::iterator it){
//	(void) it;
//}

template<typename It>
bool getHasSpecializedTag(std::bidirectional_iterator_tag a) {
	_DEBUG_SD && std::cout << "specialized function called" << std::endl;
	return true;
}

template<typename It>
bool getHasSpecializedTag(std::input_iterator_tag a) {
	_DEBUG_SD && std::cout << "generalized function called" << std::endl;
	return false;
}

template<typename It>
bool getHasSpecializedTag() {
	return getHasSpecializedTag<It>(typename It::iterator_category());
}

template<typename T>
class StupidInputIterator {
public:
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef std::input_iterator_tag iterator_category;
private:
	pointer _ptr;
public:
	StupidInputIterator(pointer ptr) : _ptr(ptr) {}

	bool operator==(const StupidInputIterator &rhs) const {
		return _ptr == rhs._ptr;
	}

	bool operator!=(const StupidInputIterator &rhs) const {
		return _ptr != rhs._ptr;
	}

	reference operator*() const {
		return *_ptr;
	}

	StupidInputIterator &operator++(){
		++_ptr;
		return *this;
	}

	StupidInputIterator operator++(int i) {
		StupidInputIterator<T> result = *this;
		if (i == 0)
			_ptr++;
		else
			while (i--)
				++_ptr;
		return result;
	}

	StupidInputIterator &operator--() {
		--_ptr;
		return *this;
	}

	StupidInputIterator operator--(int i) {
		StupidInputIterator<T> result = *this;
		if (i == 0)
			_ptr--;
		else
			while (i--)
				--_ptr;
		return result;
	}
};

void assertEqualityOfValuesContainedBySimpleDummyVector(ft::vector<simpleDummy> &x, ft::vector<simpleDummy> &y, size_t forElements){
	ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";

	for (int i = 0; i < forElements; ++i) {
		EXPECT_EQ(*x[i], *y[i]) << "Vectors x and y differ at index " << i;
	}
}

/*
 * 		1
	  /	  \
	2		5
   /	  /
  0		 4
 /
-1
*/
ft::BinarySearchTree<int, int> createThreeLevelTree() {
	ft::BinarySearchTree<int, int> result;

	result.insert(ft::make_pair(1, 0));
	result.insert(ft::make_pair(2, 0));
	result.insert(ft::make_pair(5, 0));
	result.insert(ft::make_pair(4, 0));
	result.insert(ft::make_pair(0, 0));
	result.insert(ft::make_pair(-1, 0));
	return result;
}

#endif     // TEST_UTILS_H
