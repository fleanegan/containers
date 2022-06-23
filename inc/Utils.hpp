//
// Created by fleanegan on 22.06.22.
//

#ifndef CONTAINERS_UTILS_HPP
#define CONTAINERS_UTILS_HPP

namespace ft{
	template <bool, typename T = void>
	struct enable_if
	{};

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};
}

#endif //CONTAINERS_UTILS_HPP
