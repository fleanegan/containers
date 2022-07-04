#include "testUtils.hpp"

TEST(vector, initVectorHasCapacityZero) {
	ft::vector<int> vec;

	ASSERT_EQ(0, vec.capacity());
}

TEST(vector, push_backIncreasesSize) {
	ft::vector<int> vec;
	size_t sizeInital = vec.size();

	vec.push_back(2);
	ASSERT_GT(vec.size(), sizeInital);
}

TEST(vector, canAccessStoredElementAtFront) {
	ft::vector<int> vec;
	int elementToStore = 2;

	vec.push_back(elementToStore);

	int retrievedElement = vec.front();
	ASSERT_EQ(retrievedElement, elementToStore);
}

TEST(vector, exceedingCapacityOnPush_backDoublesSize) {
	ft::vector<int> vec;
	size_t capacityInital = vec.capacity();

	vec.push_back(2);
	vec.push_back(2);
	vec.push_back(2);
	ASSERT_EQ(4, vec.capacity());
}

TEST(vector, properDestruction) {
	ft::vector<simpleDummy> vec;

	simpleDummy a;
	vec.push_back(a);
	vec.push_back(a);

	simpleDummy res = vec.front();
	res.dummyFunction();
}

TEST(vector, canModifyResultOfBracketOperator) {
	ft::vector<int> vec;

	vec.push_back(2);
	++vec[0];
	ASSERT_EQ(3, vec[0]);
}

TEST(vector, canGetConstBracketOperator) {
	const ft::vector<int> vec(1);

	const int i = vec[0];
	ASSERT_EQ(0, i);
}

TEST(vector, atGetsElementIfValidAccessor) {
	ft::vector<int> vec(1);

	vec.at(0) = 9;
	const int result = vec.at(0);

	ASSERT_EQ(9, result);
}

TEST(vector, atGetsElementIfValidAccessorConst) {
	const ft::vector<int> vec(1);

	const int result = vec.at(0);

	ASSERT_EQ(0, result);
}

TEST(vector, atThrowsIfOutOfRange) {
	ft::vector<int> vec(1);

	ASSERT_ANY_THROW(vec.at(1));
}

TEST(vector, atThrowsIfOutOfRangeConst) {
	const ft::vector<int> vec(1);

	ASSERT_ANY_THROW(vec.at(1));
}

TEST(vector, iteratorBeginPointsAtFirstElement) {
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));

	ASSERT_EQ(vec.front(), *vec.begin());
}

TEST(vector, iteratorEndPointsBehindLastElement) {
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));
	vec.push_back(simpleDummy(1));
	vec.push_back(simpleDummy(1));
	vec.push_back(simpleDummy(1));
	vec.push_back(simpleDummy(1));

	ASSERT_EQ(vec.back(), *(--vec.end()));
}

TEST(vector, clearResetsSize) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ASSERT_NE(0, vec.size());

	vec.clear();

	ASSERT_EQ(0, vec.size());
	ASSERT_EQ(0, vec.capacity());
}

TEST(vector, reserveGreaterThanMaxSizeThrows) {
	ft::vector<simpleDummy> vec;

	ASSERT_ANY_THROW(vec.reserve(-1));
}

TEST(vector, emptyVectorsAreEqual){
	ft::vector<int> vec;

	ASSERT_TRUE(vec == vec);
}

TEST(vector, equalityOfTwoVectorsTrue) {
	ft::vector<int> source;
	source.push_back(1);
	ft::vector<int> vec(source);

	ASSERT_TRUE(vec == source);
	ASSERT_FALSE(vec != source);
	ASSERT_FALSE(vec < source);
	ASSERT_FALSE(vec > source);
}

TEST(vector, equalityOfTwoVectorsFalse) {
	ft::vector<int> source;
	source.push_back(1);
	ft::vector<int> vec(source);
	source.push_back(3);

	ASSERT_TRUE(vec != source);
	ASSERT_FALSE(vec == source);
}

TEST(vector, aVectorWithLessElementsIsShorter) {
	ft::vector<int> a;
	a.push_back(1);
	ft::vector<int> b(a);
	b.push_back(3);

	ASSERT_TRUE(a < b);
	ASSERT_TRUE(b > a);
}

TEST(vector, vectorsWithSameLengthAreLexicallyCompared) {
	ft::vector<int> a;
	a.push_back(1);
	ft::vector<int> b(a);
	b.push_back(3);
	b.push_back(1);
	a.push_back(2);
	a.push_back(1);

	ASSERT_TRUE(a < b);
	ASSERT_TRUE(b > a);
}

TEST(vector, assignPutsElementsFromToIntoVecModifyingTheCapacityAsNecessary) {
	ft::vector<int> source;
	source.push_back(1);
	source.push_back(1);
	source.push_back(1);
	ft::vector<int> vec;

	vec.assign(source.begin(), source.end());
	ASSERT_EQ(3, vec.size());
	ASSERT_EQ(vec, source);
}

