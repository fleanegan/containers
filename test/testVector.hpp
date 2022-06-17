#include "testUtils.hpp"

TEST(vector, initVectorHasCapacityZero){
	ft::vector<int> vec;

	ASSERT_EQ(0, vec.capacity());
}

TEST(vector, push_backIncreasesSize){
	ft::vector<int> vec;
	size_t sizeInital = vec.size();

	vec.push_back(2);
	ASSERT_GT(vec.size(), sizeInital);
}

TEST(vector, canAccessStoredElementAtFront){
	ft::vector<int> vec;
	int elementToStore = 2;

	vec.push_back(elementToStore);

	int retrievedElement = vec.front();
	ASSERT_EQ(retrievedElement, elementToStore);
}

TEST(vector, exceedingCapacityOnPush_backDoublesSize){
	ft::vector<int> vec;
	size_t capacityInital = vec.capacity();

	vec.push_back(2);
	vec.push_back(2);
	vec.push_back(2);
	ASSERT_EQ(4, vec.capacity());
}

TEST(vector, properDestruction){
	ft::vector<simpleDummy> vec;

	simpleDummy a;
	vec.push_back(a);
	vec.push_back(a);

	simpleDummy res = vec.front();
	res.dummyFunction();
}

TEST(vector, canModifyResultOfBracketOperator){
	ft::vector<int> vec;

	vec.push_back(2);
	++vec[0];
	ASSERT_EQ(3, vec[0]);
}

TEST(vector, canGetConstBracketOperator){
	const ft::vector<int> vec(1);

	const int i = vec[0];
	ASSERT_EQ(0, i);
}

TEST(vector, atGetsElementIfValidAccessor){
	ft::vector<int> vec(1);

	vec.at(0) = 9;
	const int result = vec.at(0);

	ASSERT_EQ(9, result);
}

TEST(vector, atGetsElementIfValidAccessorConst){
	const ft::vector<int> vec(1);

	const int result = vec.at(0);

	ASSERT_EQ(0, result);
}

TEST(vector, atThrowsIfOutOfRange){
	ft::vector<int> vec(1);

	ASSERT_ANY_THROW(vec.at(1));
}

TEST(vector, atThrowsIfOutOfRangeConst){
	const ft::vector<int> vec(1);

	ASSERT_ANY_THROW(vec.at(1));
}

TEST(vector, iteratorBeginPointsAtFirstElement){
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));

	ASSERT_EQ(vec.front(), *vec.begin());
}

TEST(vector, iteratorEndPointsBehindLastElement){
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));
	vec.push_back(simpleDummy(1));

	ASSERT_EQ(vec.back(), *(--vec.end()));
}

TEST(vector, clearResetsSize){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ASSERT_NE(0, vec.size());

	vec.clear();

	ASSERT_EQ(0, vec.size());
	ASSERT_EQ(0, vec.capacity());
}

TEST(vector, reserveGreaterThanMaxSizeThrows){
	ft::vector<simpleDummy> vec;

	ASSERT_ANY_THROW(vec.reserve(-1));
}


TEST(vector, assignPutsElementsFromToIntoVecModifyingTheCapacityAsNecessary){
	ft::vector<int> source;
	source.push_back(1);
	source.push_back(1);
	source.push_back(1);
	ft::vector<int> vec;

	vec.assign(source.begin(), source.end());
	ASSERT_EQ(3, vec.size());
	ASSERT_EQ(vec, source);
}


//TEST(vector, assignmentMakesDeep){
//	ft::vector<simpleDummy> source;
//	ft::vector<simpleDummy> target;
//	source.push_back(simpleDummy());
//
//	target = source;
//
//	ASSERT_EQ(source.size(), target.size());
//	ASSERT_EQ(source.capacity(), target.capacity());
//	ASSERT_EQ(*source.front().i, *target.front().i);
//	ASSERT_NE(source.front().i, target.front().i);
//}