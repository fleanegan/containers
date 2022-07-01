#include <iostream>
#include "IteratorTraits.hpp"
#include "../inc/IteratorTraits.hpp"
#include "../inc/Vector.hpp"
#include "../inc/VectorIterator.hpp"
#include "Utils.hpp"
#include <iterator>
#include <vector>

#ifndef TESTING



int main() {
	ft::vector<int> vec;
	vec.push_back(9);
	ft::vector<int> constVec = vec;

	ft::vector<int>::reverse_iterator revy = vec.rend();
	ft::vector<int>::iterator nonConsty = vec.end();
	ft::vector<int>::const_iterator consty = nonConsty;
	ft::vector<int>::reverse_iterator nonConstRevy = vec.rend();
	ft::vector<int>::const_reverse_iterator constRevy = nonConstRevy;
	nonConstRevy == constRevy;

	std::vector<int> vecS;
	std::vector<int>::iterator tes;
	vecS.push_back(9);
	std::vector<int>::reverse_iterator revSIt = vecS.rbegin();
	std::vector<int>::const_reverse_iterator vecSIt = vecS.rbegin();
	vecSIt == revSIt;

	return (0);
}

#endif