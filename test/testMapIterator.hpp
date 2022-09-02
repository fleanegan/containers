#include "testUtils.hpp"

TEST(MapIterator, dereferenceIteratorReturnsContent){
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.begin();

	ASSERT_EQ(0, *(*it).first);
	ASSERT_EQ(0, *(*it).second);
}

TEST(MapIterator, modifyingIteratorModifiesTheActualValue){
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	*(*map.begin()).second = 25;

	ASSERT_EQ(25, *(*map.begin()).second);
}

TEST(MapIterator, decrementingIteratorJumpsToNextLesserKey){
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.end();
	--it;
	--it;
	--it;

	ASSERT_EQ(2, *(*it).first);
}

TEST(MapIterator, decrementingIteratorInverselyFollowsTheKeys){
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(2, 0));
	map.insert(ft::make_pair(1, 0));
	map.insert(ft::make_pair(4, 0));
	map.insert(ft::make_pair(3, 0));

	ft::map<simpleDummy, simpleDummy>::iterator it = map.end();
	--it;
	ASSERT_EQ(4, *(*it).first);
	--it;
	ASSERT_EQ(3, *(*it).first);
	--it;
	ASSERT_EQ(2, *(*it).first);
	--it;
	ASSERT_EQ(1, *(*it).first);
}

TEST(MapIterator, decrementingIteratorAtBeginSetsToNullNode){
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(1, 0));
	map.insert(ft::make_pair(0, 0));

	ft::map<simpleDummy, simpleDummy>::iterator it = map.begin();
	--it;

}

TEST(MapIterator, isolatedKeyFindsItsPrecedence){
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(0, 0));
	map.insert(ft::make_pair(1, 0));
	map.insert(ft::make_pair(2, 0));
	map.insert(ft::make_pair(3, 0));
	map.insert(ft::make_pair(10, 0));
	map.insert(ft::make_pair(11, 0));
	map.insert(ft::make_pair(9, 0));
	map.insert(ft::make_pair(8, 0));
	ft::map<simpleDummy, simpleDummy>::iterator it = map.end();
	--it;
	ASSERT_EQ(11, *(*it).first);
	--it;
	ASSERT_EQ(10, *(*it).first);
	--it;
	ASSERT_EQ(9, *(*it).first);
	--it;
	ASSERT_EQ(8, *(*it).first);

	--it;
	ASSERT_EQ(3, *(*it).first);
}