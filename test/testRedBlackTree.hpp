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

TEST(RedBlackTree, addingBiggerThenSmallerNodesCauseLeftRotation) {
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insert(ft::make_pair(simpleDummy(2), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(0), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(1), simpleDummy(0)));

	ASSERT_EQ(1, *rbt.root()->key);
	ASSERT_EQ(0, *rbt.root()->left->key);
	ASSERT_EQ(2, *rbt.root()->right->key);
}

TEST(RedBlackTree, changeOfRootUpdatesLinksOfNullNode) {
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insert(ft::make_pair(simpleDummy(2), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(0), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(1), simpleDummy(0)));

	ASSERT_EQ(rbt.getNullNode()->right, rbt.root());
}

TEST(RedBlackTree, colourChangeIfUncleHasNotTheSame) {
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insert(ft::make_pair(simpleDummy(5), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(9), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(11), simpleDummy(0)));
	ASSERT_FALSE(rbt.root()->left->black);
	rbt.insert(ft::make_pair(simpleDummy(25), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(24), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(26), simpleDummy(0)));

	ASSERT_EQ(9, *rbt.root()->key);
	ASSERT_EQ(5, *rbt.root()->left->key);
	ASSERT_TRUE(rbt.root()->left->black);
	ASSERT_EQ(24, *rbt.root()->right->key);
	ASSERT_FALSE(rbt.root()->right->black);
	ASSERT_EQ(25, *rbt.root()->right->right->key);
	ASSERT_FALSE(rbt.root()->right->right->right->black);
	ASSERT_EQ(11, *rbt.root()->right->left->key);
}