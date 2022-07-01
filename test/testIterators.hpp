#include "testUtils.hpp"

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

TEST(reverseIterator, compareConstReverseIteratorAgainstNonConstReverseIterator) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt = vec.rbegin();
	ReverseIterator<const ft::vector<simpleDummy>::iterator> constRevIt = vec.rbegin();

	ASSERT_EQ(constRevIt, revIt);
}

TEST(ftDistance, useRandomAccessIterator){
	ft::vector<simpleDummy> vec = createTestDummyVector();

	ft::ptrdiff_t result = TRAIT_NS::distance(vec.begin(), vec.end());

	ASSERT_EQ(5, result);
}

TEST(ftDistance, useInputIterator){
	ft::vector<simpleDummy> vec = createTestDummyVector();

	ft::ptrdiff_t result = TRAIT_NS::distance(StupidInputIterator(&*vec.begin()), StupidInputIterator(&*vec.end()));

	ASSERT_EQ(5, result);
}

// todo: reverseIteratorWithInputIteratorDoesNotCallAnyNonExistingFunctions