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

TEST(Map, assignmentClearsBeforeAddingNew) {
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();
	ft::map<simpleDummy, simpleDummy> mapPlusOne;
	mapPlusOne.insert(ft::make_pair(123, 2));

	mapPlusOne = map;

	ASSERT_TRUE(map == mapPlusOne);
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

TEST(Map, comparingEmptyMapWithNonEmpty){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();
	ft::map<simpleDummy, simpleDummy> b;

	ASSERT_FALSE(a < b);
	ASSERT_TRUE(a > b);
	ASSERT_FALSE(a > a);
	ASSERT_FALSE(a < a);
	ASSERT_TRUE(a <= a);
	ASSERT_TRUE(b <= a);
	ASSERT_FALSE(a <= b);
	ASSERT_TRUE(a >= a);
	ASSERT_TRUE(a >= b);
	ASSERT_FALSE(b >= a);
}

TEST(Map, mapWithNoItemsIsEmpty){
	ft::map<simpleDummy, simpleDummy> map;

	ASSERT_TRUE(map.empty());
}

TEST(Map, emptyAfterClearing){
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	map.clear();

	ASSERT_EQ(0, map.size());
	ASSERT_TRUE(map.empty());
}

TEST(Map, constructOneElementFromIterator){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();

	ft::map<simpleDummy, simpleDummy> fromA(a.begin(), ++a.begin());


	ASSERT_EQ(1, fromA.size());
	ASSERT_EQ(0, *(fromA.begin()->first));
}

TEST(Map, constructHoleMapFromIterator){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();

	ft::map<simpleDummy, simpleDummy> fromA(a.begin(), a.end());

	bool structuralEquality = (fromA == a);
	bool lexicographicalEquality = (fromA >= a);
	ASSERT_FALSE(structuralEquality);
	ASSERT_TRUE(lexicographicalEquality);
}

TEST(Map, accessOperatorReadOnly){
	ft::map<int, int> map;
	map.insert(ft::make_pair(0, 1));
	map.insert(ft::make_pair(1, 2));

	int result = map[1];

	ASSERT_EQ(2, result);
}

TEST(Map, accessOperatorWrite){
	ft::map<int, int> map;
	map.insert(ft::make_pair(0, 1));

	map[0] = 2;

	ASSERT_EQ(2, map[0]);
}

TEST(Map, atThrowsIfKeyNotPresent){
	ft::map<int, int> map;

	ASSERT_ANY_THROW(map.at(1));
}

TEST(Map, atReturnsMappedValueOfKeyIfKeyPresent){
	ft::map<int, int> map;
	map.insert(ft::make_pair(1, 2));

	ASSERT_EQ(2, map.at(1));
}

TEST(Map, atReadOnly){
	ft::map<int, int> map;
	map.insert(ft::make_pair(1, 2));

	const ft::map<int, int> constMap = map;

	ASSERT_EQ(2, constMap.at(1));
}

TEST(Map, hasReverseIterator){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();

	ft::map<simpleDummy, simpleDummy>::reverse_iterator revy = a.rbegin();
}

TEST(Map, constMapHasConstIterator){
	const ft::map<int, int> map;

	ft::map<int, int>::const_iterator constIt = map.begin();
}

TEST(Map, insertWithHint){
	ft::map<int, int> map;

	map.insert(map.begin(), ft::make_pair(1, 2));
}

TEST(Map, erasingOneElementDecrementsSize){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();
	ft::map<simpleDummy, simpleDummy>::size_type before = a.size();

	a.erase(a.begin());

	ft::map<simpleDummy, simpleDummy>::size_type after = a.size();
	ASSERT_EQ(before, after + 1);
}

TEST(Map, erasingByKeyReturnsOneIfElementIsFound){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();

	ASSERT_EQ(1, a.erase(a.begin()->first));
	ASSERT_EQ(0, a.erase(simpleDummy(666)));
}

TEST(Map, deletingOneElementByIterators){
		ft::map<simpleDummy, simpleDummy> a;
		a.insert(ft::make_pair(1, 2));

		a.erase(a.begin(), a.end());

		ASSERT_EQ(0, a.size());
}

TEST(Map, deletingTheWholeMapByIterators){
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();

	a.erase(a.begin(), a.end());

	ASSERT_EQ(0, a.size());
}


TEST(Map, deletingEmptyMapByIterators){
	ft::map<simpleDummy, simpleDummy> a;
	ASSERT_EQ(0, a.size());

	a.erase(a.begin(), a.end());

	ASSERT_EQ(0, a.size());
}

TEST(Map, deletingEmptyMapDoesNotDoAnything){
	ft::map<simpleDummy, simpleDummy> a;

	a.erase(a.begin(), a.end());

	ASSERT_EQ(0, a.size());
}

TEST(Map, swappingEmptyMapWithNonEmpty){
	ft::map<simpleDummy, simpleDummy> compA = generateTestMap();
	ft::map<simpleDummy, simpleDummy> a = generateTestMap();
	ft::map<simpleDummy, simpleDummy> compB;
	ft::map<simpleDummy, simpleDummy> b;

	a.swap(b);

	ASSERT_EQ(0, a.size());
	ASSERT_EQ(compA.size(), b.size());
	ASSERT_TRUE(compA <= b);
	ASSERT_TRUE(compB <= a);
}

TEST(Map, searchingInEmptyMapReturnsEnd){
	ft::map<simpleDummy, simpleDummy> a;

	ft::map<simpleDummy, simpleDummy>::iterator it = a.find(simpleDummy(1));

	ASSERT_EQ(a.end(), it);
}

TEST(Map, lowerBoundReturnsIteratorToNodeWhichIsGreaterEqual){
	ft::map<simpleDummy, simpleDummy> map = generateTestMap();

	simpleDummy value = (*map.lower_bound(simpleDummy(21))).first;

	ASSERT_EQ(4, *value);
}

TEST(Map, lowerBoundOfBiggestReturnsSecondLargest){
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();

	simpleDummy value = (*map.lower_bound(simpleDummy(7))).first;

	ASSERT_EQ(3, *value);
}

TEST(Map, lowerBoundReturnsSameKeyifKeyIsFound){
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();

	simpleDummy value = (*map.lower_bound(simpleDummy(8))).first;

	ASSERT_EQ(8, *value);
}

TEST(Map, lowerBoundWorksAlsoForNodeUnderBegin){
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.lower_bound(simpleDummy(0));

	ASSERT_EQ(it, map.begin());
}

TEST(Map, upperBoundReturnsBeginIfSearchKeyIsTooSmall){
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.upper_bound(simpleDummy(-12));

	ASSERT_EQ(it, map.begin());
}

TEST(Map, upperBoundGetsNext){
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();

	ft::map<simpleDummy, simpleDummy>::iterator it = map.upper_bound(simpleDummy(4));

	ASSERT_EQ(8, *(*it).first);
}

TEST(Map, equalRangeReturnsPairWithIteratorsForElementFound){
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();

	ft::pair<ft::map<simpleDummy, simpleDummy>::iterator, ft::map<simpleDummy, simpleDummy>::iterator> it = map.equal_range(simpleDummy(8));

	ASSERT_EQ(8, *(it.first)->first);
}

TEST(Map, equalRangeReturnsPairWithTwoTimesEndForKeyNotFound){
	ft::map<simpleDummy, simpleDummy> map = generateMapWithIsolatedKey();

	ft::pair<ft::map<simpleDummy, simpleDummy>::iterator, ft::map<simpleDummy, simpleDummy>::iterator> it = map.equal_range(simpleDummy(666));

	ASSERT_EQ(it.first, it.second);
	ASSERT_EQ(map.end(), it.second);
}