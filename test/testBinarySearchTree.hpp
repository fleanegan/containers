#include "testUtils.hpp"

TEST(BinarySearchTree, searchingAnEmptyTreeByKeyReturnsNULL){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int> > bst;
	int keyToFind = 2;

	ft::SearchTreeStandardNode<int, int> *result = bst.findByKey(keyToFind);

	ASSERT_EQ(nullptr, result);
}

TEST(BinarySearchTree, searchingANodeOnLevelThree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();
	int keyToFind = 7;

	ft::SearchTreeStandardNode<int, int> *result = bst.findByKey(keyToFind);

	ASSERT_NE(result, bst.getNullNode());
}

TEST(BinarySearchTree, insertingANodeOnAnEmptyTreeSetsItAsRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;

	bst.insert(ft::make_pair(1, 2));
	ft::SearchTreeStandardNode<int, int> *result = bst.root();

	ASSERT_NE(result, bst.getNullNode());
	ASSERT_EQ(1, result->content.first);
	ASSERT_EQ(2, result->content.second);
}

TEST(BinarySearchTree, insertingNodeWithSmallerKeyAddsToLeft){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(0, 0));

	ASSERT_NE(nullptr, bst.root()->left);
	ASSERT_EQ(0, bst.root()->left->content.first);
	ASSERT_EQ(0, bst.root()->left->content.second);
}

TEST(BinarySearchTree, insertingMultipleNodesWithAscendingValuesStacksThemOnTheRight){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	ASSERT_EQ(bst.getNullNode(), bst.root()->left);
	ASSERT_EQ(3, bst.root()->right->right->content.first);
}

TEST(BinarySearchTree, insertingMultipleNodesWithDescendingValuesStacksThemOnTheLeft){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(3, 0));

	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(1, 0));

	ASSERT_EQ(bst.getNullNode(), bst.root()->right);
	ASSERT_EQ(1, bst.root()->left->left->content.first);
}

TEST(BinarySearchTree, copyIsDeep){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> from;
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> to;
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
	ASSERT_EQ(-1, to.root()->left->left->right->content.first);
}

TEST(BinarySearchTree, removingNodeOnLowestLevelSetsChildrenOfParentToNULL){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(2, 0));

	bst.popNode(2);

	ASSERT_EQ(bst.getNullNode(), bst.root()->right);
	ASSERT_EQ(bst.getNullNode(), bst.root()->left);
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenAndSuccessorBeingOneOfThem){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(0, 0));
	bst.insert(ft::make_pair(2, 0));

	bst.popNode(1);

	ASSERT_EQ(2, bst.root()->content.first);
	ASSERT_EQ(0, bst.root()->left->content.first);
}

TEST(BinarySearchTree, removingNodeWithOneChildMovesItUp){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	bst.popNode(2);

	ASSERT_NE(bst.getNullNode(), bst.root()->right);
	ASSERT_EQ(bst.getNullNode(), bst.root()->left);
}

TEST(BinarySearchTree, removingRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.popNode(1);

	ASSERT_EQ(bst.getNullNode(), bst.root());
	ASSERT_EQ(bst.getNullNode(), bst.getNullNode()->left);
	ASSERT_EQ(bst.getNullNode(), bst.getNullNode()->right);
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenReplacesWithInorderSuccessor){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(4, 0));
	bst.insert(ft::make_pair(0, 0));
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	bst.popNode(1);

	ASSERT_EQ(2, bst.root()->content.first);
	ASSERT_EQ(4, bst.root()->right->content.first);
	ASSERT_EQ(3, bst.root()->right->left->content.first);
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenReplacesWithInorderSuccessorOnThirdLevel){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	bst.popNode(3);

	ASSERT_EQ(4, bst.root()->content.first);
}

TEST(BinarySearchTree, leftRotatingTree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(6, 0));
	bst.insert(ft::make_pair(3, 0));

	bst.leftRotate(bst.root());

	ASSERT_EQ(6, bst.root()->content.first);
	ASSERT_EQ(2, bst.root()->left->content.first);
	ASSERT_EQ(3, bst.root()->left->right->content.first);
	ASSERT_EQ(2, bst.root()->left->right->parent->content.first);
}

TEST(BinarySearchTree, rightRotatingTree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ft::SearchTreeStandardNode<int, int> *pivot = bst.root();
	bst.rightRotate(pivot);

	ASSERT_EQ(1, bst.root()->content.first);
	ASSERT_EQ(bst.getNullNode(), bst.root()->left);
	ASSERT_EQ(pivot, bst.root()->right);
}

