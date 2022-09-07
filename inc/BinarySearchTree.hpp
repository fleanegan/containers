#ifndef CONTAINERS_BINARYSEARCHTREE_HPP
#define CONTAINERS_BINARYSEARCHTREE_HPP

#include "Pair.hpp"

namespace ft {

	template<typename TKey, typename TValue>
	struct SearchTreeStandardNode {
		ft::pair<const TKey, TValue> content;
		SearchTreeStandardNode *right;
		SearchTreeStandardNode *left;
		SearchTreeStandardNode *parent;

		SearchTreeStandardNode(const TKey &key, const TValue &value, SearchTreeStandardNode<TKey, TValue> *nullNode) :content(key, value),
																													right(nullNode),
																													left(nullNode),
																													parent(nullNode) {
		}

		SearchTreeStandardNode(const ft::pair<TKey, TValue> &in, SearchTreeStandardNode<TKey, TValue> *nullNode) : content(in),
																													right(nullNode),
																													left(nullNode),
																													parent(nullNode) {
		}

		SearchTreeStandardNode(const SearchTreeStandardNode<TKey, TValue> &rhs, SearchTreeStandardNode<TKey, TValue> *nullNode) : content(rhs.content),
																				 right(nullNode),
																				 left(nullNode),
																				 parent(nullNode) {
		}

		SearchTreeStandardNode() : left(NULL), right(NULL), parent(NULL) {
		}

		virtual ~SearchTreeStandardNode() {

		}
	};

	template <typename TKey, typename TValue, typename NodeType, typename Compare = std::less<TKey>, typename Allocator = std::allocator<NodeType> >
	class BinarySearchTree {
	public:
		typedef TKey key_type;
		typedef TValue mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef NodeType Node;
		typedef Node& reference;
		typedef Node const& const_reference;
		typedef Node* pointer;
		typedef Node const * const_pointer;
		typedef Compare compare_type;
		typedef size_t size_type;

	protected:
		Node nullNode;
		pointer rootNode;
	private:
		allocator_type _allocator;
		size_type current_size;
		compare_type _compare;
	public:
		BinarySearchTree(const compare_type &compare = compare_type(), const allocator_type &alloc = allocator_type()) :
				nullNode(),
				rootNode(&nullNode),
				_compare(compare),
				_allocator(alloc),
				current_size(0) {

		}

		BinarySearchTree(const BinarySearchTree &rhs) :
				nullNode(),
				rootNode(&nullNode),
				_compare(rhs._compare),
				_allocator(rhs._allocator) {
			*this = rhs;
		}

		BinarySearchTree &operator=(const BinarySearchTree &rhs) {
			if (rhs.rootNode == this->rootNode)
				return *this;
			current_size = rhs.current_size;
			copySubTree(rhs.rootNode, &rhs.nullNode, &rootNode);
			return *this;
		}

		virtual ~BinarySearchTree() {
			deleteSubTreeFrom(rootNode);
		}

