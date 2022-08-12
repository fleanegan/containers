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

			if (rootNode == &nullNode){
				rootNode = newNode;
				nullNode.right = newNode;
				nullNode.left = newNode;
			}
			else {
				newParent = findInsertPlace(newNode);
				linkChildAndParent(newNode, &newParent);
			}
			return newNode;
		}

		Node *root() {
			return rootNode;
		}

		virtual void popNode(TKey keyOfNodeToBeRemoved) {
			Node *nodeToBeRemoved = findByKey(keyOfNodeToBeRemoved);
			popNodeByPointer(nodeToBeRemoved);
		}

		virtual void popNodeByPointer(Node *nodeToBeRemoved) {
			Node *successor;

			if (nodeToBeRemoved == &nullNode)
				return;
			if (nodeToBeRemoved->right == &nullNode)
				replaceNode(nodeToBeRemoved, nodeToBeRemoved->left);
			else if (nodeToBeRemoved->left == &nullNode) {
				replaceNode(nodeToBeRemoved, nodeToBeRemoved->right);
			}
			else {
				successor = getInorderSuccessor(nodeToBeRemoved->right, nodeToBeRemoved, nodeToBeRemoved->right);
				if (successor->parent != nodeToBeRemoved){
					replaceNode(successor, successor->right);
					successor->right = nodeToBeRemoved->right;
					successor->right->parent = successor;
				}
				replaceNode(nodeToBeRemoved, successor);
				successor->left = nodeToBeRemoved->left;
				successor->left->parent = successor;
			}
			deleteNodeWithCleanUp(nodeToBeRemoved);
		}

		void replaceNode(Node *nodeToBeReplaced, Node *replacer) {
			if (nodeToBeReplaced->parent == &nullNode)
			{
				rootNode = &nullNode;
				linkChildAndParent(replacer, &rootNode);
			}
			else if (nodeToBeReplaced == nodeToBeReplaced->parent->left)
				nodeToBeReplaced->parent->left = replacer;
			else
				nodeToBeReplaced->parent->right = replacer;
			replacer->parent = nodeToBeReplaced->parent;
		}

		void leftRotate(Node *pivot) {
			if (pivot->right == &nullNode)
				return ;
			Node *nodeToChangePlaceWith = pivot->right;

			pivot->right = nodeToChangePlaceWith->left;
			nodeToChangePlaceWith->left->parent = pivot;
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

		void rightRotate(Node *pivot) {
			if (pivot->left == &nullNode)
				return ;
			Node *nodeToChangePlaceWith = pivot->left;

			pivot->left = nodeToChangePlaceWith->right;
			nodeToChangePlaceWith->right->parent = pivot;
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

		void linkChildAndParent(Node *newNode, Node **newParent) {
			if (*newParent != &nullNode) {
				if (newNode->key < (*newParent)->key)
					(*newParent)->left = newNode;
				else
					(*newParent)->right = newNode;
			}
			else {
				nullNode.right = newNode;
				nullNode.left = newNode;
				rootNode = newNode;
			}
			newNode->parent = *newParent;
		}

		Node *linkChildToGrandParent(Node *parent, Node *&grandParent) {
			Node *leftover;

			if (parent->left != &nullNode)
				leftover = parent->right;
			else if (parent->right != &nullNode)
				leftover = parent->right;
			else
				return &nullNode;
			linkChildAndParent(leftover, &grandParent);
			return leftover;
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
	protected:
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

		void deleteNodeWithCleanUp(const Node *nodeToBeRemoved) {
			if (nodeToBeRemoved == rootNode) {
				rootNode = &nullNode;
				nullNode.right = &nullNode;
				nullNode.left = &nullNode;
			}
			delete nodeToBeRemoved;
		}
	};
}

#endif //CONTAINERS_BINARYSEARCHTREE_HPP
