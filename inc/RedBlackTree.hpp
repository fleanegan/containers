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
		bool black;

		RedBlackNode(const TKey &key, const TValue &value, RedBlackNode<TKey, TValue> *nullNode) : key(key),
																								   value(value),
																								   right(nullNode),
																								   left(nullNode),
																								   parent(nullNode),
																								   black(false) {
		}

		RedBlackNode(const ft::pair<TKey, TValue> &in, RedBlackNode<TKey, TValue> *nullNode) : key(in.first),
																							   value(in.second),
																							   right(nullNode),
																							   left(nullNode),
																							   parent(nullNode),
																							   black(false) {
		}

		RedBlackNode(const RedBlackNode<TKey, TValue> &rhs, RedBlackNode<TKey, TValue> *nullNode) : key(rhs.key),
																									value(rhs.value),
																									right(nullNode),
																									left(nullNode),
																									parent(nullNode),
																									black(false) {
		}

		RedBlackNode() : left(NULL), right(NULL), parent(NULL), black(false) {
		}

		virtual ~RedBlackNode() {

		}
	};

	template<typename TKey, typename TValue>
	class RedBlackTree : public BinarySearchTree<TKey, TValue, RedBlackNode> {
	public:
		typedef RedBlackNode<TKey, TValue> Node;

		RedBlackTree() : BinarySearchTree<TKey, TValue, ft::RedBlackNode>() {
			this->nullNode.black = true;
		}

		Node *insertByValue(ft::pair<TKey, TValue> const &in) {
			return insert(in);
		}

		Node *insert(ft::pair<TKey, TValue> const &in) {
			Node *newNode = BinarySearchTree<TKey, TValue, ft::RedBlackNode>::insert(in);
			Node *currentNode = newNode;
			Node *parent;
			Node *grandParent;
			fixup(currentNode, parent, grandParent);

			return newNode;
		}

		void fixup(Node *currentNode, Node *parent, Node *grandParent) {
			Node *uncle;

			while (currentNode->parent->black == false) {
				parent = currentNode->parent;
				grandParent = parent->parent;
				uncle = getUncle(grandParent, parent);
				if (uncle->black == parent->black) {
					fixupColourChange(parent, grandParent, uncle);
					currentNode = grandParent;
				} else {
					fixupRotate(currentNode, parent, grandParent);
					currentNode = parent;
				}
			}
			this->rootNode->black = true;
		}

		void fixupRotate(const Node *currentNode, Node *parent, Node *grandParent) {
			if (parent == grandParent->right)
				fixupRotateRightBranch(currentNode, parent, grandParent);
			else
				fixupRotateLeftBranch(currentNode, parent, grandParent);
		}

		Node *getUncle(Node *grandParent, Node *parent) const {
			if (parent == grandParent->right)
				return grandParent->left;
			return grandParent->right;
		}

		void fixupRotateRightBranch(const Node *currentNode, Node *parent, Node *grandParent) {
			if (currentNode == parent->right) {
				fixupPrepareInnerRotation(parent, grandParent);
				this->leftRotate(grandParent);
			}
			else
				this->rightRotate(parent);
		}

		void fixupRotateLeftBranch(const Node *currentNode, Node *parent, Node *grandParent) {
			if (currentNode == parent->left) {
				fixupPrepareInnerRotation(parent, grandParent);
				this->rightRotate(grandParent);
			}
			else
				this->leftRotate(parent);
		}

		void fixupPrepareInnerRotation(Node *parent, Node *grandParent) const {
			parent->black = true;
			grandParent->black = false;
		}

		void fixupColourChange(Node *parent, Node *grandParent, Node *uncle) const {
			uncle->black = true;
			parent->black = true;
			grandParent->black = false;
		}
	};
}
#endif //CONTAINERS_REDBLACKTREE_H
