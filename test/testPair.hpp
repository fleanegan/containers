#include "testUtils.hpp"

TEST(pair, accessContent){
	ft::pair<int, int> test;

	ASSERT_EQ(test.first, test.second);
}

TEST(pair, copyConstruct){
	ft::pair<int, int> source;
	source.first = 42;
	ft::pair<int, int> dest(source);

	ASSERT_EQ(42, dest.first);
	ASSERT_EQ(0, dest.second);
}

TEST(pair, initializationConstruct){

	simpleDummy first(1);
	int second = 2;
	ft::pair<simpleDummy, int> test(first, second);

	ASSERT_EQ(1, *test.first);
	ASSERT_EQ(2, test.second);
}

TEST(pair, assignment){
	ft::pair<int, int> source;
	source.first = 42;
	source.second = 24;
	ft::pair<int, int> dest;
	dest = source;

	ASSERT_EQ(42, dest.first);
	ASSERT_EQ(24, dest.second);
}

TEST(pair, comparison){
	ft::pair<int, int> a(1, 4);
	ft::pair<int, int> b(2, 6);

	ASSERT_TRUE(a < b);
	ASSERT_TRUE(a <= b);
	ASSERT_TRUE(a <= a);
	ASSERT_TRUE(b <= b);
	ASSERT_TRUE(b >= a);
	ASSERT_TRUE(b > a);
}

TEST(pair, make_pair){
	ft::pair<int, simpleDummy> pr = ft::make_pair(235, simpleDummy(3));

	ASSERT_EQ(235, pr.first);
	ASSERT_EQ(3, *pr.second);
}