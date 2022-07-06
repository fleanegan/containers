#ifndef CONTAINERS_ITERATORS_H
#define CONTAINERS_ITERATORS_H

namespace ft {
	typedef long long ptrdiff_t;

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
		typedef ft::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef ft::ptrdiff_t difference_type;
		typedef const T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<typename Category, typename Tp, typename Distance = ptrdiff_t,
			typename Pointer = Tp*, typename Reference = Tp&>
	struct iterator_traits_bundle
	{
		typedef Category  iterator_category;
		typedef Tp        value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
	};
}

#endif //CONTAINERS_ITERATORS_H
