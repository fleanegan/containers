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
			Node *uncle;

			while (currentNode->parent->black == false) {
				parent = currentNode->parent;
				grandParent = parent->parent;
				if (parent == grandParent->right) {
					uncle = grandParent->left;
					if (uncle->black == parent->black) { // colorChange
						parent->black = true;
						uncle->black = true;
						grandParent->black = false;
						currentNode = grandParent;
					} else if (currentNode == parent->right) {
						currentNode = parent;
						this->leftRotate(grandParent);
					} else {
						parent->black = true;
						grandParent->black = false;
						currentNode = parent;
						this->rightRotate(grandParent);
					}
				} else { //parent == grandParent->left
					uncle = grandParent->right;
					if (false) {

					} else if (currentNode == parent->right) {
						currentNode = parent;
						this->leftRotate(currentNode);
					} else {
						parent->black = true;
						grandParent->black = false;
						currentNode = parent;
						this->rightRotate(grandParent);
					}
				}
			}
			this->rootNode->black = true;
			return newNode;
		}
	};
}
#endif //CONTAINERS_REDBLACKTREE_H
