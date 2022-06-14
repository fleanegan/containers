#include <iostream>
#include "iterators.hpp"
#include "../inc/iterators.hpp"
#include <iterator>
#include <vector>

#ifndef TESTING


template <typename T>
class Exp1{
public:
	class Iterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T&>{

	};
	Exp1() : iterator() {}

	Iterator iterator;
};

template <typename T>
class Exp2{
public:
	class Iterator : public std::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>{

	};
	Exp2() : iterator() {}

	Iterator iterator;
};

template <typename It>
void foo(It &it, std::bidirectional_iterator_tag){
	std::cout << "specialized function called" << std::endl;
	(void) it;
}

template <typename It>
void foo(It &it, std::input_iterator_tag){
	std::cout << "generalized function called" << std::endl;
	(void) it;
}

template <typename It>
void foo(It it){
	foo<It>(it, typename It::iterator_category());
}

int	main(){
	std::vector<int> v;
	Exp1<int> objectWithWeakIterator;
	Exp2<int> objectWithStrongIterator;
	foo<Exp1<int>::Iterator>(objectWithWeakIterator.iterator); // will call the specialized version
	foo<Exp2<int>::Iterator>(objectWithStrongIterator.iterator); // will call the specialized version
	foo<std::vector<int>::iterator>(v.begin());  // works with vector as well!
	return (0);
}

#endif