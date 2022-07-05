#include <stack>
#include "testUtils.hpp"

TEST(stack, isEmptyOnInitialization){
	ft::stack<simpleDummy> stack;

	ASSERT_TRUE(stack.empty());
}

TEST(stack, notEmptyAfterPush){
	ft::stack<simpleDummy> stack;

	stack.push(simpleDummy(3));

	ASSERT_FALSE(stack.empty());
}

TEST(stack, topReturnsLastEnteredElement){
	ft::stack<simpleDummy> stack;
	stack.push(simpleDummy(3));
	stack.push(simpleDummy(2));

	ASSERT_EQ(2, *stack.top());
}

TEST(stack, popRemovesTheLastElement){
	ft::stack<simpleDummy> stack;
	stack.push(simpleDummy(3));
	stack.push(simpleDummy(2));

	stack.pop();

	ASSERT_EQ(1, stack.size());
	ASSERT_EQ(3, *stack.top());
}

TEST(stack, twoEmptyStacksAreEqual){
	ft::stack<simpleDummy> s1;
	ft::stack<simpleDummy> s2;

	ASSERT_EQ(s1, s2);
}

TEST(stack, twoStacksWithTheSameContentAreEqual){
	ft::stack<int> s1;
	s1.push(int(0));

	ft::stack<int> s2;
	s2.push(0);

	ASSERT_EQ(s1, s2);
	ASSERT_FALSE(s1 > s2);
}

TEST(stack, twoStacksWithDifferentContentAreNotEqual){
	ft::stack<int> s1;
	s1.push(int(0));

	ft::stack<int> s2;

	ASSERT_NE(s1, s2);
}

TEST(stack, emptyStackIsSmallerThanNonEmpty){
	ft::stack<int> s1;
	s1.push(int(0));

	ft::stack<int> s2;

	ASSERT_LT(s2, s1);
	ASSERT_TRUE(s1 != s2);
	ASSERT_FALSE(s2 > s1);
	ASSERT_FALSE(s2 >= s1);
	ASSERT_TRUE(s1 >= s2);
	ASSERT_TRUE(s1 >= s1);
	ASSERT_TRUE(s1 <= s1);
}