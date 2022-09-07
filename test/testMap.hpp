#include "testUtils.hpp"

TEST(Map, insertingElementIncrementsSize){
	ft::map<int, int> map;

	map.insert(ft::make_pair(1, 0));

	ASSERT_EQ(1, map.size());
}

TEST(Map, insertingElementReturnsPairWithSuccessStatusAsSecondElement){
	ft::map<int, int> map;

	ft::pair<ft::map<int, int>::iterator, bool> result = map.insert(ft::make_pair(1, 1));

	ASSERT_TRUE(result.second);
}

TEST(Map, beginContainsLowestKey) {
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.begin();

	ASSERT_EQ(0, *(*it).first);
}

TEST(Map, prevOfEndIsHighestKey) {
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.end();
	it--;

	ASSERT_EQ(4, *(*it).first);
}

TEST(Map, insertingElementWithKeyAlreadyPresentHasSizeOne){
	ft::map<int, int> map;
	map.insert(ft::make_pair(1, 0));

	map.insert(ft::make_pair(1, 0));

	ASSERT_EQ(1, map.size());
}

TEST(Map, returnValueStatesFalseSinceKeyAlreadyPresent){
	ft::map<int, int> map;
	map.insert(ft::make_pair(1, 0));

	ft::pair<ft::map<int, int>::iterator, bool> result = map.insert(ft::make_pair(1, 1));

	ASSERT_EQ(0, result.first->second);
	ASSERT_FALSE(result.second);
}

TEST(Map, comparingMapWithItselfReturnsSame){
	ft::map<int, int> map;

	ASSERT_TRUE(map == map);
}

TEST(Map, comparingMapWithAnotherOneWithSameStructureReturnsSame){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();
	ft::map<simpleDummy, simpleDummy> b = generateTestMap();

	ASSERT_TRUE(a == b);
}

TEST(Map, comparingMapWithAnotherOneWithSameStructureReturnsSame_Negation){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();
	ft::map<simpleDummy, simpleDummy> b = generateTestMap();

	ASSERT_FALSE(a != b);
}

