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


int		main(void)
{
	std::map<int, int, std::__new_allocator<int> > mapS;
	ft::map<int, int, std::__new_allocator<int> > mapSe;
	return (0);
}


#endif