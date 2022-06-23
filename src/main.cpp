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
	ft::vector<int> nonConst;
	nonConst.push_back(8);
	ft::vector<int> tmp;
	tmp.assign(nonConst.begin(), nonConst.end());
	const ft::vector<int> consty(nonConst);

	return (0);
}

#endif