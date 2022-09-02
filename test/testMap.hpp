#include "testUtils.hpp"

TEST(Map, insertingElementWithKeyAlreadyPresent){
	ft::map<int, int> map;

	map.insert(ft::make_pair(1, 0));

	ASSERT_EQ(1, map.size());
}

//insertingElementWithKeyAlreadyPresentHasSizeOne
//returnValueStatesFalseSinceKeyAlreadyPresent