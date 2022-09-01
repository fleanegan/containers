#ifndef CONTAINERS_REDBLACKTREE_H
#define CONTAINERS_REDBLACKTREE_H

#include "BinarySearchTree.hpp"
#include "Pair.hpp"

namespace ft {

	template<typename TKey, typename TValue>
	struct RedBlackNode {
		TKey key;
		TValue value;
		RedBlackNode *right;
		RedBlackNode *left;
		RedBlackNode *parent;
		bool isBlack;

		RedBlackNode(const TKey &key, const TValue &value, RedBlackNode<TKey, TValue> *nullNode) : key(key),
																								   value(value),
																								   right(nullNode),
																								   left(nullNode),
																								   parent(nullNode),
																								   isBlack(false) {
		}

		RedBlackNode(const ft::pair<TKey, TValue> &in, RedBlackNode<TKey, TValue> *nullNode) : key(in.first),
																							   value(in.second),
																							   right(nullNode),
																							   left(nullNode),
																							   parent(nullNode),
																							   isBlack(false) {
		}

		RedBlackNode(const RedBlackNode<TKey, TValue> &rhs, RedBlackNode<TKey, TValue> *nullNode) : key(rhs.key),
																									value(rhs.value),
																									right(nullNode),
																									left(nullNode),
																									parent(nullNode),
																									isBlack(false) {
		}

		RedBlackNode() : left(NULL), right(NULL), parent(NULL), isBlack(false) {
		}

		virtual ~RedBlackNode() {

		}
	};

	template<typename TKey, typename TValue>
	class RedBlackTree : public BinarySearchTree<TKey, TValue, RedBlackNode> {
	public:
		typedef RedBlackNode<TKey, TValue> Node;

		RedBlackTree() : BinarySearchTree<TKey, TValue, ft::RedBlackNode>() {
			this->nullNode.isBlack = true;
		}

		RedBlackTree(const RedBlackTree<TKey, TValue> &rhs) : BinarySearchTree<TKey, TValue, ft::RedBlackNode>() {
			BinarySearchTree<TKey, TValue, ft::RedBlackNode>::operator=(rhs);
			this->nullNode.isBlack = true;
		}

		RedBlackTree<TKey,TValue>&
		operator=(const RedBlackTree<TKey,TValue>& rhs) {
			BinarySearchTree<TKey, TValue, ft::RedBlackNode>::operator=(rhs);
			return *this;
		}

		Node *insertByValue(ft::pair<TKey, TValue> const &in) {
			return insert(in);
		}

		Node *insert(ft::pair<TKey, TValue> const &in) {
			Node *newNode = BinarySearchTree<TKey, TValue, ft::RedBlackNode>::insert(in);
			Node *currentNode = newNode;
			Node *parent;
			Node *grandParent;

			fixupInsertion(currentNode, parent, grandParent);
			return newNode;
		}

		void popNodeByPointer(Node *nodeToBeRemoved) {
			Node *successor;
			Node *potentialColourTrouble;
			bool isNodeToBeRemovedBlack = nodeToBeRemoved->isBlack;

			if (nodeToBeRemoved == &this->nullNode)
				return;
			if (nodeToBeRemoved->right == &this->nullNode) {
				potentialColourTrouble = nodeToBeRemoved->left;
				this->replaceNode(nodeToBeRemoved, nodeToBeRemoved->left);
			} else if (nodeToBeRemoved->left == &this->nullNode) {
				potentialColourTrouble = nodeToBeRemoved->right;
				this->replaceNode(nodeToBeRemoved, nodeToBeRemoved->right);
			} else {
				successor = this->getInorderSuccessor(nodeToBeRemoved->right, nodeToBeRemoved, nodeToBeRemoved->right);
				isNodeToBeRemovedBlack = successor->isBlack;
				potentialColourTrouble = successor->right;
				replaceNodeBySuccessor(nodeToBeRemoved, successor);
				successor->isBlack = nodeToBeRemoved->isBlack;
			}
			this->deleteNodeWithCleanUp(nodeToBeRemoved);
			if (isNodeToBeRemovedBlack) {
				fixupDeletion(potentialColourTrouble);
			}
		}

		bool isValid() {
			ft::vector<int> blackNodeCountPerBranch;
			countBranches(this->rootNode, 0, blackNodeCountPerBranch);
			if (!this->rootNode->isBlack)
				return false;
			if (!isBlackCountSameInAllBranches(blackNodeCountPerBranch))
				return false;
			if (isContainingDoubleRed(this->rootNode))
				return false;
			return true;
		}

	protected:
		virtual void fixupDeletion(Node *troubleMaker) {
			Node *parent = troubleMaker->parent;
			Node *sibling;

			while (troubleMaker != this->rootNode && troubleMaker->isBlack  && troubleMaker != &this->nullNode) {
				sibling = getSibling(troubleMaker, parent);
				if (sibling->isBlack == false)
					troubleMaker = fixupDeletionCaseOne(parent, sibling);
				if (sibling->left->isBlack && sibling->right->isBlack)
					troubleMaker = fixupDeletionCaseTwo(parent, sibling);
				else if (isOuterChildBlack(sibling))
					fixupDeletionCaseThree(parent, &sibling);
				else
					troubleMaker = fixupDeletionCaseFour(parent, sibling);
			}
			troubleMaker->isBlack = true;
		}

