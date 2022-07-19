#ifndef CONTAINERS_BINARYSEARCHTREE_HPP
#define CONTAINERS_BINARYSEARCHTREE_HPP

namespace ft {

	template<typename TKey, typename TValue>
	struct Node {
		TKey key;
		TValue value;
		Node *right;
		Node *left;
		Node *parent;

		Node(const TKey &key, const TValue &value) : key(key), value(value), right(NULL), left(NULL), parent(NULL) {
		}

		Node(const ft::pair<TKey, TValue> &in) : key(in.first), value(in.second), right(NULL), left(NULL),
												 parent(NULL) {
		}
	};

	template<typename TKey, typename TValue>
	class BinarySearchTree {
	private:
		Node<TKey, TValue> *rootNode;
	public:
		BinarySearchTree() : rootNode() {

		}

		BinarySearchTree &operator=(const BinarySearchTree &rhs) {
			Node<TKey, TValue> *tmp = rhs.rootNode;
			if (rhs.rootNode == this->rootNode)
				return *this;
			copySubTree(rhs.rootNode, &rootNode);
			return *this;
		}

		virtual ~BinarySearchTree() {
			deleteSubTreeFrom(&rootNode);
		}

		Node<TKey, TValue> *findByKey(TKey i) {
			Node<TKey, TValue> *tmp = rootNode;

			while (tmp != NULL) {
				if (tmp->key == i)
					return (tmp);
				if (tmp->key > i) {
					if (tmp->left == NULL)
						return NULL;
					tmp = tmp->left;
				} else {
					if (tmp->right == NULL)
						return NULL;
					tmp = tmp->right;
				}
			}
			return NULL;
		}

		void insert(ft::pair<TKey, TValue> in) {
			Node<TKey, TValue> *newNode = new ::ft::Node<TKey, TValue>(in);
			Node<TKey, TValue> *newParent = rootNode;

			if (rootNode == NULL)
				rootNode = newNode;
			else {
				newParent = findInsertPlace(newNode);
				linkChildAndParent(newNode, &newParent);
			}
		}

		Node<TKey, TValue> *root() {
			return rootNode;
		}

		void popNode(TKey keyOfNodeToBeRemoved) {
			Node<TKey, TValue> *nodeToBeRemoved = findByKey(keyOfNodeToBeRemoved);
			popNodeByPointer(nodeToBeRemoved);

		}

		void popNodeByPointer(Node<TKey, TValue> *nodeToBeRemoved) {
			Node<TKey, TValue> *parent = nodeToBeRemoved->parent;
			Node<TKey, TValue> *tmp;

			if (nodeToBeRemoved == NULL)
				return;
			if (nodeToBeRemoved->left == NULL || nodeToBeRemoved->right == NULL) {
				linkChildrenToGrandParent(nodeToBeRemoved, parent);
				unlinkChildFromParent(nodeToBeRemoved, parent);
				delete nodeToBeRemoved;
			} else {
				tmp = getInorderSuccessor(nodeToBeRemoved, nodeToBeRemoved, NULL);
				nodeToBeRemoved->key = tmp->key;
				nodeToBeRemoved->value = tmp->value;
				popNodeByPointer(tmp);
			}
		}

		void linkChildrenToGrandParent(Node <TKey, TValue> *parent, Node <TKey, TValue> *&grandParent) const {
			if (parent->left != NULL)
				linkChildAndParent(parent->left, &grandParent);
			if (parent->right != NULL)
				linkChildAndParent(parent->right, &grandParent);
		}

	private:
		Node<TKey, TValue> *getInorderSuccessor(Node<TKey, TValue> *localRoot, Node<TKey, TValue> *biggerThan,
												Node<TKey, TValue> *currentOptimum) {
			Node<TKey, TValue> *leftMinimum = NULL;
			Node<TKey, TValue> *rightMinimum = NULL;

			if (localRoot == NULL)
				return NULL;
			if (currentOptimum == NULL){
				currentOptimum = localRoot->right;
				if (currentOptimum == NULL)
					localRoot->left;
			}
			if (localRoot->right == NULL && localRoot->left == NULL) {
				if (localRoot->key < currentOptimum->key && localRoot->key > biggerThan->key)
					return localRoot;
				return currentOptimum;
			}
			leftMinimum = getInorderSuccessor(localRoot->left, biggerThan, currentOptimum);
			rightMinimum = getInorderSuccessor(localRoot->right, biggerThan, currentOptimum);
			if (leftMinimum != NULL && leftMinimum->key > biggerThan->key && leftMinimum->key < currentOptimum->key)
				return leftMinimum;
			if (rightMinimum != NULL && rightMinimum->key > biggerThan->key && rightMinimum->key < currentOptimum->key)
				return rightMinimum;
			return currentOptimum;
		}

		void unlinkChildFromParent(const Node<TKey, TValue> *nodeToBeRemoved, Node<TKey, TValue> *parent) const {
			if (nodeToBeRemoved == NULL)
				return;
			if (parent->left == nodeToBeRemoved) {
				parent->left->parent = NULL;
				parent->left = NULL;
			}
			if (parent->right == nodeToBeRemoved) {
				parent->right->parent = NULL;
				parent->right = NULL;
			}
		}

		void linkChildAndParent(Node<TKey, TValue> *newNode, Node<TKey, TValue> **newParent) const {
			if (newNode == NULL)
				return;
			if (*newParent != NULL) {
				if (newNode->key < (*newParent)->key)
					(*newParent)->left = newNode;
				else
					(*newParent)->right = newNode;
			} else
				*newParent = newNode;
			newNode->parent = *newParent;
		}

		Node<TKey, TValue> *findInsertPlace(const Node<TKey, TValue> *newNode) const {
			Node<TKey, TValue> *tmp = rootNode;

			while ((tmp->left != NULL || tmp->right != NULL)) {
				if (newNode->key < tmp->key) {
					if (tmp->left == NULL)
						return tmp;
					tmp = tmp->left;
				} else {
					if (tmp->right == NULL)
						return tmp;
					tmp = tmp->right;
				}
			}
			return tmp;
		}

		void deleteSubTreeFrom(Node<TKey, TValue> **localRoot) {
			if (localRoot == NULL || *localRoot == NULL)
				return;
			deleteSubTreeFrom(&(*localRoot)->left);
			deleteSubTreeFrom(&(*localRoot)->right);
			delete *localRoot;
			localRoot = NULL;
		}

		void copySubTree(Node<TKey, TValue> *source, Node<TKey, TValue> **dest) {
			Node<TKey, TValue> *newNode;

			if (source != NULL) {
				newNode = new Node<TKey, TValue>(*source);
				linkChildAndParent(newNode, dest);
				if (source->right != NULL)
					copySubTree(source->right, &newNode);
				if (source->left != NULL)
					copySubTree(source->left, &newNode);
			}
		}
	};
}

#endif //CONTAINERS_BINARYSEARCHTREE_HPP
