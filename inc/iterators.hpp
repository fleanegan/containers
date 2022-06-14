//
// Created by fschlute on 6/14/22.
//

#ifndef CONTAINERS_ITERATORS_H
#define CONTAINERS_ITERATORS_H

namespace ft {
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	typedef unsigned long ptrdiff_t;
	//general
	template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
			typename _Pointer = _Tp*, typename _Reference = _Tp&>
	struct iterator
	{
		typedef _Category  iterator_category;
		typedef _Tp        value_type;
		typedef _Distance  difference_type;
		typedef _Pointer   pointer;
		typedef _Reference reference;
	};
}

#ifdef COMPAT_MODE
#else
#endif

#endif //CONTAINERS_ITERATORS_H
