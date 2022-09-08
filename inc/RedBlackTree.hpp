#ifndef CONTAINERS_REDBLACKTREE_H
#define CONTAINERS_REDBLACKTREE_H

#include "BinarySearchTree.hpp"
#include "Pair.hpp"

namespace ft {

	template<typename TKey, typename TValue>
	struct RedBlackNode {
		ft::pair<const TKey, TValue> content;
		RedBlackNode *right;
		RedBlackNode *left;
		RedBlackNode *parent;
		bool isBlack;

		RedBlackNode(const TKey &key, const TValue &value, RedBlackNode<TKey, TValue> *nullNode) : content(key, value),
																								   right(nullNode),
																								   left(nullNode),
																								   parent(nullNode),
																								   isBlack(false) {
		}

		RedBlackNode(const ft::pair<TKey, TValue> &in, RedBlackNode<TKey, TValue> *nullNode) : content(in),
																							   right(nullNode),
																							   left(nullNode),
																							   parent(nullNode),
																							   isBlack(false) {
		}

		RedBlackNode(const RedBlackNode<TKey, TValue> &rhs, RedBlackNode<TKey, TValue> *nullNode) : content(rhs.content),
																									right(nullNode),
																									left(nullNode),
																									parent(nullNode),
																									isBlack(false) {
		}

		RedBlackNode(const RedBlackNode<TKey, TValue> &rhs) :	content(rhs.content),
																right(rhs.right),
																left(rhs.left),
																parent(rhs.parent),
																isBlack(rhs.isBlack) {
		}


		RedBlackNode() : right(this), left(this), parent(this), isBlack(false) {
		}

		virtual ~RedBlackNode() {

		}
	};

	template<typename TKey, typename TValue, typename NodeType = ft::RedBlackNode<TKey, TValue>, typename Compare = std::less<TKey>, typename Allocator = std::allocator<NodeType> >
	class RedBlackTree : public ft::BinarySearchTree<TKey, TValue, ft::RedBlackNode<TKey, TValue> > {
	public:
		typedef TKey key_type;
		typedef TValue mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef NodeType Node;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

	public:

		RedBlackTree(const key_compare &compare = std::less<TKey>(), const allocator_type &alloc = allocator_type())
				: ft::BinarySearchTree<key_type, mapped_type, Node, key_compare, allocator_type>(compare, alloc) {
			this->nullNode.isBlack = true;
		}

		RedBlackTree(const RedBlackTree<key_type, mapped_type, NodeType> &rhs, key_compare, const allocator_type &alloc = allocator_type())
				: ft::BinarySearchTree<key_type, mapped_type, NodeType, key_compare, allocator_type>(alloc) {
			BinarySearchTree<key_type, mapped_type, key_compare, Node>::operator=(rhs);
			this->nullNode.isBlack = true;
		}

		RedBlackTree<key_type, mapped_type, NodeType> &
		operator=(const RedBlackTree<key_type, mapped_type, key_compare, NodeType> &rhs) {
			BinarySearchTree<key_type, mapped_type, key_compare, Node>::operator=(rhs);
			return *this;
		}

		pointer insertByValue(ft::pair<key_type, mapped_type> const &in) {
			return insert(in);
		}

		pointer insert(ft::pair<key_type, mapped_type> const &in) {
			Node *newNode = BinarySearchTree<key_type, mapped_type, Node>::insert(in);
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

			while (troubleMaker != this->rootNode && troubleMaker->isBlack && troubleMaker != &this->nullNode) {
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
		pointer fixupRotate(Node *currentNode, Node *parent, Node *grandParent) {
			if (parent == grandParent->right)
				return fixupRotateRightBranch(currentNode, parent, grandParent);
			else
				return fixupRotateLeftBranch(currentNode, parent, grandParent);
		}

		pointer getUncle(Node *grandParent, Node *parent) const {
			if (parent == grandParent->right)
				return grandParent->left;
			return grandParent->right;
		}

		pointer fixupRotateRightBranch(Node *currentNode, Node *parent, Node *grandParent) {
			if (currentNode == parent->right) {
				fixupInnerRotationReColour(parent, grandParent);
				this->leftRotate(grandParent);
				return grandParent;
			}
			this->rightRotate(parent);
			return parent;
		}

		pointer fixupRotateLeftBranch(Node *currentNode, Node *parent, Node *grandParent) {
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

		pointer fixupDeletionCaseOne(Node *parent, Node *sibling) {
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

		pointer fixupDeletionCaseTwo(Node *parent, Node *sibling) {
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

		pointer fixupDeletionCaseFour(Node *parent, Node *sibling) {
			Node *troubleMaker;

			sibling->isBlack = parent->isBlack;
			parent->isBlack = true;
			if (sibling == parent->right) {
				sibling->right->isBlack = true;
				this->leftRotate(parent);
			} else {
				sibling->left->isBlack = true;
				this->rightRotate(parent);
			}
			troubleMaker = this->rootNode;
			return troubleMaker;
		}

		pointer getSibling(const Node *troubleMaker, Node *parent) const {
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

		bool isContainingDoubleRed(Node *current) {
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
