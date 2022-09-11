//
// Created by fleanegan on 10.09.22.
//

#ifndef CONTAINERS_ALGORITHM_HPP
#define CONTAINERS_ALGORITHM_HPP

namespace ft {
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2) {
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class value_type>
	bool equal(value_type const &a, value_type const &b) {
		return (a == b);
	}

	typedef long long ptrdiff_t;
}

#endif //CONTAINERS_ALGORITHM_HPP
