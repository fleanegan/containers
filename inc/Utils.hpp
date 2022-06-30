//
// Created by fleanegan on 22.06.22.
//

#ifndef CONTAINERS_UTILS_HPP
#define CONTAINERS_UTILS_HPP

#include <limits>

namespace ft{
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last, ft::input_iterator_tag){
		typename InputIterator::difference_type result = 0;

		while (first != last){
			++first;
			++result;
		}
		return result;
	}

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last, ft::random_access_iterator_tag){
		return (last - first);
	}

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last){
		return TRAIT_NS::distance(first, last, typename InputIterator::iterator_category());
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
}

#endif //CONTAINERS_UTILS_HPP
