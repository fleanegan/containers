#include "testUtils.hpp"

TEST(vectorIterator, deferencingAnIteratorReturnsAReferenceToTheObjectPointedTo){
	ft::vector<simpleDummy> vec;
	vec.push_back(simpleDummy(1));
	ft::vector<simpleDummy>::iterator it1 = vec.begin();

	ASSERT_EQ(1, **it1);
	ASSERT_EQ(&(**it1), &(*(it1->i)));
}

TEST(vectorIterator, testCanonicalForm){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	std::cout << "creating test vector " << std::endl;
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2(it1);
	std::cout << "creating from iterator: done " << std::endl;
	ft::vector<simpleDummy>::iterator it3 = vec.begin();
	it3 = it1;

	ASSERT_EQ(it1, it2);
	ASSERT_EQ(it1, it3);
}


TEST(vectorIterator, comparingTheSamePointers){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();

	ASSERT_EQ(it1, it2);
}

TEST(vectorIterator, comparingTheUnequalPointers){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();
	++it2;

	ASSERT_NE(it1, it2);
}

TEST(vectorIterator, equalIteratorsStayEqualWhenAdvancing){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();
	++it2;
	++it1;

	ASSERT_EQ(it1, it2);
}

TEST(vectorIterator, postIncrementingChangesValueAfter){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();

	ASSERT_EQ(**it1, *(*it2++));
}

TEST(vectorIterator, incrementMultipleTimes){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();

	ASSERT_EQ(5, *(*(++++++++it1)));
	ASSERT_EQ(1, *(*(--------it1)));
}

TEST(vectorIterator, plusEqualOperator){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	it1 += 1;

	ASSERT_EQ(2, **it1);
}

TEST(vectorIterator, addingIntsToIterators){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::iterator it1 = vec.begin();
	ft::vector<simpleDummy>::iterator it2 = vec.begin();
	it2 = it1 + 1;
	it1++;

	ASSERT_EQ(it1, it2);
}

TEST(vectorIterator, subtractingIteratorsFromIterators){
	ft::vector<simpleDummy> vec = createTestDummyVector();
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
	ft::vector<simpleDummy> vec = createTestDummyVector();
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

TEST(vectorIterator, canUseIteratorAdditionDirectlyInFunctionCall){
	ft::vector<int> vec;
	vec.push_back(1);
	ft::vector<int>::iterator it1 = vec.end();

	testIterator<ft::vector<int> >(it1 - 1);
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
}

TEST(vectorIterator, canConstructConstFromNormal){
	ft::vector<simpleDummy> vec = createTestDummyVector();

	ft::vector<simpleDummy>::const_iterator nameOfConstIterator(vec.end());
}

TEST(vectorIterator, subtractConstIteratorFromNormal){
	ft::vector<simpleDummy> vec = createTestDummyVector();
	ft::vector<simpleDummy>::const_iterator consty(vec.end());
	ft::vector<simpleDummy>::iterator non_consty(vec.begin());

	ft::vector<simpleDummy>::difference_type result = consty - non_consty;

}

template<typename T>
void checkErase(ft::vector<T> const &vct, typename ft::vector<T>::const_iterator const &it)
{
	static int i = 0;
	it - vct.begin();
	//std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
}

TEST(vectorIterator, addToInt){
	ft::vector<simpleDummy> vec;
	std::vector<simpleDummy> vecS;
	vec.push_back(simpleDummy(9));
	vecS.push_back(simpleDummy(9));

	ft::vector<simpleDummy>::iterator it = 1 + vec.begin();
	std::vector<simpleDummy>::iterator itS = 1 + vecS.begin();

}

TEST(vectorIterator, subtractConstFromNonConst){
	ft::vector<simpleDummy> vec = createTestDummyVector();

	checkErase(vec, vec.end());
}