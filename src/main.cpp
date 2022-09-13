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

//#define STD
#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_prelude.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 20:49:46 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/24 13:27:12 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map.hpp"
#include <cstddef>
#include <functional>
#include <map>
#include <string>


int main()
{

	const ft::map<int, int>map;
	ft::map<int, int>::const_reverse_iterator it = map.rbegin();

	(void) it;
	return (0);
}



#endif