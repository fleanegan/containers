//
// Created by fleanegan on 22.06.22.
//

#ifndef CONTAINERS_UTILS_HPP
#define CONTAINERS_UTILS_HPP

#include <limits>

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

	template <class T, T v>
	struct integral_constant {
		static constexpr T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		constexpr operator T() { return v; }
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <bool, typename T = void>
	struct enable_if
	{};

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template<class T> struct is_const          : std::false_type {};
	template<class T> struct is_const<const T> : std::true_type {};

	template <typename T>
	struct is_integral
	{
		static const bool value;
	};

	template <typename T>
	const bool is_integral<T>::value = std::numeric_limits<T>::is_integer;
}

#endif //CONTAINERS_UTILS_HPP
