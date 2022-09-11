//
// Created by fleanegan on 10.09.22.
//

#ifndef CONTAINERS_ITERATOR_HPP
#define CONTAINERS_ITERATOR_HPP

#include <cstddef>

namespace ft{
	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef std::ptrdiff_t difference_type;
		typedef const T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<typename Category, typename Tp, typename Distance = std::ptrdiff_t,
			typename Pointer = Tp*, typename Reference = Tp&>
	struct iterator_traits_bundle
	{
		typedef Category  iterator_category;
		typedef Tp        value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
	};

	template<typename It>
	typename ft::iterator_traits<It>::difference_type
	distance (It first, It last, std::input_iterator_tag){
		typename ft::iterator_traits<It>::difference_type result = 0;

		while (first != last){
			++first;
			++result;
		}
		return result;
	}

	template<typename It>
	typename ft::iterator_traits<It>::difference_type
	distance (It first, It last, std::random_access_iterator_tag){
		return (last - first);
	}

	template<typename  It>
	typename ft::iterator_traits<It>::difference_type
	distance (It first, It last){
		return ft::distance<It>(first, last, typename ft::iterator_traits<It>::iterator_category());
	}
}

#endif //CONTAINERS_ITERATOR_HPP
