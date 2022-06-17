#include "testUtils.hpp"

TEST(vectorIterator, deferencingAnIteratorReturnsAReferenceToTheObjectPointedTo){
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));
	createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();

	ASSERT_EQ(1, **it1);
	ASSERT_EQ(&(**it1), &(*(it1->i)));
}
/*
TEST(vectorIterator, testCanonicalForm){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2(it1);
	ft::vector<simpleDummy>::iterator it3 = vec.begin();
	it3 = it1;

	ASSERT_EQ(it1, it2);
	ASSERT_EQ(it1, it3);
}


TEST(vectorIterator, comparingTheSamePointers){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();

	ASSERT_EQ(it1, it2);
}

TEST(vectorIterator, comparingTheUnequalPointers){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();
	++it2;

	ASSERT_NE(it1, it2);
}

TEST(vectorIterator, equalIteratorsStayEqualWhenAdvancing){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();
	++it2;
	++it1;

	ASSERT_EQ(it1, it2);
}

TEST(vectorIterator, postIncrementingChangesValueAfter){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();

	ASSERT_EQ(**it1, *(*it2++));
}

TEST(vectorIterator, incrementMultipleTimes){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();

	ASSERT_EQ(5, *(*(++++++++it1)));
	ASSERT_EQ(1, *(*(--------it1)));
}

TEST(vectorIterator, plusEqualOperator){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	it1 += 1;

	ASSERT_EQ(2, **it1);
}

TEST(vectorIterator, addingIntsToIterators){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();
	it2 = it1 + 1;
	it1++;

	ASSERT_EQ(it1, it2);
}

TEST(vectorIterator, subtractingIteratorsFromIterators){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();
	it1++;
	size_t distance = it1 - it2;

	ASSERT_EQ(1, distance);
}

TEST(vectorIterator, dereferenceAsLvalue){
	ft::vector<int> vec;
	vec.push_back(1);
	ft::vector<int>::iterator it1 = vec.begin();
	*it1 = 4;

	ASSERT_EQ(4, vec.front());
}

TEST(vectorIterator, offsetDereferenceAsLvalue){
	ft::vector<simpleDummy> vec = createTestDumyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();

	ASSERT_EQ(1, *it1[0]);
	ASSERT_EQ(2, *it1[1]);
}

TEST(vectorIterator, incrementDereferenced){
	ft::vector<int> vec;
	vec.push_back(1);
	ft::vector<int>::iterator it1 = vec.begin();

	ASSERT_EQ(1, *it1++);
	ASSERT_NE(vec.begin(), it1);
}

TEST(vectorIterator, relationalComparison){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin() + 1;
	ft::vector<simpleDummy>::iterator it3 = vec.begin() + 1;

	ASSERT_TRUE(it1 < it2);
	ASSERT_TRUE(it2 > it1);
	ASSERT_TRUE(it2 >= it1);
	ASSERT_TRUE(it2 >= it3);
	ASSERT_TRUE(it1 <= it2);
	ASSERT_TRUE(it3 <= it2);
}*/
