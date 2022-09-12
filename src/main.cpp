#include <iostream>
#include "iterator_traits.hpp"
#include "../inc/iterator_traits.hpp"
#include "../inc/vector.hpp"
#include "../inc/VectorIterator.hpp"
#include "../inc/RedBlackTree.hpp"
#include <iterator>
#include <vector>
#include <typeinfo>
#include <map>
#include "stack.hpp"
#include "pair.hpp"
#include "BinarySearchTree.hpp"
#include "map.hpp"
#include "MapIterator.hpp"

#define TESTED_TYPE int
#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#ifndef TESTING
#include <vector>
#include <stack>
#include <sstream>
#include "../test/testUtils.hpp"

#define STD
#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

template <typename c>
std::size_t getMax(){
	std::size_t max = c().max_size();
	return max;
}

struct m{
	m(){
		throw std::length_error("tm");
	}
};

int main()
{
//	ft::vector<char> vec(4, '2');
//	std::istringstream str("1 2 3 4 5 6 7");
//	std::istreambuf_iterator<char> it(str), end;
//
//	vec.insert(vec.begin() + 1, it, end);

	ft::vector<char> cv;
	for (int i = 0; i < 20; ++i) {
		cv.insert(cv.begin(), i, i);
	}


	return (0);
}



#endif