#include "testUtils.hpp"

#define REVERSE_ITERATOR_OFFSET 1
TEST(reverseIterator, canDereferenceNormally) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin() + REVERSE_ITERATOR_OFFSET);

	simpleDummy result = *revIt;

	ASSERT_EQ(*result, **vec.begin());
}

TEST(reverseIterator, advancingReverseIteratorMeansRetreating) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin() + REVERSE_ITERATOR_OFFSET + 1);
	ASSERT_EQ(2, **revIt);

	revIt++;

	ASSERT_EQ(**revIt, **vec.begin());
}

TEST(reverseIterator, isMisalignedOnPurpose) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator forwIt = vec.begin() + REVERSE_ITERATOR_OFFSET;
	ft::vector<simpleDummy>::reverse_iterator revIt(forwIt);

	ASSERT_EQ(1, **revIt);
	ASSERT_EQ(2, *(*revIt.base()));
}

TEST(reverseIterator, baseIteratorIsNotReverse) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin());
	ft::vector<simpleDummy>::iterator forwIt = revIt.base();
	int before = **forwIt;

	++forwIt;

	int after = **forwIt;
	ASSERT_GT(after, before);
}

TEST(reverseIterator, postAndPrefixIncrementing) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin() + REVERSE_ITERATOR_OFFSET);

	ASSERT_EQ(**(revIt--), **(vec.begin()));
	ASSERT_EQ(**(++revIt), **(vec.begin()));
}

TEST(reverseIterator, accessingByIndexIsInversed){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.rbegin());

	ASSERT_EQ(4, **(revIt += 1));
}

TEST(reverseIterator, compareConstReverseIteratorAgainstNonConstReverseIterator) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt = vec.rbegin();
	ReverseIterator<const ft::vector<simpleDummy>::iterator> constRevIt = vec.rbegin();

	ASSERT_EQ(constRevIt, revIt);
}

TEST(reverseIterator, movingIteratorTo) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt = vec.rbegin();


	simpleDummy baseOperatorResult = *(revIt.base().operator-(1));
	simpleDummy operatorResult = *(revIt + 1);

	ASSERT_EQ(*baseOperatorResult, *operatorResult + REVERSE_ITERATOR_OFFSET);
}

TEST(reverseIterator, plusEqualDecrements) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt = vec.rbegin();

	ASSERT_EQ(3, **(revIt += 2));
}

TEST(reverseIterator, minusEqualIncrements) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin());

	ASSERT_EQ(2, **(revIt -= 2));
}

TEST(reverseIterator, distanceBetweenTwoReverseIteratorsIsNegative) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin());
	ReverseIterator<ft::vector<simpleDummy>::iterator> revItEnd(vec.end());

	ASSERT_LT(revItEnd - revIt, 0);
}

TEST(reverseIterator, numberPlusIteratorReturnsNegativeDistance) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin());

	ASSERT_EQ(2, **(-2 + revIt));
}

TEST(reverseIterator, movingIteratorBackwards) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ReverseIterator<ft::vector<simpleDummy>::iterator> revIt(vec.begin() + 2);

	simpleDummy baseOperatorResult = *(revIt.base().operator+(1));
	simpleDummy operatorResult = *(revIt - 1);

	ASSERT_EQ(*baseOperatorResult, *operatorResult + REVERSE_ITERATOR_OFFSET);
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

template<typename T, typename U>
void foo(T it, U ite){
	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;
	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
}

TEST(reverseIterator, accessorOperator){
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(42));
	ft::vector<simpleDummy>::reverse_iterator revIt(vec.begin() + 1);

	int result = *revIt[0];

	ASSERT_EQ(**vec.begin(), result);
}

TEST(reverseIterator, equalityOfReverseAndNormalIterator) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	std::vector<simpleDummy> vecS;
	vecS.push_back(simpleDummy(2));

	std::vector<simpleDummy>::iterator itS = vecS.end();
	std::vector<simpleDummy>::reverse_iterator revItS(itS);
	ft::vector<simpleDummy>::iterator it = vec.end();
	ft::vector<simpleDummy>::reverse_iterator revIt(it);

	ASSERT_EQ(it, revIt);
}
// todo: reverseIteratorWithInputIteratorDoesNotCallAnyNonExistingFunctions

