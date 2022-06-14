#include <iostream>
#include "iterators.hpp"
#include "../inc/iterators.hpp"
#include <iterator>
#include <vector>

#ifndef TESTING


template <typename T>
class Exp1{
public:
	class Iterator : public ft::iterator<ft::input_iterator_tag, T, std::ptrdiff_t, T*, T&>{

	};
	Exp1() : iterator() {}

	Iterator iterator;
};

template <typename T>
class Exp2{
public:
	class Iterator : public ft::iterator<ft::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>{

	};
	Exp2() : iterator() {}

	Iterator iterator;
};

template <typename It>
void foo(It &it, ft::bidirectional_iterator_tag){
	std::cout << "specialized function called" << std::endl;
	(void) it;
}

template <typename It>
void foo(It &it, ft::input_iterator_tag){
	std::cout << "generalized function called" << std::endl;
	(void) it;
}

template <typename It>
void foo(It it){
	foo<It>(it, typename It::iterator_category());
}

int	main(){
	std::vector<int> v(2,3);
	Exp1<int> objectWithWeakIterator;
	Exp2<int> objectWithStrongIterator;
	foo<Exp1<int>::Iterator>(objectWithWeakIterator.iterator); // will call the specialized version
	foo<Exp2<int>::Iterator>(objectWithStrongIterator.iterator); // will call the specialized version
	return (0);
}

#endif