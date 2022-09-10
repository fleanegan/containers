#include "testUtils.hpp"

TEST(MapIterator, dereferenceIteratorReturnsContent) {
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.begin();

	ASSERT_EQ(0, *(*it).first);
	ASSERT_EQ(0, *(*it).second);
}

TEST(MapIterator, modifyingIteratorModifiesTheActualValue) {
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	*(*map.begin()).second = 25;

	ASSERT_EQ(25, *(*map.begin()).second);
}

TEST(MapIterator, decrementingIteratorJumpsToNextLesserKey) {
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.end();
	--it;
	--it;
	--it;

	ASSERT_EQ(2, *(*it).first);
}

TEST(MapIterator, decrementingIteratorInverselyFollowsTheKeys) {
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

TEST(MapIterator, decrementingIteratorAtBeginSetsToNullNode) {
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(1, 0));
	map.insert(ft::make_pair(0, 0));

	ft::map<simpleDummy, simpleDummy>::iterator it = map.begin();
	--it;
	++it;

	ASSERT_EQ(0, *(*it).first);
}

TEST(MapIterator, isolatedKeyFindsItsPrecedence) {
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();
	ft::map<simpleDummy, simpleDummy>::iterator it = map.end();

	--it;
	ASSERT_EQ(11, *(*it).first);
	--it;
	ASSERT_EQ(10, *(*it).first);
	--it;
	ASSERT_EQ(9, *(*it).first);
	--it;
	ASSERT_EQ(8, *(*it).first);
}

TEST(MapIterator, incrementingBegingGetsPairWithNextBiggerKey) {
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(0, 0));
	map.insert(ft::make_pair(1, 0));

	ft::map<simpleDummy, simpleDummy>::iterator it = map.begin();
	it++;

	ASSERT_EQ(1, *(*it).first);
}

TEST(MapIterator, moveFromStartToEndOfMapUsingIterator) {
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();
	ft::map<simpleDummy, simpleDummy>::iterator it = map.begin();

	while (it != map.end())
		++it;
	--it;

	ASSERT_EQ(11, *(*it).first);
}

TEST(MapIterator, Two_iterators_that_compare_equal_keep_comparing_equal_after_being_both_increased) {
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();
	ft::map<simpleDummy, simpleDummy>::iterator a = map.begin();
	ft::map<simpleDummy, simpleDummy>::iterator b = map.begin();

	while (a != map.end()) {
		a++;
		b++;
		ASSERT_EQ(a, b);
	}
}

TEST(MapIterator, dereferencingOperator) {
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();
	ft::map<simpleDummy, simpleDummy>::iterator a = map.begin();
	ft::pair<simpleDummy, simpleDummy> b = *a;

	ASSERT_EQ(0, *(a->first));
	ASSERT_EQ(0, *b.first);
}

TEST(MapIterator, constIteratorFromNonConst) {
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();
	ft::map<simpleDummy, simpleDummy>::iterator a = map.begin();

	ft::map<simpleDummy, simpleDummy>::const_iterator aee = a;
}

TEST(MapIterator, dereferenceConstIterator) {
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();
	ft::map<simpleDummy, simpleDummy>::iterator a = map.begin();
	ft::map<simpleDummy, simpleDummy>::const_iterator aee = map.begin();

	aee++;
	*aee;

	ASSERT_EQ(0, *(a->first));
}

TEST(MapIterator, moveToNextChangesAddressOfCurrentNode) {
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(1, 2));
	ft::map<simpleDummy, simpleDummy>::iterator a = map.begin();
	ft::map<simpleDummy, simpleDummy>::NodeType *before = a.current();

	a++;

	ft::map<simpleDummy, simpleDummy>::NodeType *after = a.current();
	ASSERT_NE(before, after);
}

TEST(MapIterator, moveToPrevChangesAddressOfCurrentNode) {
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(1, 2));
	ft::map<simpleDummy, simpleDummy>::iterator a = map.end();
	ft::map<simpleDummy, simpleDummy>::NodeType *before = a.current();

	a--;

	ft::map<simpleDummy, simpleDummy>::NodeType *after = a.current();
	ASSERT_NE(before, after);
}

TEST(MapIterator, moveToPrevMovesToNullNodeIfWasOnBeginBefore) {
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(1, 2));
	ft::map<simpleDummy, simpleDummy>::iterator a = map.begin();

	a--;

	ASSERT_TRUE(a.current()->isNullNode());
}

TEST(MapIterator, moveBackUsesToLeft) {
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(1, 2));
	map.insert(ft::make_pair(0, 2));
	map.insert(ft::make_pair(3, 2));
	ft::map<simpleDummy, simpleDummy>::iterator a = --map.end();

	a--;

	ASSERT_EQ(1, *(*a).first);
}