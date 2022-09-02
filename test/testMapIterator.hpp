#include "testUtils.hpp"

TEST(MapIterator, dereferenceIteratorReturnsModifiyableReferenceToPair){
	ft::map<int, int> map;
	map.insert(ft::make_pair(1, 0));

	ft::map<int, int>::iterator it = map.begin();

	ASSERT_EQ(1, (*it).first);
	ASSERT_EQ(0, (*it).second);
	(*it).second = 25;
	ASSERT_EQ(25, (*map.begin()).second);

}