//
// Created by fleanegan on 10.09.22.
//

#ifndef CONTAINERS_TYPE_TRAITS_HPP
#define CONTAINERS_TYPE_TRAITS_HPP

#include <limits>


namespace ft{
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

#endif //CONTAINERS_TYPE_TRAITS_HPP