TEST(BinarySearchTree, leftRotatingNodeWithNoChildDoesNothing){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();
	int pivotKey = 20;
	int nodeToSwapWithKey = 19;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.findByKey(pivotKey);
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = bst.findByKey(nodeToSwapWithKey);

	bst.leftRotate(pivot);

	ASSERT_EQ(bst.root()->right->content.first, nodeToSwapWith->parent->content.first);
	ASSERT_EQ(bst.getNullNode(), pivot->right);
	ASSERT_EQ(nodeToSwapWithKey, pivot->parent->content.first);
	ASSERT_EQ(nodeToSwapWith->parent->parent->content.first, bst.root()->content.first);
}

TEST(BinarySearchTree, rightRotatingNodeWithNoChildDoesNothing){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();
	int pivotKey = 4;
	int nodeToSwapWithKey = 5;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.findByKey(pivotKey);
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = bst.findByKey(nodeToSwapWithKey);

	bst.rightRotate(pivot);

	ASSERT_EQ(bst.getNullNode(), pivot->right);
	ASSERT_EQ(nodeToSwapWithKey, pivot->parent->content.first);
}

TEST(BinarySearchTree, rotatingRootAwaySetsNullNodeAsParentOfNewRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	bst.leftRotate(bst.root());

	ASSERT_EQ(bst.getNullNode(), bst.root()->parent);
}

TEST(BinarySearchTree, rightRotatingNodeWithNoRightChildWorks){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();
	int pivotKey = 7;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.findByKey(pivotKey);
	bst.popNodeByPointer(pivot->right);
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = pivot->left;
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWithRight = nodeToSwapWith->right;

	bst.rightRotate(pivot);

	ASSERT_EQ(nodeToSwapWithRight->content.first, pivot->left->content.first);
	ASSERT_EQ(bst.getNullNode(), pivot->right);
	ASSERT_EQ(nodeToSwapWith->content.first, pivot->parent->content.first);
}

TEST(BinarySearchTree, theParentOfTheRootIsTheNullnode){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.getNullNode(), bst.root()->parent);
}

TEST(BinarySearchTree, theParentOfTheRootsChildIsTheParent) {
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.root(), bst.root()->right->parent);
}

TEST(BinarySearchTree, nullNodeWillNeverBeAValidSearchResult) {
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;

	ft::SearchTreeStandardNode<int, int> *result = bst.findByKey((int &) bst.getNullNode()->content.first);

	ASSERT_EQ(nullptr, result);
}

TEST(BinarySearchTree, nullNodePointsToRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.root(), bst.getNullNode()->right);
	ASSERT_EQ(bst.root(), bst.getNullNode()->left);
}

TEST(BinarySearchTree, copyConstructor){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insertByValue(ft::make_pair(1, 0));
	bst.insertByValue(ft::make_pair(2, 0));

	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> reproduction(bst);

	ASSERT_EQ(1, reproduction.root()->content.first);
	//todo: add size == newSize
}

TEST(BinarySearchTree, noItemsSizeIsZero){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;

	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>>::size_type size = bst.size();

	ASSERT_EQ(0, size);
}

TEST(BinarySearchTree, addingIncrementsSize){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 1));

	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>>::size_type size = bst.size();

	ASSERT_EQ(1, size);
}

TEST(BinarySearchTree, assigningTakesSize){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 1));

	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> copy;
	copy = bst;
	copy.insert(ft::make_pair(2, 2));

	ASSERT_NE(bst.size(), copy.size());
	ASSERT_EQ(2, copy.size());
}

TEST(BinarySearchTree, usingCompareGreaterLeadsToInversedTree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>, std::greater<> > bst;
	bst.insert(ft::make_pair(1, 1));

	bst.insert(ft::make_pair(2, 2));

	ASSERT_EQ(2, bst.root()->left->content.first);
}

TEST(BinarySearchTree, addingAlreadyExistingDoesNotIncrementsSize){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 1));

	bst.insert(ft::make_pair(1, 2));

	ASSERT_EQ(1, bst.size());
}

TEST(BinarySearchTree, poppingNodeDecrementsSize){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 1));

	bst.popNode(1);

	ASSERT_EQ(0, bst.size());
}

TEST(BinarySearchTree, getLowestItem){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ft::SearchTreeStandardNode<int, int> *result = bst.getLowest(bst.root(), bst.getNullNode());

	ASSERT_EQ(1, result->content.first);
}

TEST(BinarySearchTree, getHighestItem){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ft::SearchTreeStandardNode<int, int> *result = bst.getHighest(bst.root(), bst.getNullNode());

	ASSERT_EQ(20, result->content.first);
}

 //test corner cases: what happens if the rootnode is being rotated, what if the z.right is nullNode