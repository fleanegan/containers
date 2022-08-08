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

	template<typename TKey, typename TValue, template<typename, typename> class NodeType>
	class BinarySearchTree {
	private:
		typedef NodeType<TKey, TValue> Node;
		Node *rootNode;
	public:
		BinarySearchTree() : rootNode() {

		}

		BinarySearchTree &operator=(const BinarySearchTree &rhs) {
			Node *tmp = rhs.rootNode;
			if (rhs.rootNode == this->rootNode)
				return *this;
			copySubTree(rhs.rootNode, &rootNode);
			return *this;
		}

		virtual ~BinarySearchTree() {
			deleteSubTreeFrom(&rootNode);
		}

		Node *findByKey(TKey &i) {
			Node *tmp = rootNode;

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
			insert_ref(in);
		}

		void insert_ref(ft::pair<TKey, TValue> const &in) {
			Node *newNode = new Node(in);
			Node *newParent = rootNode;

			if (rootNode == NULL)
				rootNode = newNode;
			else {
				newParent = findInsertPlace(newNode);
				linkChildAndParent(newNode, &newParent);
			}
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

			if (nodeToBeRemoved == NULL)
				return;
			if (nodeToBeRemoved->left == NULL || nodeToBeRemoved->right == NULL) {
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
			Node *parent = pivot->parent;
			Node *nodeToChangePlaceWith = pivot->right;

			if (nodeToChangePlaceWith->parent == rootNode)
				rootNode = nodeToChangePlaceWith;
			pivot->right = nodeToChangePlaceWith->left;
			linkChildAndParent(nodeToChangePlaceWith, &parent);
			linkChildAndParent(pivot, &nodeToChangePlaceWith);
		}

		void rightRotate(Node *pivot) {
			Node *parent = pivot->parent;
			Node *nodeToChangePlaceWith = pivot->left;

			if (nodeToChangePlaceWith->parent == rootNode)
				rootNode = nodeToChangePlaceWith;
			pivot->left = nodeToChangePlaceWith->right;
			linkChildAndParent(nodeToChangePlaceWith, &parent);
			linkChildAndParent(pivot, &nodeToChangePlaceWith);
		}

	private:

		Node *getInorderSuccessor(Node *localRoot, Node *biggerThan,
								  Node *currentOptimum) {
			Node *leftMinimum = NULL;
			Node *rightMinimum = NULL;

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

		void unlinkChildFromParent(const Node *nodeToBeRemoved, Node *parent) const {
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

		void linkChildAndParent(Node *newNode, Node **newParent) const {
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

		void linkChildrenToGrandParent(Node *parent, Node *&grandParent) const {
			if (parent->left != NULL)
				linkChildAndParent(parent->left, &grandParent);
			if (parent->right != NULL)
				linkChildAndParent(parent->right, &grandParent);
		}

		Node *findInsertPlace(const Node *newNode) const {
			Node *tmp = rootNode;

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

		void deleteSubTreeFrom(Node **localRoot) {
			if (localRoot == NULL || *localRoot == NULL)
				return;
			deleteSubTreeFrom(&(*localRoot)->left);
			deleteSubTreeFrom(&(*localRoot)->right);
			delete *localRoot;
			localRoot = NULL;
		}

		void copySubTree(Node *source, Node **dest) {
			Node *newNode;

			if (source != NULL) {
				newNode = new Node(*source);
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