		void fixupInsertion(Node *currentNode, Node *parent, Node *grandParent) {
			Node *uncle;

			while (currentNode->parent->isBlack == false) {
				parent = currentNode->parent;
				grandParent = parent->parent;
				uncle = getUncle(grandParent, parent);
				if (uncle->isBlack == parent->isBlack) {
					fixupColourChange(parent, grandParent, uncle);
					currentNode = grandParent;
				} else {
					currentNode = fixupRotate(currentNode, parent, grandParent);
				}
			}
			this->rootNode->isBlack = true;
		}

	private:
		Node *fixupRotate(Node *currentNode, Node *parent, Node *grandParent) {
			if (parent == grandParent->right)
				return fixupRotateRightBranch(currentNode, parent, grandParent);
			else
				return fixupRotateLeftBranch(currentNode, parent, grandParent);
		}

		Node *getUncle(Node *grandParent, Node *parent) const {
			if (parent == grandParent->right)
				return grandParent->left;
			return grandParent->right;
		}

		Node *fixupRotateRightBranch(Node *currentNode, Node *parent, Node *grandParent) {
			if (currentNode == parent->right) {
				fixupInnerRotationReColour(parent, grandParent);
				this->leftRotate(grandParent);
				return grandParent;
			}
			this->rightRotate(parent);
			return parent;
		}

		Node *fixupRotateLeftBranch(Node *currentNode, Node *parent, Node *grandParent) {
			if (currentNode == parent->left) {
				fixupInnerRotationReColour(parent, grandParent);
				this->rightRotate(grandParent);
				return grandParent;
			}
			this->leftRotate(parent);
			return parent;
		}

		void fixupInnerRotationReColour(Node *parent, Node *grandParent) {
			parent->isBlack = true;
			grandParent->isBlack = false;
		}

		void fixupColourChange(Node *parent, Node *grandParent, Node *uncle) {
			uncle->isBlack = true;
			parent->isBlack = true;
			grandParent->isBlack = false;
		}

		void replaceNodeBySuccessor(Node *nodeToBeRemoved, Node *successor) {
			if (successor->parent != nodeToBeRemoved) {
				this->replaceNode(successor, successor->right);
				successor->right = nodeToBeRemoved->right;
				successor->right->parent = successor;
			} else
				successor->right->parent = successor;
			this->replaceNode(nodeToBeRemoved, successor);
			successor->left = nodeToBeRemoved->left;
			successor->left->parent = successor;
		}
		Node *fixupDeletionCaseOne(Node *parent, Node *sibling) {
			Node *troubleMaker;

			sibling->isBlack = true;
			parent->isBlack = false;
			if (sibling == parent->left) {
				this->leftRotate(parent);
				troubleMaker = sibling->right;
			} else {
				this->rightRotate(parent);
				troubleMaker = sibling->left;
			}
			return troubleMaker;
		}

		Node *fixupDeletionCaseTwo(Node *parent, Node *sibling) {
			Node *troubleMaker;

			sibling->isBlack = false;
			troubleMaker = parent;
			return troubleMaker;
		}

		bool isOuterChildBlack(const Node *sibling) const {
			if (sibling == sibling->parent->right)
				return sibling->right->isBlack;
			return sibling->left->isBlack;
		}

		void fixupDeletionCaseThree(Node *parent, Node **sibling) {
			(*sibling)->isBlack = false;
			if ((*sibling) == parent->right) {
				(*sibling)->left->isBlack = true;
				this->rightRotate((*sibling));
				(*sibling) = parent->right;
			} else {
				(*sibling)->right->isBlack = true;
				this->leftRotate((*sibling));
				(*sibling) = parent->left;
			}
		}

		Node *fixupDeletionCaseFour(Node *parent, Node *sibling) {
			Node *troubleMaker;

			sibling->isBlack = parent->isBlack;
			parent->isBlack = true;
			if (sibling == parent->right) {
				sibling->right->isBlack = true;
				this->leftRotate(parent);
			} else{
				sibling->left->isBlack = true;
				this->rightRotate(parent);
			}
			troubleMaker = this->rootNode;
			return troubleMaker;
		}

		Node *getSibling(const Node *troubleMaker, Node *parent) const {
			Node *sibling;

			if (troubleMaker == parent->left)
				sibling = parent->right;
			else
				sibling = parent->left;
			return sibling;
		}

		void countBranches(Node *current, int sum, ft::vector<int> &result) {
			if (current != &this->nullNode) {
				sum += current->isBlack;
				countBranches(current->right, sum, result);
				countBranches(current->left, sum, result);
				if (current->right == &this->nullNode && current->left == &this->nullNode)
					result.push_back(sum);
			}
		}

		double isContainingDoubleRed(Node *current) {
			if (current != &this->nullNode) {
				if (current->isBlack == current->parent->isBlack && current->isBlack == false)
					return true;
				return isContainingDoubleRed(current->right) || isContainingDoubleRed(current->left);
			}
			return false;
		}

		bool isBlackCountSameInAllBranches(vector<int> &blackNodeCountPerBranch) const {
			vector<int>::iterator start = blackNodeCountPerBranch.begin();
			vector<int>::iterator end = blackNodeCountPerBranch.end();

			while (start != end) {
				if (*start != blackNodeCountPerBranch.front())
					return false;
				start++;
			}
			return true;
		}
	};
}
#endif //CONTAINERS_REDBLACKTREE_H
