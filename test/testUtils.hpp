#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "gtest/gtest.h"
#include "../inc/IteratorTraits.hpp"
#include "../inc/Vector.hpp"
#include "../inc/VectorIterator.hpp"
#include <iostream>

struct simpleDummy {
	int *i = NULL;

	simpleDummy() {
		_DEBUG && std::cout << "default constructor" << std::endl;
		i = new int;
	}

	explicit simpleDummy(int in) {
		_DEBUG && std::cout << "argument constructor. i is " << (void *) i << std::endl;
		i = new int;
		*i = in;
	}

	simpleDummy(const simpleDummy &other) {
		_DEBUG && std::cout << "copy constructor. i is " << (void *) i << std::endl;
		i = new int;
		*i = *(other.i);
	}

	simpleDummy &operator=(const simpleDummy &other) {
		_DEBUG && std::cout << "assignment start" << std::endl;
		*i = *(other.i);
		_DEBUG && std::cout << "assignment end" << std::endl;
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
		_DEBUG && std::cout << "destructor" << std::endl;
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

template<typename It>
bool getHasSpecializedTag(TRAIT_NS::bidirectional_iterator_tag a) {
	_DEBUG && std::cout << "specialized function called" << std::endl;
	return true;
}

template<typename It>
bool getHasSpecializedTag(TRAIT_NS::input_iterator_tag a) {
	_DEBUG && std::cout << "generalized function called" << std::endl;
	return false;
}

template<typename It>
bool getHasSpecializedTag() {
	return getHasSpecializedTag<It>(typename It::iterator_category());
}

#endif     // TEST_UTILS_H
