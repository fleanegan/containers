#ifndef CONTAINERS_ITERATORS_H
#define CONTAINERS_ITERATORS_H

#ifdef USE_STD_TRAITS
# define TRAIT_NS std
#else
# define TRAIT_NS ft
#endif

namespace ft {
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	typedef unsigned long ptrdiff_t;
	template<typename Category, typename Tp, typename Distance = ptrdiff_t,
			typename Pointer = Tp*, typename Reference = Tp&>
	struct iterator
	{
		typedef Category  iterator_category;
		typedef Tp        value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
	};
}

#ifdef COMPAT_MODE
#else
#endif

#endif //CONTAINERS_ITERATORS_H
