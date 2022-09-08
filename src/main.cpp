#include <iostream>
#include "IteratorTraits.hpp"
#include "../inc/IteratorTraits.hpp"
#include "../inc/Vector.hpp"
#include "../inc/VectorIterator.hpp"
#include "../inc/RedBlackTree.hpp"
#include "Utils.hpp"
#include <iterator>
#include <vector>
#include <typeinfo>
#include <map>
#include "Stack.hpp"
#include "Pair.hpp"
#include "BinarySearchTree.hpp"
#include "Map.hpp"
#include "MapIterator.hpp"

//#define TESTED_TYPE int
//#ifndef TESTED_NAMESPACE
//#define TESTED_NAMESPACE ft
//#endif

#ifndef TESTING

int main(){
	const ft::map<int, int> map;

	ft::map<int, int>::const_iterator constIt = map.begin();
	(void) constIt;
}




#endif