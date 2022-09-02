#include "testUtils.hpp"

TEST(Map, insertingElementWithKeyAlreadyPresent){
	ft::map<int, int> map;

	map.insert(ft::make_pair(1, 0));

	ASSERT_EQ(1, map.size());
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

//insertingElementWithKeyAlreadyPresentHasSizeOne
//returnValueStatesFalseSinceKeyAlreadyPresent