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

	std::vector<int> vecS;
	std::vector<int>::iterator tes;
	vecS.push_back(9);
	std::vector<int>::const_reverse_iterator vecSIt = vecS.rbegin();

	return (0);
}

#endif