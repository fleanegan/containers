#include "testUtils.hpp"

TEST(BinarySearchTree, searchingANodeOnLevelThree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();
	int keyToFind = 7;

	ft::SearchTreeStandardNode<int, int> *result = bst.find(keyToFind);

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

	ASSERT_NE(nullptr, bst.root()->getLeft());
	ASSERT_EQ(0, bst.root()->getLeft()->content.first);
	ASSERT_EQ(0, bst.root()->getLeft()->content.second);
}

TEST(BinarySearchTree, insertingMultipleNodesWithAscendingValuesStacksThemOnTheRight){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	ASSERT_EQ(bst.getNullNode(), bst.root()->getLeft());
	ASSERT_EQ(3, bst.root()->getRight()->getRight()->content.first);
}

TEST(BinarySearchTree, insertingMultipleNodesWithDescendingValuesStacksThemOnTheLeft){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(3, 0));

	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(1, 0));

	ASSERT_EQ(bst.getNullNode(), bst.root()->getRight());
	ASSERT_EQ(1, bst.root()->getLeft()->getLeft()->content.first);
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
	ASSERT_NE(to.root()->getRight(), from.root()->getRight());
	ASSERT_NE(to.root()->getRight(), nullptr);
	ASSERT_NE(to.root()->getLeft(), from.root()->getLeft());
	ASSERT_NE(to.root()->getLeft(), nullptr);
	ASSERT_EQ(-1, to.root()->getLeft()->getLeft()->getRight()->content.first);
}

TEST(BinarySearchTree, removingNodeOnLowestLevelSetsChildrenOfParentToNULL){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(2, 0));

	bst.popNode(2);

	ASSERT_EQ(bst.getNullNode(), bst.root()->getRight());
	ASSERT_EQ(bst.getNullNode(), bst.root()->getLeft());
}

TEST(BinarySearchTree, removingNodeWithTwoChildrenAndSuccessorBeingOneOfThem){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(0, 0));
	bst.insert(ft::make_pair(2, 0));

	bst.popNode(1);

	ASSERT_EQ(2, bst.root()->content.first);
	ASSERT_EQ(0, bst.root()->getLeft()->content.first);
}

TEST(BinarySearchTree, removingNodeWithOneChildMovesItUp){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));
	bst.insert(ft::make_pair(2, 0));
	bst.insert(ft::make_pair(3, 0));

	bst.popNode(2);

	ASSERT_NE(bst.getNullNode(), bst.root()->getRight());
	ASSERT_EQ(bst.getNullNode(), bst.root()->getLeft());
}

TEST(BinarySearchTree, removingRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 0));

	bst.popNode(1);

	ASSERT_EQ(bst.getNullNode(), bst.root());
	ASSERT_EQ(bst.getNullNode(), bst.getNullNode()->getLeft());
	ASSERT_EQ(bst.getNullNode(), bst.getNullNode()->getRight());
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
	ASSERT_EQ(4, bst.root()->getRight()->content.first);
	ASSERT_EQ(3, bst.root()->getRight()->getLeft()->content.first);
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
	ASSERT_EQ(2, bst.root()->getLeft()->content.first);
	ASSERT_EQ(3, bst.root()->getLeft()->getRight()->content.first);
	ASSERT_EQ(2, bst.root()->getLeft()->getRight()->getParent()->content.first);
}

TEST(BinarySearchTree, rightRotatingTree){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ft::SearchTreeStandardNode<int, int> *pivot = bst.root();
	bst.rightRotate(pivot);

	ASSERT_EQ(1, bst.root()->content.first);
	ASSERT_EQ(bst.getNullNode(), bst.root()->getLeft());
	ASSERT_EQ(pivot, bst.root()->getRight());
}

TEST(BinarySearchTree, leftRotatingNodeWithNoChildDoesNothing){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();
	int pivotKey = 20;
	int nodeToSwapWithKey = 19;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.find(pivotKey);
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = bst.find(nodeToSwapWithKey);

	bst.leftRotate(pivot);

	ASSERT_EQ(bst.root()->getRight()->content.first, nodeToSwapWith->getParent()->content.first);
	ASSERT_EQ(bst.getNullNode(), pivot->getRight());
	ASSERT_EQ(nodeToSwapWithKey, pivot->getParent()->content.first);
	ASSERT_EQ(nodeToSwapWith->getParent()->getParent()->content.first, bst.root()->content.first);
}

TEST(BinarySearchTree, rightRotatingNodeWithNoChildDoesNothing){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();
	int pivotKey = 4;
	int nodeToSwapWithKey = 5;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.find(pivotKey);
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = bst.find(nodeToSwapWithKey);

	bst.rightRotate(pivot);

	ASSERT_EQ(bst.getNullNode(), pivot->getRight());
	ASSERT_EQ(nodeToSwapWithKey, pivot->getParent()->content.first);
}

TEST(BinarySearchTree, rotatingRootAwaySetsNullNodeAsParentOfNewRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	bst.leftRotate(bst.root());

	ASSERT_EQ(bst.getNullNode(), bst.root()->getParent());
}

TEST(BinarySearchTree, rightRotatingNodeWithNoRightChildWorks){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();
	int pivotKey = 7;
	ft::SearchTreeStandardNode<int, int> *pivot = bst.find(pivotKey);
	bst.popNodeByPointer(pivot->getRight());
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWith = pivot->getLeft();
	ft::SearchTreeStandardNode<int, int> *nodeToSwapWithRight = nodeToSwapWith->getRight();

	bst.rightRotate(pivot);

	ASSERT_EQ(nodeToSwapWithRight->content.first, pivot->getLeft()->content.first);
	ASSERT_EQ(bst.getNullNode(), pivot->getRight());
	ASSERT_EQ(nodeToSwapWith->content.first, pivot->getParent()->content.first);
}