TEST(vector, assignmentMakesDeepCopy) {
	ft::vector<simpleDummy> source;
	ft::vector<simpleDummy> target;
	source.push_back(simpleDummy(0));

	target = source;

	ASSERT_EQ(source.size(), target.size());
	ASSERT_EQ(source.capacity(), target.capacity());
	ASSERT_EQ(*source.front().i, *target.front().i);
	ASSERT_NE(source.front().i, target.front().i);
}

TEST(vector, assignResetsSizes) {
	simpleDummy i(1);
	ft::vector<simpleDummy> vec;
	vec.push_back(i);
	vec.push_back(i);

	vec.assign(3, i);

	ASSERT_EQ(3, vec.size());
	ASSERT_EQ(*(vec[0]), 1);
}

TEST(vector, erasingSingleElementDecrementsSize) {
	ft::vector<simpleDummy> vec = createTestDummyVector();

	vec.erase(vec.begin() + 1);

	ASSERT_EQ(4, vec.size());
	ASSERT_EQ(*(vec[0]), 1);
}

TEST(vector, erasingMovesRest) {
	ft::vector<simpleDummy> vec = createTestDummyVector();

	vec.erase(vec.begin());

	ASSERT_EQ(4, vec.size());
	ASSERT_EQ(*(vec[0]), 2);
}

TEST(vector, eraseReturnsIteratorToNextElementAfterDeleted) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	int secondElement = *vec[1];

	ft::vector<simpleDummy>::iterator result = vec.erase(vec.begin());

	ASSERT_EQ(**result, secondElement);
}

TEST(vector, eraseRangeRemovesMultipleElements) {
	ft::vector<simpleDummy> vec = createTestDummyVector();

	vec.erase(vec.begin(), vec.end() - 1);

	ASSERT_EQ(1, vec.size());
	ASSERT_EQ(5, *vec[0]);
}

TEST(vector, eraseRangeInMiddleDoesNotRemoveTail) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ASSERT_EQ(5, vec.size());

	vec.erase(vec.begin() + 1, vec.begin() + 4);

	ASSERT_EQ(2, vec.size());
	ASSERT_EQ(1, *vec[0]);
	ASSERT_EQ(5, *vec[1]);
}

TEST(vector, erasingEmptyRangeIsNoOp) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	size_t sizeOriginal = vec.size();

	vec.erase(vec.begin(), vec.begin());

	ASSERT_EQ(sizeOriginal, vec.size());
}

TEST(vector, insertingChangesCapacityIfNecessary) {
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));
	simpleDummy element(-1);
	size_t originalCapacity = vec.capacity();

	vec.insert(vec.begin(), element);

	ASSERT_LT(originalCapacity, vec.capacity());
}

TEST(vector, insertingDoesNotChangeTheCapacityIfNotNecessary) {
	ft::vector<simpleDummy> vec;
	vec.reserve(1);
	size_t originalCapacity = vec.capacity();
	simpleDummy element(-1);

	vec.insert(vec.begin(), element);

	ASSERT_EQ(originalCapacity, vec.capacity());
}

TEST(vector, insertingBeforeBeginPutsElementInTheFront) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	simpleDummy element(-1);
	size_t originalCapacity = vec.capacity();

	vec.insert(vec.begin(), element);

	ASSERT_EQ(*vec.front(), *element);
}

TEST(vector, insertingInTheMiddleReturnsIteratorToNewElement) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	simpleDummy element(-1);
	size_t originalCapacity = vec.capacity();

	ft::vector<simpleDummy>::iterator result = vec.insert(vec.begin() + 1, element);

	ASSERT_EQ(**result, *element);
	ASSERT_EQ(*result, *(vec.begin() + 1));
}

TEST(vector, insertingAtTheEndWithFreeCapacityDoesNotMoveTheRest) {
	ft::vector<simpleDummy> vec;
	vec.reserve(3);
	simpleDummy element(-1);

	vec.insert(vec.begin(), element);
	vec.insert(vec.end(), element);

	ASSERT_EQ(vec[0].moves, vec[1].moves);
	ASSERT_EQ(-1, *vec[1]);
}

TEST(vector, insertingNElementsInEmptyListUpdatesCapacity) {
	ft::vector<simpleDummy> vec;
	simpleDummy element(-1);
	ASSERT_EQ(0, vec.capacity());

	vec.insert(vec.begin(), 2, element);
	ASSERT_GE(vec.capacity(), 2);
}

TEST(vector, insertingNElementsAddsCopiesToArray) {
	ft::vector<simpleDummy> vec;
	simpleDummy element(-1);

	int count = 2;
	vec.insert(vec.begin(), count, element);
	ASSERT_EQ(*element, *vec[0]);
	ASSERT_EQ(*element, *vec[1]);
	ASSERT_EQ(count, vec.size());
}

