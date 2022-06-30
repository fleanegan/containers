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

TEST(reverseIterator, canDereferenceNormally) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin());

	simpleDummy result = *revIt;

	ASSERT_EQ(*result, **vec.begin());
}

TEST(reverseIterator, advancingReverseIteratorMeansRetreating) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin() + 1);
	ASSERT_EQ(2, **revIt);

	revIt++;

	ASSERT_EQ(**revIt, **vec.begin());
}

TEST(reverseIterator, baseIteratorIsNotReverse) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin());
	ft::vector<simpleDummy>::iterator forwIt = revIt.base();

	forwIt++;

	ASSERT_EQ(**forwIt, **(vec.begin() + 1)	);
}

TEST(reverseIterator, postAndPrefixIncrementing) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin());

	ASSERT_EQ(**(revIt--), **(vec.begin()));
	ASSERT_EQ(**(++revIt), **(vec.begin()));
}


// todo: reverseIteratorWithInputIteratorDoesNotCallAnyNonExistingFunctions