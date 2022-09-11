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

#define STD
#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

int main()
{
	ft::vector<std::string> str(235, "Test");

	ft::vector<int> tes;
	ft::vector<int>::iterator tesIt = tes.begin();
	ft::distance(tes.begin(), tes.end());
	NAMESPACE::stack<float> other_stack;
	NAMESPACE::vector<std::string> lst;

	lst.push_back("salut");
	lst.push_back("tu vas bien?");
	lst.push_back("super");
	lst.push_back("et toi?");

	NAMESPACE::stack<std::string, vector<std::string> >	my_stack(lst);

	std::cout << std::boolalpha << other_stack.empty() << std::endl;
	other_stack.push(8.5); // 8.5;
	other_stack.push(42.4242); // 8.5; 42.4242;
	std::cout << other_stack.size() << '\n'; // 2
	other_stack.pop(); // 8.5;
	std::cout << other_stack.size() << '\n'; // 1
	other_stack.push(78541.987); // 8.5; 78541.987;
	std::cout << other_stack.size() << '\n'; // 2
	std::cout << other_stack.top() << '\n'; //78541.987
	std::cout << std::boolalpha << other_stack.empty() << std::endl;

	const std::string const_top = my_stack.top();

	std::cout << "const top: " << const_top << '\n';

	while (!my_stack.empty())
	{
		std::cout << my_stack.top() << '\n';
		my_stack.pop();
	}

	return (0);
}



#endif