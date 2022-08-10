#ifndef CONTAINERS_BINARYSEARCHTREE_HPP
#define CONTAINERS_BINARYSEARCHTREE_HPP

#include "Pair.hpp"

namespace ft {

	template<typename TKey, typename TValue>
	struct SearchTreeStandardNode {
		TKey key;
		TValue value;
		SearchTreeStandardNode *right;
		SearchTreeStandardNode *left;
		SearchTreeStandardNode *parent;

		SearchTreeStandardNode(const TKey &key, const TValue &value, SearchTreeStandardNode<TKey, TValue> *nullNode) : key(key), value(value), right(nullNode), left(nullNode), parent(nullNode) {
		}

		SearchTreeStandardNode(const ft::pair<TKey, TValue> &in, SearchTreeStandardNode<TKey, TValue> *nullNode) : key(in.first), value(in.second), right(nullNode), left(nullNode),
																												   parent(nullNode) {
		}

		SearchTreeStandardNode(const SearchTreeStandardNode<TKey, TValue> &rhs, SearchTreeStandardNode<TKey, TValue> *nullNode) : key(rhs.key), value(rhs.value), right(nullNode), left(nullNode),
																																  parent(nullNode) {
		}

		SearchTreeStandardNode() : left(NULL), right(NULL), parent(NULL){
		}

		virtual ~SearchTreeStandardNode(){

		}
	};

	template<typename TKey, typename TValue, template<typename, typename> class NodeType>
	class BinarySearchTree {
	protected:
		typedef NodeType<TKey, TValue> Node;
		Node nullNode;
		Node *rootNode;
	public:
		BinarySearchTree() : nullNode(), rootNode(&nullNode) {

		}

		BinarySearchTree &operator=(const BinarySearchTree &rhs) {
			Node *tmp = rhs.rootNode;
			if (rhs.rootNode == this->rootNode)
				return *this;
			copySubTree(rhs.rootNode, &rhs.nullNode, &rootNode);
			return *this;
		}

		virtual ~BinarySearchTree() {
			deleteSubTreeFrom(rootNode);
		}

		Node *findByKey(TKey &i) {
			Node *tmp = rootNode;

			while (tmp != &nullNode) {
				if (tmp->key == i)
					return (tmp);
				if (tmp->key > i) {
					if (tmp->left == &nullNode)
						return &nullNode;
					tmp = tmp->left;
				} else {
					if (tmp->right == &nullNode)
						return &nullNode;
					tmp = tmp->right;
				}
			}
			return NULL;
		}

		Node *getNullNode() {
			return &nullNode;
		}

		Node *insertByValue(ft::pair<TKey, TValue> in) {
			return insert(in);
		}

		Node *insert(ft::pair<TKey, TValue> const &in) {
			Node *newNode = new Node(in, &nullNode);
			Node *newParent;

			if (rootNode == &nullNode)
				rootNode = newNode;
			else {
				newParent = findInsertPlace(newNode);
				linkChildAndParent(newNode, &newParent);
			}
			return newNode;
		}

		Node *root() {
			return rootNode;
		}

		void popNode(TKey keyOfNodeToBeRemoved) {
			Node *nodeToBeRemoved = findByKey(keyOfNodeToBeRemoved);
			popNodeByPointer(nodeToBeRemoved);
		}

		void popNodeByPointer(Node *nodeToBeRemoved) {
			Node *parent = nodeToBeRemoved->parent;
			Node *tmp;

			if (nodeToBeRemoved == &nullNode)
				return;
			if (nodeToBeRemoved->left == &nullNode || nodeToBeRemoved->right == &nullNode) {
				linkChildrenToGrandParent(nodeToBeRemoved, parent);
				unlinkChildFromParent(nodeToBeRemoved, parent);
				delete nodeToBeRemoved;
			} else {
				tmp = getInorderSuccessor(nodeToBeRemoved, nodeToBeRemoved, nodeToBeRemoved->right);
				nodeToBeRemoved->key = tmp->key;
				nodeToBeRemoved->value = tmp->value;
				popNodeByPointer(tmp);
			}
		}

