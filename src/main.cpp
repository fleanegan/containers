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
	std::vector<int>(getMax<std::vector<int> >() + 1);
	//m awf;
//	ft::vector<int> v(getMax() + 10);
	return (0);
}



#endif