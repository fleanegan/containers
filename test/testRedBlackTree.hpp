#include "testUtils.hpp"

TEST(RedBlackTree, freshNodeIsAlwaysRed){
	ft::RedBlackNode<int, int> a;

	ASSERT_FALSE(a.isBlack);
}

TEST(RedBlackTree, nullNodeIsAlwaysBlack){
	ft::RedBlackTree<int, int> rbt;

	ASSERT_TRUE(rbt.getNullNode()->isBlack);
}

TEST(RedBlackTree, rootIsBlackAfterInsert){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insert(ft::make_pair(simpleDummy(2), simpleDummy(1)));

	ASSERT_TRUE(rbt.root()->isBlack);
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

TEST(RedBlackTree, insertColourChangeIfUncleHasNotTheSame) {
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insert(ft::make_pair(simpleDummy(5), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(9), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(11), simpleDummy(0)));
	ASSERT_FALSE(rbt.root()->left->isBlack);
	rbt.insert(ft::make_pair(simpleDummy(25), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(24), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(26), simpleDummy(0)));

	ASSERT_EQ(9, *rbt.root()->key);
	ASSERT_EQ(5, *rbt.root()->left->key);
	ASSERT_TRUE(rbt.root()->left->isBlack);
	ASSERT_EQ(24, *rbt.root()->right->key);
	ASSERT_FALSE(rbt.root()->right->isBlack);
	ASSERT_EQ(25, *rbt.root()->right->right->key);
	ASSERT_FALSE(rbt.root()->right->right->right->isBlack);
	ASSERT_EQ(11, *rbt.root()->right->left->key);
}

TEST(RedBlackTree, removeRootWithOneChild) {
	ft::RedBlackTree <simpleDummy, simpleDummy> rbt;
	rbt.insert(ft::make_pair(simpleDummy(5), simpleDummy(0)));
	rbt.insert(ft::make_pair(simpleDummy(9), simpleDummy(0)));

	rbt.popNodeByPointer(rbt.root());

	ASSERT_EQ(9, *rbt.root()->key);
}

TEST(RedBlackTree, multipleInsertionsAlwaysCreateAValidTree){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt = generateBigRbt();

	ASSERT_TRUE(rbt.isValid());
}

TEST(RedBlackTree, notTheSameBlackCountIsInvalidTree){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt = generateBigRbt();
	rbt.root()->left->left->left->isBlack = true;

	ASSERT_FALSE(rbt.isValid());
}

TEST(RedBlackTree, redRootIsIllegal){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt = generateBigRbt();
	rbt.root()->isBlack = false;

	ASSERT_FALSE(rbt.isValid());
}

TEST(RedBlackTree, doubleRedIsIllegal){
	ft::RedBlackTree<int, int> rbt;
	rbt.insertByValue(ft::make_pair(3, 0));
	rbt.insertByValue(ft::make_pair(4, 0));
	rbt.insertByValue(ft::make_pair(1, 0));
	rbt.insertByValue(ft::make_pair(0, 0));
	rbt.insertByValue(ft::make_pair(2, 0));
	rbt.root()->left->isBlack = false;
	rbt.root()->right->isBlack = false;

	ASSERT_FALSE(rbt.isValid());
}

TEST(RedBlackTree, variousDeletionsTreeStillValid){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt = generateBigRbt();
	ASSERT_TRUE(rbt.isValid());

	rbt.popNodeByPointer(rbt.root()->right->right);
	ASSERT_TRUE(rbt.isValid());
	rbt.popNodeByPointer(rbt.root()->left->right);
	ASSERT_TRUE(rbt.isValid());
	rbt.popNodeByPointer(rbt.root()->right->right->right);
	ASSERT_TRUE(rbt.isValid());
	while (rbt.root() != rbt.getNullNode()){
		rbt.popNodeByPointer(rbt.root());
		ASSERT_TRUE(rbt.isValid());
	}
}

TEST(RedBlackTree, assign){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insertByValue(ft::make_pair(1, 0));
	rbt.insertByValue(ft::make_pair(2, 0));
	ft::RedBlackTree<simpleDummy, simpleDummy> reproduction;

	reproduction = rbt;

	ASSERT_EQ(1, *reproduction.root()->key);
}

TEST(RedBlackTree, copyConstructor){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insertByValue(ft::make_pair(1, 0));
	rbt.insertByValue(ft::make_pair(2, 0));

	ft::RedBlackTree<simpleDummy, simpleDummy> reproduction(rbt);

	ASSERT_EQ(1, *reproduction.root()->key);
}

TEST(RedBlackTree, sizeBehavesLikeInParent){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;

	rbt.insertByValue(ft::make_pair(1, 0));
	rbt.insertByValue(ft::make_pair(2, 0));
	ASSERT_EQ(2, rbt.size());

	rbt.popNodeByPointer(rbt.root());
	ASSERT_EQ(1, rbt.size());

	rbt.popNodeByPointer(rbt.root());
	rbt.popNodeByPointer(rbt.root());
	rbt.popNodeByPointer(rbt.root());
	ASSERT_EQ(0, rbt.size());
}

// removingRootWithOneChildKeepsNewRootBlack