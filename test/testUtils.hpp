#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "gtest/gtest.h"
#include "../inc/iterators.hpp"
#include <iostream>



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
