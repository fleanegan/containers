#include <iostream>
#include "IteratorTraits.hpp"
#include "../inc/IteratorTraits.hpp"
#include "../inc/Vector.hpp"
#include "../inc/VectorIterator.hpp"
#include "Utils.hpp"
#include <iterator>
#include <vector>

#ifndef TESTING

template <typename T>
typename ft::enable_if<ft::is_integral<T>::value, void>::type foo(T in ){
	std::cout << "is integral" << std::endl;
	(void) in;
}

template <typename T>
typename ft::enable_if<!ft::is_integral<T>::value, void>::type foo(T in ){
	std::cout << "is class" << std::endl;
	(void) in;
}


int main() {
	ft::vector<char> it;
	foo(it);
	foo(3);

	return (0);
}

#endif