#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "gtest/gtest.h"
#include "../inc/IteratorTraits.hpp"
#include "../inc/Vector.hpp"
#include "../inc/VectorIterator.hpp"
#include <iostream>
#define _DEBUG_SD 0

struct simpleDummy {
	int *i = NULL;

	simpleDummy() {
		_DEBUG_SD && std::cout << "default constructor" << std::endl;
		i = new int;
	}

	explicit simpleDummy(int in) {
		_DEBUG_SD && std::cout << "argument constructor. i is " << (void *) i << std::endl;
		i = new int;
		*i = in;
	}

	simpleDummy(const simpleDummy &other) {
		_DEBUG_SD && std::cout << "copy constructor. i is " << (void *) i << std::endl;
		i = new int;
		*i = *(other.i);
	}

	simpleDummy &operator=(const simpleDummy &other) {
		_DEBUG_SD && std::cout << "assignment start, updating addr: " << (void *) i << " from addr: " << (void *) other.i << std::endl;
		*i = *(other.i);
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

template<class T>
void testIterator(typename T::iterator it){
	(void) it;
}

template<typename It>
bool getHasSpecializedTag(TRAIT_NS::bidirectional_iterator_tag a) {
	_DEBUG_SD && std::cout << "specialized function called" << std::endl;
	return true;
}

template<typename It>
bool getHasSpecializedTag(TRAIT_NS::input_iterator_tag a) {
	_DEBUG_SD && std::cout << "generalized function called" << std::endl;
	return false;
}

template<typename It>
bool getHasSpecializedTag() {
	return getHasSpecializedTag<It>(typename It::iterator_category());
}

void assertEqualityOfValuesContainedBySimpleDummyVector(ft::vector<simpleDummy> &x, ft::vector<simpleDummy> &y, size_t forElements){
	ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";

	for (int i = 0; i < forElements; ++i) {
		EXPECT_EQ(*x[i], *y[i]) << "Vectors x and y differ at index " << i;
	}
}


#endif     // TEST_UTILS_H
