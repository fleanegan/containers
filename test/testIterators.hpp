#include "testUtils.hpp"

template <typename T>
class Exp1{
public:
	class Iterator : public TRAIT_NS::iterator<TRAIT_NS::input_iterator_tag, T, std::ptrdiff_t, T*, T&>{

	};
	Exp1() : iterator() {}

	Iterator iterator;
};

template <typename T>
class Exp2{
public:
	class Iterator : public TRAIT_NS::iterator<TRAIT_NS::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>{

	};
	Exp2() : iterator() {}

	Iterator iterator;
};

TEST(iterators, init) {
	Exp2<int> iterableTestObject;
	ASSERT_TRUE(getHasSpecializedTag<Exp2<int>::Iterator>());
}