#include "testUtils.hpp"

TEST(RedBlackTree, freshNodeIsAlwaysRed){
	ft::RedBlackNode<int, int> a;

	ASSERT_FALSE(a.black);
}

TEST(RedBlackTree, nullNodeIsAlwaysBlack){
	ft::RedBlackTree<int, int> rbt;

	ASSERT_TRUE(rbt.getNullNode()->black);
}

TEST(RedBlackTree, rootIsBlackAfterInsert){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insert(ft::make_pair(simpleDummy(2), simpleDummy(1)));

	ASSERT_TRUE(rbt.root()->black);
}

TEST(RedBlackTree, threeConsecutivelyBiggerNodesCauseLeftRotation) {
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insert(ft::make_pair(simpleDummy(0), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(1), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(2), simpleDummy(0)));

	ASSERT_EQ(1, *rbt.root()->key);
	ASSERT_EQ(0, *rbt.root()->left->key);
	ASSERT_EQ(2, *rbt.root()->right->key);
}

TEST(RedBlackTree, addingBiggerThenSmallerNodesCauseLeftRotationAndColourChange) {
	ft::RedBlackTree<int, int> rbt;
	rbt.insert(ft::make_pair(int(2), int(0)));
	rbt.insert(ft::make_pair(int(0), int(0)));
	rbt.insert(ft::make_pair(int(1), int(0)));

	ASSERT_EQ(1, rbt.root()->key);
	ASSERT_EQ(0, rbt.root()->left->key);
	ASSERT_EQ(2, rbt.root()->right->key);
}
