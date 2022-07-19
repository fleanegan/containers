#include "testUtils.hpp"

TEST(BinarySearchTree, searchingAnEmptyTreeByKeyReturns){
	ft::BinarySearchTree<int, int> bst;

	ft::Node<int, int> *result = bst.findByKey(2);

	ASSERT_EQ(result, nullptr);
}

TEST(BinarySearchTree, searchingANodeOnLevelThree){
	ft::BinarySearchTree<int, int> bst = createThreeLevelTree();

	ft::Node<int, int> *result = bst.findByKey(2);

	ASSERT_NE(result, nullptr);
}

TEST(BinarySearchTree, insertingANodeOnAnEmptyTreeSetsItAsRoot){
	ft::BinarySearchTree<int, int> bst;

	bst.insert(ft::make_pair(1, 2));
	ft::Node<int, int> *result = bst.root();

	ASSERT_NE(result, nullptr);
	ASSERT_EQ(1, result->key);
	ASSERT_EQ(2, result->value);
}

TEST(BinarySearchTree, insertingSameKeysTwiceSetsNewNodeToRight){
	ft::BinarySearchTree<int, int> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(1, 0));

	ASSERT_NE(nullptr, bst.root()->right);
	ASSERT_EQ(1, bst.root()->right->key);
	ASSERT_EQ(0, bst.root()->right->value);
}

TEST(BinarySearchTree, insertingNodeWithSmallerKeyAddsToLeft){
	ft::BinarySearchTree<int, int> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(0, 0));

	ASSERT_NE(nullptr, bst.root()->left);
	ASSERT_EQ(0, bst.root()->left->key);
	ASSERT_EQ(0, bst.root()->left->value);
}

TEST(BinarySearchTree, insertingMultipleNodesWithAscendingValuesStacksThemOnTheRight){
	ft::BinarySearchTree<int, int> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	ASSERT_EQ(nullptr, bst.root()->left);
	ASSERT_EQ(3, bst.root()->right->right->key);
}

TEST(BinarySearchTree, insertingMultipleNodesWithDescendingValuesStacksThemOnTheLeft){
	ft::BinarySearchTree<int, int> bst;
	bst.insert(ft::make_pair(3, 0));

	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(1, 0));

	ASSERT_EQ(nullptr, bst.root()->right);
	ASSERT_EQ(1, bst.root()->left->left->key);
}

TEST(BinarySearchTree, copyIsDeep){
	ft::BinarySearchTree<int, int> from;
	ft::BinarySearchTree<int, int> to;
	from.insert(ft::make_pair(1, 1));
	from.insert(ft::make_pair(2, 1));
	from.insert(ft::make_pair(0, 1));
	from.insert(ft::make_pair(-2, 1));
	from.insert(ft::make_pair(-1, 1));

	to = from;

	ASSERT_NE(to.root(), from.root());
	ASSERT_NE(to.root()->right, from.root()->right);
	ASSERT_NE(to.root()->right, nullptr);
	ASSERT_NE(to.root()->left, from.root()->left);
	ASSERT_NE(to.root()->left, nullptr);
	ASSERT_EQ(-1, to.root()->left->left->right->key);
}

TEST(BinarySearchTree, removingNodeOnLowestLevelSetsChildrenOfParentToNULL){
	ft::BinarySearchTree<int, int> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(2, 0));

	bst.popNode(2);

	ASSERT_EQ(nullptr, bst.root()->right);
	ASSERT_EQ(nullptr, bst.root()->left);
}

TEST(BinarySearchTree, removingNodeWithOneChildMovesItUp){
	ft::BinarySearchTree<int, int> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	bst.popNode(2);

	ASSERT_NE(nullptr, bst.root()->right);
	ASSERT_EQ(nullptr, bst.root()->left);
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenReplacesWithInorderSuccessor){
	ft::BinarySearchTree<int, int> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(3, 0));
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(4, 0));

	bst.popNode(3);

	ASSERT_EQ(4, bst.root()->right->key);
	ASSERT_EQ(2, bst.root()->right->left->key);
	ASSERT_EQ(nullptr, bst.root()->right->right);
	ASSERT_EQ(nullptr, bst.root()->right->left->right);
	ASSERT_EQ(nullptr, bst.root()->right->left->left);
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenReplacesWithInorderSuccessorOnThirdLevel){
	ft::BinarySearchTree<int, int> bst;
	bst.insert(ft::make_pair(-3, 0));
	bst.insert(ft::make_pair(3, 0));
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(16, 0));
	bst.insert(ft::make_pair(19, 0));
	bst.insert(ft::make_pair(7, 0));
	bst.insert(ft::make_pair(5, 0));
	bst.insert(ft::make_pair(8, 0));
	bst.insert(ft::make_pair(4, 0));
	bst.insert(ft::make_pair(6, 0));


	bst.popNode(3);

	ASSERT_EQ(4, bst.root()->right->key);
}

// removingRootDoesNotAttemptToSetParentNULL