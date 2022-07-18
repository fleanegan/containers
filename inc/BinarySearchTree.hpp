#ifndef CONTAINERS_BINARYSEARCHTREE_HPP
#define CONTAINERS_BINARYSEARCHTREE_HPP

namespace ft {

	template<typename TKey, typename TValue>
	struct Node {
		TKey key;
		TValue value;
		Node *right;
		Node *left;

		Node(const TKey &key, const TValue &value) : key(key), value(value), right(NULL), left(NULL){
		}

		Node(const ft::pair<TKey, TValue> &in) : key(in.first), value(in.second), right(NULL), left(NULL){
		}
	};

	template<typename TKey, typename TValue>
	class BinarySearchTree {
	private:
		Node<TKey, TValue> *rootNode;
	public:
		BinarySearchTree() : rootNode(){

		}

		BinarySearchTree &operator=(const BinarySearchTree &rhs){
			Node<TKey, TValue> *tmp = rhs.rootNode;
			if (rhs.rootNode == this->rootNode)
				return *this;
			copySubTree(rhs.rootNode, &rootNode);
			return *this;
		}

		virtual ~BinarySearchTree() {
			deleteNodesFrom(&rootNode);
		}

		Node<TKey, TValue> *findByKey(TKey i) {
			Node<TKey, TValue> *tmp = rootNode;

			while (tmp != NULL){
				if (tmp->key == i)
					return (tmp);
				if (tmp->key > i){
					if(tmp->left == NULL)
						return NULL;
					tmp = tmp->left;
				}
				else{
					if(tmp->right == NULL)
						return NULL;
					tmp = tmp->right;
				}
			}
			return NULL;
		}

		void insert(ft::pair<TKey, TValue> in) {
			Node <TKey, TValue> *newNode = new ::ft::Node<TKey, TValue>(in);
			Node <TKey, TValue> *newParent = rootNode;

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

	private:

		void linkChildAndParent(Node <TKey, TValue> *newNode, Node <TKey, TValue> **newParent) const {
			if (*newParent != NULL){
				if (newNode->key < (*newParent)->key)
					(*newParent)->left = newNode;
				else
					(*newParent)->right = newNode;
			}
			else
				*newParent = newNode;
		}

		Node <TKey, TValue> *findInsertPlace(const Node <TKey, TValue> *newNode) const {
			Node <TKey, TValue> *tmp = rootNode;

			while ((tmp->left != NULL || tmp->right != NULL)) {
				if (newNode->key < tmp->key){
					if (tmp->left == NULL)
						return tmp;
					tmp = tmp->left;
				}
				else
				{
					if (tmp->right == NULL)
						return tmp;
					tmp = tmp->right;
				}
			}
			return tmp;
		}

		void deleteNodesFrom(Node<TKey, TValue> **localRoot){
			if (localRoot == NULL || *localRoot == NULL)
				return ;
			deleteNodesFrom(&(*localRoot)->left);
			deleteNodesFrom(&(*localRoot)->right);
			delete *localRoot;
			localRoot = NULL;
		}

		void copySubTree(Node<TKey, TValue> *source,Node<TKey, TValue> **dest){
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
