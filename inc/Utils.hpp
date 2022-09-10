//
// Created by fleanegan on 22.06.22.
//

#ifndef CONTAINERS_UTILS_HPP
#define CONTAINERS_UTILS_HPP

#include <limits>
#include "IteratorTraits.hpp"

namespace ft{
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

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
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

	template <bool, typename T = void>
	struct enable_if
	{};

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template <typename T>
	struct is_integral
	{
		static const bool value;
	};

	template <typename T>
	const bool is_integral<T>::value = std::numeric_limits<T>::is_integer;


	template<typename T>
	struct less: public std::binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const {
			return (x < y);
		}
	};

	template<typename T>
	struct more: public std::binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const {
			return (x > y);
		}
	};

	template<class value_type>
	value_type const &min(value_type const &a, value_type const &b) {
		return (a < b ? a : b);
	}

	template<class value_type>
	value_type const &max(value_type const &a, value_type const &b) {
		return (a < b ? b : a);
	}

	template<class value_type>
	bool equal(value_type const &a, value_type const &b) {
		return (a == b);
	}
}

#endif //CONTAINERS_UTILS_HPP
