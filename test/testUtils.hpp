#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "gtest/gtest.h"
#include "../inc/Iterators.hpp"
#include "../inc/Vector.hpp"
#include <iostream>

class simpleDummy{
	int *i;
public:
	simpleDummy() : i(new int) {}
	simpleDummy(const simpleDummy & other) : i(new int){}
	simpleDummy &operator=(const simpleDummy &other){
		i = new int;
		return *this;
	}
	void dummyFunction(){}
	~simpleDummy() { delete i; }
};

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