TEST(BinarySearchTree, theParentOfTheRootIsTheNullnode){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.getNullNode(), bst.root()->getParent());
}

TEST(BinarySearchTree, theParentOfTheRootsChildIsTheParent) {
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.root(), bst.root()->getRight()->getParent());
}

TEST(BinarySearchTree, nullNodePointsToRoot){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ASSERT_EQ(bst.root(), bst.getNullNode()->getRight());
	ASSERT_EQ(bst.root(), bst.getNullNode()->getLeft());
}

TEST(BinarySearchTree, copyConstructor){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insertByValue(ft::make_pair(1, 0));
	bst.insertByValue(ft::make_pair(2, 0));

	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> reproduction(bst);

	ASSERT_EQ(1, reproduction.root()->content.first);
	ASSERT_EQ(2, reproduction.size());
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

	ASSERT_EQ(2, bst.root()->getLeft()->content.first);
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

TEST(BinarySearchTree, poppingLastNodeSetsAllInternalPointersToNullNode){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;
	bst.insert(ft::make_pair(1, 1));

	bst.popNode(1);

	ASSERT_TRUE(bst.root()->getLeft()->isNullNode());
	ASSERT_TRUE(bst.root()->getParent()->isNullNode());
	ASSERT_TRUE(bst.root()->getRight()->isNullNode());
	ASSERT_TRUE(bst.root()->isNullNode());
}

TEST(BinarySearchTree, getLowestItemOnEmptyTreeReturnsNullNode){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst;

	ft::SearchTreeStandardNode<int, int> *result = ft::getLowest(bst.root());

	ASSERT_EQ(result, bst.getNullNode());
}

TEST(BinarySearchTree, getLowestItem){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ft::SearchTreeStandardNode<int, int> *result = ft::getLowest(bst.root());

	ASSERT_EQ(1, result->content.first);
}

TEST(BinarySearchTree, getHighestItem){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> bst = generateFiveLevelTree();

	ft::SearchTreeStandardNode<int, int> *result = ft::getHighest(bst.root());

	ASSERT_EQ(20, result->content.first);
}


TEST(BinarySearchTree, equalityOfDifferingRootsIsFalse){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a;
	a.insert(ft::make_pair(1, 0));
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b;
	b.insert(ft::make_pair(3, 0));

	ASSERT_FALSE(a.isSameStructure(a.root(), b.root(), b.getNullNode()));
}

TEST(BinarySearchTree, equalityOfDifferingRightChildIsFalse){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a;
	a.insert(ft::make_pair(1, 0));
	a.insert(ft::make_pair(2, 0));
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b;
	b.insert(ft::make_pair(1, 0));
	b.insert(ft::make_pair(3, 0));

	ASSERT_FALSE(a.isSameStructure(a.root(), b.root(), b.getNullNode()));
}

TEST(BinarySearchTree, equalityOfOnlyEqualLeftChildsIsTrue){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a;
	a.insert(ft::make_pair(1, 0));
	a.insert(ft::make_pair(0, 0));
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b;
	b.insert(ft::make_pair(1, 0));
	b.insert(ft::make_pair(0, 0));

	ASSERT_TRUE(a.isSameStructure(a.root(), b.root(), b.getNullNode()));
}

TEST(BinarySearchTree, equalityOfUnEqualLeftChildsIsFalse){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a;
	a.insert(ft::make_pair(2, 0));
	a.insert(ft::make_pair(1, 0));
	a.insert(ft::make_pair(0, 0));
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b;
	b.insert(ft::make_pair(2, 0));
	b.insert(ft::make_pair(1, 0));

	ASSERT_FALSE(a.isSameStructure(a.root(), b.root(), b.getNullNode()));
}

TEST(BinarySearchTree, twoTreesAreEqualIfTheyHaveEqualOrderAndItems){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a = generateFiveLevelTree();
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b = generateFiveLevelTree();

	ASSERT_TRUE(a.isSameStructure(a.root(), b.root(), b.getNullNode()));
}

TEST(BinarySearchTree, sameValuesDifferentOrderIsNotSameStructure){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a = generateFiveLevelTree();
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b = generateFiveLevelTree();
	b.popNode(5);
	b.insert(ft::make_pair(5, 0));

	ASSERT_FALSE(a.isSameStructure(a.root(), b.root(), b.getNullNode()));
}

TEST(BinarySearchTree, twoEmptyBinaryTreesAreEqual){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a;
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b;

	ASSERT_TRUE(a == b);
}

TEST(BinarySearchTree, BinaryTreesEqualsItself){
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a = generateFiveLevelTree();

	ASSERT_TRUE(a == a);
}

TEST(BinarySearchTree, swappingEmptyTreeWithNonEmpty) {
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a = generateFiveLevelTree();
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b;

	a.swap(b);

	ASSERT_EQ(0, a.size());
}

TEST(BinarySearchTree, swappingTreeSwapsExtremeties) {
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a = generateFiveLevelTree();
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> b;
	ft::SearchTreeStandardNode<int, int> *aExtremetiesBefore = a.getExtremeties();

	a.swap(b);

	ASSERT_EQ(aExtremetiesBefore, b.getExtremeties());
	ASSERT_EQ(a.getNullNode(), a.getExtremeties()->getLeft());
}

TEST(BinarySearchTree, testPrint) {
ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode<int, int>> a = generateFiveLevelTree();

a.printTree();
}