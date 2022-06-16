#include "testUtils.hpp"

TEST(vector, initVectorHasCapacityOne){
	ft::vector<int> vec;

	ASSERT_EQ(1, vec.capacity());
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
	ASSERT_EQ(2 * capacityInital, vec.capacity());
}