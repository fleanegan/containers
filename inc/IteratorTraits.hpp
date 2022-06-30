#ifndef CONTAINERS_ITERATORS_H
#define CONTAINERS_ITERATORS_H

#ifdef USE_STD_TRAITS
# define TRAIT_NS std
#else
# define TRAIT_NS std
#endif

namespace ft {
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	typedef long ptrdiff_t;

	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
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
