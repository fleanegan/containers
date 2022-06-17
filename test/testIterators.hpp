#include "testUtils.hpp"

template <typename T>
class Exp1{
public:
	class Iterator;
	Exp1() : iterator() {}
	Iterator iterator;
};

template <typename T>
class Exp1<T>::Iterator : public TRAIT_NS::iterator_traits_bundle<TRAIT_NS::input_iterator_tag, T, std::ptrdiff_t, T*, T&>{};

template <typename T>
class Exp2{
public:
	class Iterator;
	Exp2() : iterator() {}
	Iterator iterator;
};

template <typename T>
class Exp2<T>::Iterator : public TRAIT_NS::iterator_traits_bundle<TRAIT_NS::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>{};


TEST(iterators, init) {
	Exp2<int> iterableTestObject;
	ASSERT_TRUE(getHasSpecializedTag<Exp2<int>::Iterator>());
}