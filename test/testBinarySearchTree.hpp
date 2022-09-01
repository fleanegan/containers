#include "testUtils.hpp"

TEST(BinarySearchTree, searchingAnEmptyTreeByKeyReturnsNULL){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	int keyToFind = 2;

	ft::SearchTreeStandardNode<int, int> *result = bst.findByKey(keyToFind);

	ASSERT_EQ(nullptr, result);
}

TEST(BinarySearchTree, searchingANodeOnLevelThree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();
	int keyToFind = 7;

	ft::SearchTreeStandardNode<int, int> *result = bst.findByKey(keyToFind);

	ASSERT_NE(result, bst.getNullNode());
}

TEST(BinarySearchTree, insertingANodeOnAnEmptyTreeSetsItAsRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;

	bst.insert(ft::make_pair(1, 2));
	ft::SearchTreeStandardNode<int, int> *result = bst.root();

	ASSERT_NE(result, bst.getNullNode());
	ASSERT_EQ(1, result->key);
	ASSERT_EQ(2, result->value);
}

TEST(BinarySearchTree, insertingSameKeysTwiceSetsNewNodeToRight){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(1, 0));

	ASSERT_NE(nullptr, bst.root()->right);
	ASSERT_EQ(1, bst.root()->right->key);
	ASSERT_EQ(0, bst.root()->right->value);
}

TEST(BinarySearchTree, insertingNodeWithSmallerKeyAddsToLeft){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(0, 0));

	ASSERT_NE(nullptr, bst.root()->left);
	ASSERT_EQ(0, bst.root()->left->key);
	ASSERT_EQ(0, bst.root()->left->value);
}

TEST(BinarySearchTree, insertingMultipleNodesWithAscendingValuesStacksThemOnTheRight){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	ASSERT_EQ(bst.getNullNode(), bst.root()->left);
	ASSERT_EQ(3, bst.root()->right->right->key);
}

TEST(BinarySearchTree, insertingMultipleNodesWithDescendingValuesStacksThemOnTheLeft){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(3, 0));

	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(1, 0));

	ASSERT_EQ(bst.getNullNode(), bst.root()->right);
	ASSERT_EQ(1, bst.root()->left->left->key);
}

TEST(BinarySearchTree, copyIsDeep){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> from;
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> to;
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
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(2, 0));

	bst.popNode(2);

	ASSERT_EQ(bst.getNullNode(), bst.root()->right);
	ASSERT_EQ(bst.getNullNode(), bst.root()->left);
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenAndSuccessorBeingOneOfThem){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(0, 0));
	bst.insert(ft::make_pair(2, 0));

	bst.popNode(1);

	ASSERT_EQ(2, bst.root()->key);
	ASSERT_EQ(0, bst.root()->left->key);
}

TEST(BinarySearchTree, removingNodeWithOneChildMovesItUp){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	bst.popNode(2);

	ASSERT_NE(bst.getNullNode(), bst.root()->right);
	ASSERT_EQ(bst.getNullNode(), bst.root()->left);
}

TEST(BinarySearchTree, removingRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.popNode(1);

	ASSERT_EQ(bst.getNullNode(), bst.root());
	ASSERT_EQ(bst.getNullNode(), bst.getNullNode()->left);
	ASSERT_EQ(bst.getNullNode(), bst.getNullNode()->right);
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenReplacesWithInorderSuccessor){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(4, 0));
	bst.insert(ft::make_pair(0, 0));
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	bst.popNode(1);

	ASSERT_EQ(2, bst.root()->key);
	ASSERT_EQ(4, bst.root()->right->key);
	ASSERT_EQ(3, bst.root()->right->left->key);
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenReplacesWithInorderSuccessorOnThirdLevel){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();

	bst.popNode(3);

	ASSERT_EQ(4, bst.root()->key);
}

TEST(BinarySearchTree, leftRotatingTree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(6, 0));
	bst.insert(ft::make_pair(3, 0));

	bst.leftRotate(bst.root());

	ASSERT_EQ(6, bst.root()->key);
	ASSERT_EQ(2, bst.root()->left->key);
	ASSERT_EQ(3, bst.root()->left->right->key);
	ASSERT_EQ(2, bst.root()->left->right->parent->key);
}

TEST(BinarySearchTree, rightRotatingTree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();

	ft::SearchTreeStandardNode<int, int> *pivot = bst.root();
	bst.rightRotate(pivot);

	ASSERT_EQ(1, bst.root()->key);
	ASSERT_EQ(bst.getNullNode(), bst.root()->left);
	ASSERT_EQ(pivot, bst.root()->right);
}

TEST(BinarySearchTree, leftRotatingNodeWithNoChildDoesNothing){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();
	int pivotKey = 20;
	int nodeToSwapWithKey = 19;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.findByKey(pivotKey);
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = bst.findByKey(nodeToSwapWithKey);

	bst.leftRotate(pivot);

	ASSERT_EQ(bst.root()->right->key, nodeToSwapWith->parent->key);
	ASSERT_EQ(bst.getNullNode(), pivot->right);
	ASSERT_EQ(nodeToSwapWithKey, pivot->parent->key);
	ASSERT_EQ(nodeToSwapWith->parent->parent->key, bst.root()->key);
}

TEST(BinarySearchTree, rightRotatingNodeWithNoChildDoesNothing){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();
	int pivotKey = 4;
	int nodeToSwapWithKey = 5;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.findByKey(pivotKey);
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = bst.findByKey(nodeToSwapWithKey);

	bst.rightRotate(pivot);

	ASSERT_EQ(bst.getNullNode(), pivot->right);
	ASSERT_EQ(nodeToSwapWithKey, pivot->parent->key);
}

TEST(BinarySearchTree, rotatingRootAwaySetsNullNodeAsParentOfNewRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();

	bst.leftRotate(bst.root());

	ASSERT_EQ(bst.getNullNode(), bst.root()->parent);
}

TEST(BinarySearchTree, rightRotatingNodeWithNoRightChildWorks){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();
	int pivotKey = 7;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.findByKey(pivotKey);
	bst.popNodeByPointer(pivot->right);
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = pivot->left;
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWithRight = nodeToSwapWith->right;

	bst.rightRotate(pivot);

	ASSERT_EQ(nodeToSwapWithRight->key, pivot->left->key);
	ASSERT_EQ(bst.getNullNode(), pivot->right);
	ASSERT_EQ(nodeToSwapWith->key, pivot->parent->key);
}

TEST(BinarySearchTree, theParentOfTheRootIsTheNullnode){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.getNullNode(), bst.root()->parent);
}

TEST(BinarySearchTree, theParentOfTheRootsChildIsTheParent) {
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.root(), bst.root()->right->parent);
}

TEST(BinarySearchTree, nullNodeWillNeverBeAValidSearchResult) {
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	int randomKey = 8;
	bst.getNullNode()->key = randomKey;

	ft::SearchTreeStandardNode<int, int> *result = bst.findByKey(randomKey);

	ASSERT_EQ(nullptr, result);
}

TEST(BinarySearchTree, nullNodePointsToRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.root(), bst.getNullNode()->right);
	ASSERT_EQ(bst.root(), bst.getNullNode()->left);
}

TEST(BinarySearchTree, copyConstructor){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> bst;
	bst.insertByValue(ft::make_pair(1, 0));
	bst.insertByValue(ft::make_pair(2, 0));

	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> reproduction(bst);

	ASSERT_EQ(1, reproduction.root()->key);
}

// test corner cases: what happens if the rootnode is being rotated, what if the z.right is nullNode