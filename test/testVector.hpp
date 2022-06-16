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
	std::cout << "end of test" << std::endl;
}

TEST(vector, canModifyResultOfBracketOperator){
	ft::vector<int> vec;

	vec.push_back(2);
	vec.push_back(3);
	++vec[1];
	ASSERT_EQ(4, vec[1]);
}

#include <vector>

TEST(vector, canGetConstBracketOperator){
	const ft::vector<int> vec(1);

	const int i = vec[0];
	ASSERT_EQ(0, i);
}