		pointer findByKey(TKey &i) {
			Node *tmp = rootNode;

			while (tmp != &nullNode) {
				if (tmp->content.first == i)
					return (tmp);
				if (_compare(tmp->content.first, i) == false) {
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

		pointer getNullNode() {
			return &nullNode;
		}

		pointer getNullNode() const {
			return &nullNode;
		}

		pointer insertByValue(ft::pair<TKey, TValue> in) {
			return insert(in);
		}

		pointer insert(ft::pair<TKey, TValue> const &in) {
			Node *newParent = &nullNode;

			if (rootNode != &nullNode) {
				newParent = findInsertPlace(&in.first);
				if (newParent->content.first == in.first)
					return newParent;
			}
			return pairToChildOf(in, newParent);
		}

		pointer root() {
			return rootNode;
		}

		pointer root() const {
			return rootNode;
		}

		virtual void popNode(TKey keyOfNodeToBeRemoved) {
			Node *nodeToBeRemoved = findByKey(keyOfNodeToBeRemoved);
			popNodeByPointer(nodeToBeRemoved);
		}

		virtual void popNodeByPointer(Node *nodeToBeRemoved) {
			if (nodeToBeRemoved == &nullNode)
				return;
			if (nodeToBeRemoved->right == &nullNode)
				replaceNode(nodeToBeRemoved, nodeToBeRemoved->left);
			else if (nodeToBeRemoved->left == &nullNode)
				replaceNode(nodeToBeRemoved, nodeToBeRemoved->right);
			else
				substituteNodeWithSuccessor(nodeToBeRemoved);
			deleteNodeWithCleanUp(nodeToBeRemoved);
		}

		void leftRotate(Node *pivot) {
			if (pivot->right == &nullNode)
				return;
			Node *nodeToChangePlaceWith = pivot->right;

			pivot->right = nodeToChangePlaceWith->left;
			nodeToChangePlaceWith->left->parent = pivot;
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

		void rightRotate(Node *pivot) {
			if (pivot->left == &nullNode)
				return;
			Node *nodeToChangePlaceWith = pivot->left;

			pivot->left = nodeToChangePlaceWith->right;
			nodeToChangePlaceWith->right->parent = pivot;
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

		size_type size() const{
			return current_size;
		}

		static pointer getLowest(Node *startingPoint, Node *nullNode) {
			Node *tmp = startingPoint;

			while (tmp->left != nullNode)
				tmp = tmp->left;
			return tmp;
		}

		static pointer getHighest(Node *startingPoint, Node *nullNode) {
			Node *tmp = startingPoint;

			while (tmp->right != nullNode)
				tmp = tmp->right;
			return tmp;
		}


	private:
		void updateNodesForRotation(Node *pivot, Node *nodeToChangePlaceWith) {
			Node *parent = pivot->parent;

			if (nodeToChangePlaceWith->parent == rootNode)
				rootNode = nodeToChangePlaceWith;
			linkChildAndParent(nodeToChangePlaceWith, &parent);
			linkChildAndParent(pivot, &nodeToChangePlaceWith);
		}

		pointer findInsertPlace(const TKey *keyOfNewNode) const {
			Node *tmp = rootNode;

			while ((tmp->left != &nullNode || tmp->right != &nullNode)) {
				if (_compare(*keyOfNewNode, tmp->content.first)) {
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
				newNode = _allocator.allocate(1);
				_allocator.construct(newNode, *source, &nullNode);
				linkChildAndParent(newNode, dest);
				if (source->right != sourceNullNode)
					copySubTree(source->right, sourceNullNode, &newNode);
				if (source->left != sourceNullNode)
					copySubTree(source->left, sourceNullNode, &newNode);
			}
		}

	protected:
		pointer getInorderSuccessor(Node *localRoot, Node *biggerThan,
								  Node *currentOptimum) {
			Node *leftMinimum = &nullNode;
			Node *rightMinimum = &nullNode;

			if (localRoot == &nullNode)
				return &nullNode;
			if (localRoot->right == &nullNode && localRoot->left == &nullNode) {
				if (_compare(localRoot->content.first, currentOptimum->content.first) && _compare(localRoot->content.first, biggerThan->content.first) == false)
					return localRoot;
				return currentOptimum;
			}
			leftMinimum = getInorderSuccessor(localRoot->left, biggerThan, currentOptimum);
			rightMinimum = getInorderSuccessor(localRoot->right, biggerThan, currentOptimum);
			if (leftMinimum != &nullNode && _compare(leftMinimum->content.first, biggerThan->content.first) == false &&
					_compare(leftMinimum->content.first, currentOptimum->content.first)) {
				if (_compare(leftMinimum->content.first, localRoot->content.first))
					return leftMinimum;
				return localRoot;
			}
			if (rightMinimum != &nullNode && _compare(rightMinimum->content.first, biggerThan->content.first) == false &&
					_compare(rightMinimum->content.first, currentOptimum->content.first)) {
				if (_compare(rightMinimum->content.first, localRoot->content.first))
					return rightMinimum;
				return localRoot;
			}
			return currentOptimum;
		}

		void substituteNodeWithSuccessor(Node *nodeToBeRemoved) {
			Node *successor;

			successor = getInorderSuccessor(nodeToBeRemoved->right, nodeToBeRemoved, nodeToBeRemoved->right);
			if (successor->parent != nodeToBeRemoved) {
				replaceNode(successor, successor->right);
				successor->right = nodeToBeRemoved->right;
				successor->right->parent = successor;
			}
			replaceNode(nodeToBeRemoved, successor);
			successor->left = nodeToBeRemoved->left;
			successor->left->parent = successor;
		}

		void replaceNode(Node *nodeToBeReplaced, Node *replacer) {
			if (nodeToBeReplaced->parent == &nullNode) {
				rootNode = &nullNode;
				linkChildAndParent(replacer, &rootNode);
			} else if (nodeToBeReplaced == nodeToBeReplaced->parent->left)
				nodeToBeReplaced->parent->left = replacer;
			else
				nodeToBeReplaced->parent->right = replacer;
			replacer->parent = nodeToBeReplaced->parent;
		}

		void deleteNodeWithCleanUp(const Node *nodeToBeRemoved) {
			if (nodeToBeRemoved == rootNode) {
				rootNode = &nullNode;
				nullNode.right = &nullNode;
				nullNode.left = &nullNode;
			}
			--current_size;
			delete nodeToBeRemoved;
		}

	private:
		void linkChildAndParent(Node *newNode, Node **newParent) {
			if (*newParent != &nullNode) {
				if (_compare(newNode->content.first, (*newParent)->content.first))
					(*newParent)->left = newNode;
				else
					(*newParent)->right = newNode;
			} else {
				nullNode.right = newNode;
				nullNode.left = newNode;
				rootNode = newNode;
			}
			newNode->parent = *newParent;
		}

		pointer linkChildToGrandParent(Node *parent, Node *&grandParent) {
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

		pointer pairToChildOf(const pair <TKey, TValue> &in, Node *&newParent) {
			Node *newNode;
			newNode = _allocator.allocate(1);
			_allocator.construct(newNode, in, &nullNode);
			linkChildAndParent(newNode, &newParent);
			++current_size;
			return newNode;
		}
	};
}

#endif //CONTAINERS_BINARYSEARCHTREE_HPP