TEST(vector, existingElementsAreNotOverwrittenByInsert) {
	ft::vector<simpleDummy> vec = createTestDummyVector();
	EXPECT_EQ(1, *vec[0]);
	EXPECT_EQ(2, *vec[1]);
	EXPECT_EQ(3, *vec[2]);
	EXPECT_EQ(4, *vec[3]);
	EXPECT_EQ(5, *vec[4]);
	EXPECT_EQ(5, vec.size());
	simpleDummy element(-1);

	vec.insert(vec.begin() + 1, 2, element);
	ASSERT_EQ(1, *vec[0]);
	ASSERT_EQ(*element, *vec[1]);
	ASSERT_EQ(*element, *vec[2]);
	EXPECT_EQ(2, *vec[3]);
	EXPECT_EQ(3, *vec[4]);
	EXPECT_EQ(4, *vec[5]);
	EXPECT_EQ(5, *vec[6]);
}

TEST(vector, insertingRangeInEmptyVectorDoesTheSameThingThanAssign) {
	ft::vector<simpleDummy> source = createTestDummyVector();
	ft::vector<simpleDummy> target;

	target.insert(target.begin(), source.begin(), source.end());

	assertEqualityOfValuesContainedBySimpleDummyVector(source, target, source.size());
	ASSERT_EQ(source.size(), target.size());
}

TEST(vector, swapChangesSizeCapacityAndArr) {
	ft::vector<simpleDummy> a = createTestDummyVector();
	ft::vector<simpleDummy> b;
	b.push_back(simpleDummy(9));
	size_t bSizeOriginal = b.size();
	size_t aSizeOriginal = a.size();
	size_t bCapacityOriginal = b.capacity();
	size_t aCapacityOriginal = a.capacity();

	b.swap(a);

	ASSERT_EQ(aSizeOriginal, b.size());
	ASSERT_EQ(bSizeOriginal, a.size());
	ASSERT_EQ(aCapacityOriginal, b.capacity());
	ASSERT_EQ(bCapacityOriginal, a.capacity());
	ASSERT_EQ(9, *a[0]);
	ASSERT_EQ(1, *b[0]);
	ASSERT_EQ(2, *b[1]);
}

TEST(vector, usingResizeToEnlargeVectorInitializesNewElements) {
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));

	vec.resize(2, simpleDummy(2));

	ASSERT_EQ(1, *vec[0]);
	ASSERT_EQ(2, *vec[1]);
}

TEST(vector, resizingToSmallerThanSizeDestroysOnlyOtherElements) {
	ft::vector<simpleDummy> vec = createTestDummyVector();

	vec.resize(4, simpleDummy(2));

	ASSERT_EQ(4, vec.size());
}

TEST(vector, usingResizeWithEqualSizeDoesNothing) {
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));

	vec.resize(1, simpleDummy(2));

	ASSERT_EQ(1, vec.size());
}

TEST(vector, vectorWithoutElementsIsEmpty) {
	ft::vector<simpleDummy> vec;

	ASSERT_EQ(true, vec.empty());
}

TEST(vector, vectorWithElementsIsNotEmpty) {
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));

	ASSERT_EQ(false, vec.empty());
}

TEST(vector, canAssignFromConst) {
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));
	const ft::vector<simpleDummy> consty(vec);

	ASSERT_EQ(false, consty.empty());
}

TEST(vector, constructFromIterator) {
	ft::vector<int> vec;
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(2);

	ft::vector<int> result(vec.begin(), vec.end());

	ASSERT_EQ(vec, result);
}

TEST(vector, getReverseIterator) {
	ft::vector<simpleDummy> vec = createTestDummyVector();

	ft::vector<simpleDummy>::reverse_iterator revy = vec.rend();
	ft::vector<simpleDummy>::const_iterator nonConsty = vec.end();
	ft::vector<simpleDummy>::const_reverse_iterator constRevy = vec.rbegin();
}

TEST(vector, subtractNonConstAndConstReverseIterators) {
	ft::vector<simpleDummy> vec = createTestDummyVector();

	ft::vector<simpleDummy>::reverse_iterator revy = vec.rend();
	ft::vector<simpleDummy>::const_iterator constRevy = vec.end();
	ASSERT_EQ(0, constRevy - revy);
}

TEST(vector, useInputIteratorForAssign) {
	ft::vector<simpleDummy> source = createTestDummyVector();
	StupidInputIterator<simpleDummy> from(source.begin().current());
	StupidInputIterator<simpleDummy> to(source.end().current());
	ft::vector<simpleDummy> target;

	target.insert(target.begin(), from, to);

	ASSERT_EQ(**target.begin(), **source.begin());
	ASSERT_EQ(**--target.end(), **--source.end());
}

// canCompareWithConst
// insertBeforeBeginDoes?????
// insertAfterEndDoes?????