		void leftRotate(Node *pivot) {
			if (pivot->right == &nullNode)
				return ;
			Node *nodeToChangePlaceWith = pivot->right;

			pivot->right = nodeToChangePlaceWith->left;
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

		void rightRotate(Node *pivot) {
			if (pivot->left == &nullNode)
				return ;
			Node *nodeToChangePlaceWith = pivot->left;

			pivot->left = nodeToChangePlaceWith->right;
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

	private:

		void updateNodesForRotation(Node *pivot, Node *nodeToChangePlaceWith) {
			Node *parent = pivot->parent;

			if (nodeToChangePlaceWith->parent == rootNode)
				rootNode = nodeToChangePlaceWith;
			linkChildAndParent(nodeToChangePlaceWith, &parent);
			linkChildAndParent(pivot, &nodeToChangePlaceWith);
		}

		Node *getInorderSuccessor(Node *localRoot, Node *biggerThan,
								  Node *currentOptimum) {
			Node *leftMinimum = &nullNode;
			Node *rightMinimum = &nullNode;

			if (localRoot->right == &nullNode && localRoot->left == &nullNode) {
				if (localRoot->key < currentOptimum->key && localRoot->key > biggerThan->key)
					return localRoot;
				return currentOptimum;
			}
			leftMinimum = getInorderSuccessor(localRoot->left, biggerThan, currentOptimum);
			rightMinimum = getInorderSuccessor(localRoot->right, biggerThan, currentOptimum);
			if (leftMinimum != &nullNode && leftMinimum->key > biggerThan->key && leftMinimum->key < currentOptimum->key)
				return leftMinimum;
			if (rightMinimum != &nullNode && rightMinimum->key > biggerThan->key && rightMinimum->key < currentOptimum->key)
				return rightMinimum;
			return currentOptimum;
		}

		void unlinkChildFromParent(const Node *nodeToBeRemoved, Node *parent) {
			if (nodeToBeRemoved == &nullNode)
				return;
			if (parent->left == nodeToBeRemoved) {
				parent->left->parent = &nullNode;
				parent->left = &nullNode;
			}
			if (parent->right == nodeToBeRemoved) {
				parent->right->parent = &nullNode;
				parent->right = &nullNode;
			}
		}

		void linkChildAndParent(Node *newNode, Node **newParent) const {
			if (*newParent != &nullNode) {
				if (newNode->key < (*newParent)->key)
					(*newParent)->left = newNode;
				else
					(*newParent)->right = newNode;
			}
			newNode->parent = *newParent;
		}

		void linkChildrenToGrandParent(Node *parent, Node *&grandParent) const {
			if (parent->left != &nullNode)
				linkChildAndParent(parent->left, &grandParent);
			if (parent->right != &nullNode)
				linkChildAndParent(parent->right, &grandParent);
		}

		Node *findInsertPlace(const Node *newNode) const {
			Node *tmp = rootNode;

			while ((tmp->left != &nullNode || tmp->right != &nullNode)) {
				if (newNode->key < tmp->key) {
					if (tmp->left == &nullNode)
						return tmp;
					tmp = tmp->left;
				} else {
					if (tmp->right == &nullNode)
						return tmp;
					tmp = tmp->right;
				}
			}
			return tmp;
		}

		void deleteSubTreeFrom(Node *localRoot) {
			if (localRoot == &nullNode)
				return;
			deleteSubTreeFrom((localRoot)->left);
			deleteSubTreeFrom((localRoot)->right);
			delete localRoot;
		}

		void copySubTree(Node *source, const Node *sourceNullNode, Node **dest) {
			Node *newNode;

			if (source != sourceNullNode) {
				newNode = new Node(*source, &nullNode);
				if (*dest == &nullNode)
					*dest = newNode;
				linkChildAndParent(newNode, dest);
				if (source->right != &nullNode)
					copySubTree(source->right, sourceNullNode, &newNode);
				if (source->left != &nullNode)
					copySubTree(source->left, sourceNullNode, &newNode);
			}
		}
	};
}

#endif //CONTAINERS_BINARYSEARCHTREE_HPP
