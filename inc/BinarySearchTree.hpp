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
		bool isNull;

		SearchTreeStandardNode(const TKey &key, const TValue &value, SearchTreeStandardNode<TKey, TValue> *nullNode)
				: content(key, value),
				  right(nullNode),
				  left(nullNode),
				  parent(nullNode),
				  isNull(false) {
		}

		SearchTreeStandardNode(const ft::pair<TKey, TValue> &in, SearchTreeStandardNode<TKey, TValue> *nullNode)
				: content(in),
				  right(nullNode),
				  left(nullNode),
				  parent(nullNode),
				  isNull(false) {
		}

		SearchTreeStandardNode(const SearchTreeStandardNode<TKey, TValue> &rhs,
							   SearchTreeStandardNode<TKey, TValue> *nullNode) : content(rhs.content),
																				 right(nullNode),
																				 left(nullNode),
																				 parent(nullNode),
																				 isNull(false) {
		}

		SearchTreeStandardNode() : left(this), right(this), parent(this), isNull(true) {
		}

		bool isNullNode() const{
			return isNull;
		}

		virtual ~SearchTreeStandardNode() {

		}
	};

	template<typename TKey, typename TValue, typename NodeType, typename Compare = std::less<TKey>, typename Allocator = std::allocator<NodeType> >
	class BinarySearchTree {
	public:
		typedef TKey key_type;
		typedef TValue mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef ft::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef NodeType Node;
		typedef Node &reference;
		typedef Node const &const_reference;
		typedef Node *pointer;
		typedef Node const *const_pointer;
		typedef Compare compare_type;
		typedef size_t size_type;

	private:
		allocator_type _allocator;
		compare_type _compare;
		size_type current_size;
	protected:
		pointer nullNode;
		pointer rootNode;

	public:
		BinarySearchTree(const compare_type &compare = compare_type(), const allocator_type &alloc = allocator_type()) :
				_allocator(alloc),
				_compare(compare),
				current_size(0),
				nullNode(makeNullNode()),
				rootNode(nullNode) {

		}

		BinarySearchTree(const BinarySearchTree &rhs) :
				_allocator(rhs._allocator),
				_compare(rhs._compare),
				nullNode(makeNullNode()),
				rootNode(nullNode) {
			*this = rhs;
		}

		BinarySearchTree &operator=(const BinarySearchTree &rhs) {
			if (rhs.rootNode == this->rootNode)
				return *this;
			current_size = rhs.current_size;
			copySubTree(rhs.rootNode, rhs.nullNode, &rootNode);
			return *this;
		}

		virtual ~BinarySearchTree() {
			clear();
			destroyAndDeallocateNode(nullNode);
		}

		pointer find(const TKey &i) {
			return const_cast<pointer>(findByKey(i));
		}

		const_pointer find(const TKey &i) const {
			return findByKey(i);
		}

		void clear() {
			deleteSubTreeFrom(rootNode);
		}

		pointer getNullNode() {
			return nullNode;
		}

		const_pointer getNullNode() const {
			return nullNode;
		}

		pointer insertByValue(ft::pair<TKey, TValue> in) {
			return insert(in);
		}

		pointer insert(ft::pair<TKey, TValue> const &in) {
			pointer newParent = nullNode;

			if (rootNode->isNullNode() == false) {
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
			pointer nodeToBeRemoved = find(keyOfNodeToBeRemoved);
			popNodeByPointer(nodeToBeRemoved);
		}

		virtual void popNodeByPointer(pointer nodeToBeRemoved) {
			if (nodeToBeRemoved->isNullNode())
				return;
			if (nodeToBeRemoved->right->isNullNode())
				replaceNode(nodeToBeRemoved, nodeToBeRemoved->left);
			else if (nodeToBeRemoved->left->isNullNode())
				replaceNode(nodeToBeRemoved, nodeToBeRemoved->right);
			else
				substituteNodeWithSuccessor(nodeToBeRemoved);
			deleteNodeWithCleanUp(nodeToBeRemoved);
		}

		void leftRotate(pointer pivot) {
			if (pivot->right->isNullNode())
				return;
			pointer nodeToChangePlaceWith = pivot->right;

			pivot->right = nodeToChangePlaceWith->left;
			nodeToChangePlaceWith->left->parent = pivot;
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

		void rightRotate(pointer pivot) {
			if (pivot->left->isNullNode())
				return;
			pointer nodeToChangePlaceWith = pivot->left;

			pivot->left = nodeToChangePlaceWith->right;
			nodeToChangePlaceWith->right->parent = pivot;
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

		size_type size() const {
			return current_size;
		}

		size_type max_size(void) const {
			return (std::min((size_type) std::numeric_limits<difference_type>::max(),
							 std::numeric_limits<size_type>::max() / (sizeof(NodeType) + sizeof(pointer))));
		}

		static pointer getLowest(pointer startingPoint) {
			pointer tmp = startingPoint;

			if (tmp->isNullNode() && tmp->left->isNullNode())
				return tmp;
			while (tmp->left->isNullNode() == false)
				tmp = tmp->left;
			return tmp;
		}

		static pointer getHighest(pointer startingPoint) {
			pointer tmp = startingPoint;

			while (tmp->right->isNullNode() == false)
				tmp = tmp->right;
			return tmp;
		}

		bool isSameStructure(const_pointer a, const_pointer const b, const_pointer bNullNode) const {
			if (!((a->isNullNode()) && (b == bNullNode)))
				if (a->isNullNode() == false && b != bNullNode && a->content != b->content)
					return false;
			if (a->right->isNullNode() == false) {
				if (b->right == bNullNode || isSameStructure(a->right, b->right, bNullNode) == false)
					return false;
			}
			if (a->left->isNullNode() == false) {
				if (b->left == bNullNode || isSameStructure(a->left, b->left, bNullNode) == false)
					return false;
			}
			return true;
		}

		void swap(BinarySearchTree &in) {
			size_type current_size_tmp = current_size;
			pointer rootNode_tmp = rootNode;
			pointer nullNode_tmp = nullNode;

			current_size = in.current_size;
			nullNode = in.nullNode;
			rootNode = in.rootNode;
			in.current_size = current_size_tmp;
			in.rootNode = rootNode_tmp;
			in.nullNode = nullNode_tmp;
		}

	private:
		const_pointer findByKey(const TKey &i) const {
			pointer tmp = rootNode;

			while (tmp->isNullNode() == false) {
				if (tmp->content.first == i)
					return (tmp);
				if (_compare(tmp->content.first, i) == false) {
					if (tmp->left->isNullNode())
						return nullNode;
					tmp = tmp->left;
				} else {
					if (tmp->right->isNullNode())
						return nullNode;
					tmp = tmp->right;
				}
			}
			return NULL;
		}

		void updateNodesForRotation(pointer pivot, pointer nodeToChangePlaceWith) {
			pointer parent = pivot->parent;

			if (nodeToChangePlaceWith->parent == rootNode)
				rootNode = nodeToChangePlaceWith;
			linkChildAndParent(nodeToChangePlaceWith, &parent);
			linkChildAndParent(pivot, &nodeToChangePlaceWith);
		}

		pointer findInsertPlace(const TKey *keyOfNewNode) const {
			pointer tmp = rootNode;

			while ((tmp->left->isNullNode() == false || tmp->right->isNullNode() == false)) {
				if (_compare(*keyOfNewNode, tmp->content.first)) {
					if (tmp->left->isNullNode())
						return tmp;
					tmp = tmp->left;
				} else {
					if (tmp->right->isNullNode())
						return tmp;
					tmp = tmp->right;
				}
			}
			return tmp;
		}

		void deleteSubTreeFrom(pointer localRoot) {
			if (localRoot->isNullNode())
				return;
			deleteSubTreeFrom((localRoot)->left);
			deleteSubTreeFrom((localRoot)->right);
			if (localRoot == rootNode)
				rootNode = nullNode;
			--current_size;
			_allocator.destroy(localRoot);
			_allocator.deallocate(localRoot, 1);
		}

		void copySubTree(pointer source, const_pointer sourceNullNode, pointer *dest) {
			pointer newNode;

			if (source != sourceNullNode) {
				newNode = copyNode(source);
				linkChildAndParent(newNode, dest);
				if (source->right != sourceNullNode)
					copySubTree(source->right, sourceNullNode, &newNode);
				if (source->left != sourceNullNode)
					copySubTree(source->left, sourceNullNode, &newNode);
			}
		}

		pointer copyNode(const Node *source) {
			pointer newNode;
			newNode = _allocator.allocate(1);
			Node tmp(*source, nullNode);
			_allocator.construct(newNode, tmp);
			return newNode;
		}

	protected:
		pointer getInorderSuccessor(pointer localRoot, pointer biggerThan,
									pointer currentOptimum) {
			pointer leftMinimum = nullNode;
			pointer rightMinimum = nullNode;

			if (localRoot->isNullNode())
				return nullNode;
			if (localRoot->right->isNullNode() && localRoot->left->isNullNode()) {
				if (_compare(localRoot->content.first, currentOptimum->content.first) &&
					_compare(localRoot->content.first, biggerThan->content.first) == false)
					return localRoot;
				return currentOptimum;
			}
			leftMinimum = getInorderSuccessor(localRoot->left, biggerThan, currentOptimum);
			rightMinimum = getInorderSuccessor(localRoot->right, biggerThan, currentOptimum);
			if (leftMinimum->isNullNode() == false && _compare(leftMinimum->content.first, biggerThan->content.first) == false &&
				_compare(leftMinimum->content.first, currentOptimum->content.first)) {
				if (_compare(leftMinimum->content.first, localRoot->content.first))
					return leftMinimum;
				return localRoot;
			}
			if (rightMinimum->isNullNode() == false && _compare(rightMinimum->content.first, biggerThan->content.first) == false &&
				_compare(rightMinimum->content.first, currentOptimum->content.first)) {
				if (_compare(rightMinimum->content.first, localRoot->content.first))
					return rightMinimum;
				return localRoot;
			}
			return currentOptimum;
		}

		void substituteNodeWithSuccessor(pointer nodeToBeRemoved) {
			pointer successor;

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

		void replaceNode(pointer nodeToBeReplaced, pointer replacer) {
			if (nodeToBeReplaced->parent->isNullNode()) {
				rootNode = nullNode;
				linkChildAndParent(replacer, &rootNode);
			} else if (nodeToBeReplaced == nodeToBeReplaced->parent->left)
				nodeToBeReplaced->parent->left = replacer;
			else
				nodeToBeReplaced->parent->right = replacer;
			replacer->parent = nodeToBeReplaced->parent;
		}

		void deleteNodeWithCleanUp(const pointer nodeToBeRemoved) {
			if (nodeToBeRemoved == rootNode) {
				rootNode = nullNode;
				nullNode->right = nullNode;
				nullNode->left = nullNode;
			}
			--current_size;
			delete nodeToBeRemoved;
		}

	private:
		pointer makeNullNode() {
			pointer result;
			result = _allocator.allocate(1);
			_allocator.construct(result, Node());
			result->right = result;
			result->left = result;
			result->parent = result;
			return result;
		}

		void destroyAndDeallocateNode(pointer in) {
			_allocator.destroy(in);
			_allocator.deallocate(in, 1);
		}

		void linkChildAndParent(pointer newNode, pointer *newParent) {
			if ((*newParent)->isNullNode() == false) {
				if (_compare(newNode->content.first, (*newParent)->content.first))
					(*newParent)->left = newNode;
				else
					(*newParent)->right = newNode;
			} else {
				nullNode->right = newNode;
				nullNode->left = newNode;
				rootNode = newNode;
			}
			newNode->parent = *newParent;
		}

		pointer pairToChildOf(const pair<TKey, TValue> &in, pointer &newParent) {
			pointer newNode;
			newNode = _allocator.allocate(1);
			_allocator.construct(newNode, in, nullNode);
			linkChildAndParent(newNode, &newParent);
			++current_size;
			return newNode;
		}
	};

	template<class Key, class T, class NodeType, class Compare, class Allocator>
	bool operator==(const BinarySearchTree<Key, T, NodeType, Compare, Allocator> &x,
					const BinarySearchTree<Key, T, NodeType, Compare, Allocator> &y) {
		if (x.size() == 0 && y.size() == 0)
			return true;
		return x.isSameStructure(x.root(), y.root(), y.getNullNode());
	}

	template<class Key, class T, class NodeType, class Compare, class Allocator>
	bool operator!=(const BinarySearchTree<Key, T, NodeType, Compare, Allocator> &x,
					const BinarySearchTree<Key, T, NodeType, Compare, Allocator> &y) {
		return !(x == y);
	}
}

#endif //CONTAINERS_BINARYSEARCHTREE_HPP
