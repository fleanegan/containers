#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "gtest/gtest.h"
#include "../inc/IteratorTraits.hpp"
#include "../inc/Vector.hpp"
#include "../inc/VectorIterator.hpp"
#include <iostream>

struct simpleDummy{
	int *i;

	simpleDummy() : i(new int) {}

	explicit simpleDummy(int in) : i(new int) { *i = in; }

	simpleDummy(const simpleDummy & other) : i(new int){ *i = *other.i; }

	bool operator==(const simpleDummy &rhs) const {
		return i == rhs.i;
	}

	bool operator!=(const simpleDummy &rhs) const {
		return !(rhs == *this);
	}

	simpleDummy &operator=(const simpleDummy &other){
		i = new int;
		*i = *other.i;
		return *this;
	}

	int &operator*(){
		return *i;
	}

	void dummyFunction(){}

	~simpleDummy() { delete i; }
};

ft::vector<simpleDummy> createTestDumyVector(){
	ft::vector<simpleDummy> result;
	for (int i = 1; i < 6; ++i) {
		result.push_back(simpleDummy(i));
	}
	return result;
}

template <typename It>
bool getHasSpecializedTag(TRAIT_NS::bidirectional_iterator_tag a){
	std::cout << "specialized function called" << std::endl;
	return true;
}

template <typename It>
bool getHasSpecializedTag(TRAIT_NS::input_iterator_tag a){
	std::cout << "generalized function called" << std::endl;
	return false;
}

template <typename It>
bool getHasSpecializedTag(){
	return getHasSpecializedTag<It>(typename It::iterator_category());
}

#endif	 // TEST_UTILS_H
