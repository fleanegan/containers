#ifndef CONTAINERS_BINARYSEARCHTREE_HPP
#define CONTAINERS_BINARYSEARCHTREE_HPP

#include "pair.hpp"
#include "Node.hpp"
#include "algorithm.hpp"
#include "vector.hpp"
#include <memory>
#include <functional>

namespace ft {
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
		typedef std::size_t size_type;

	private:
		allocator_type _allocator;
		compare_type _compare;
		size_type current_size;
	protected:
		pointer nullNode;
		pointer extremeties;
		pointer rootNode;

	public:
		BinarySearchTree(const compare_type &compare = compare_type(), const allocator_type &alloc = allocator_type()) :
				_allocator(alloc),
				_compare(compare),
				current_size(0),
				nullNode(makeNullNode()),
				extremeties(makeExtremety()),
				rootNode(nullNode) {
		}

		BinarySearchTree(const BinarySearchTree &rhs) :
				_allocator(rhs._allocator),
				_compare(rhs._compare),
				nullNode(makeNullNode()),
				extremeties(makeExtremety()),
				rootNode(nullNode) {
			*this = rhs;
		}

		BinarySearchTree &operator=(const BinarySearchTree &rhs) {
			if (rhs.rootNode == this->rootNode)
				return *this;
			clear();
			current_size = rhs.current_size;
			copySubTree(rhs.rootNode, rhs.nullNode, &rootNode);
			updateExtremities();
			return *this;
		}

		virtual ~BinarySearchTree() {
			clear();
			destroyAndDeallocateNode(nullNode);
			destroyAndDeallocateNode(extremeties);
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

		size_type popNode(TKey keyOfNodeToBeRemoved) {
			pointer nodeToBeRemoved = find(keyOfNodeToBeRemoved);
			return popNodeByPointer(nodeToBeRemoved);
		}

		size_type popNodeByPointer(pointer nodeToBeRemoved) {
			if (nodeToBeRemoved->isNullNode())
				return 0;
			if (nodeToBeRemoved->getRight()->isNullNode())
				replaceNode(nodeToBeRemoved, nodeToBeRemoved->getLeft());
			else if (nodeToBeRemoved->getLeft()->isNullNode())
				replaceNode(nodeToBeRemoved, nodeToBeRemoved->getRight());
			else
				substituteNodeWithSuccessor(nodeToBeRemoved);
			deleteNodeWithCleanUp(nodeToBeRemoved, false);
			return 1;
		}

		void leftRotate(pointer pivot) {
			if (pivot->getRight()->isNullNode())
				return;
			pointer nodeToChangePlaceWith = pivot->getRight();

			pivot->setRight(nodeToChangePlaceWith->getLeft());
			nodeToChangePlaceWith->getLeft()->setParent(pivot);
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

		void rightRotate(pointer pivot) {
			if (pivot->getLeft()->isNullNode())
				return;
			pointer nodeToChangePlaceWith = pivot->getLeft();

			pivot->setLeft(nodeToChangePlaceWith->getRight());
			nodeToChangePlaceWith->getRight()->setParent(pivot);
			updateNodesForRotation(pivot, nodeToChangePlaceWith);
		}

		size_type size() const {
			return current_size;
		}

		size_type max_size(void) const {
			return _allocator.max_size();
		}

		bool isSameStructure(const_pointer a, const_pointer const b, const_pointer bNullNode) const {
			if (b == bNullNode != a->isNullNode())
				return false;
			if (a->isNullNode() == false && b != bNullNode && a->content != b->content)
				return false;
			if (a->getRight()->isNullNode() == false) {
				if (b->getRight() == bNullNode || isSameStructure(a->getRight(), b->getRight(), bNullNode) == false)
					return false;
			}
			if (a->getLeft()->isNullNode() == false) {
				if (b->getLeft() == bNullNode || isSameStructure(a->getLeft(), b->getLeft(), bNullNode) == false)
					return false;
			}
			return true;
		}

		void swap(BinarySearchTree &in) {
			size_type current_size_tmp = current_size;
			pointer rootNode_tmp = rootNode;
			pointer nullNode_tmp = nullNode;
			pointer extremeties_tmp = getExtremeties();

			current_size = in.current_size;
			nullNode = in.nullNode;
			rootNode = in.rootNode;
			extremeties = in.extremeties;
			in.current_size = current_size_tmp;
			in.rootNode = rootNode_tmp;
			in.nullNode = nullNode_tmp;
			in.extremeties = extremeties_tmp;
			updateExtremities();
			in.updateExtremities();
		}

		pointer getExtremeties() const{
			return extremeties;
		}

		pointer getExtremeties(){
			return extremeties;
		}

		void printTree(){
			ft::vector<pointer> children;
			ft::vector<pointer> current;

			current.push_back(rootNode);
			while (current.empty() == false){
				children.clear();
				for (typename ft::vector<pointer>::iterator it = current.begin(); it != current.end(); ++it)
				{
					std::cout << "	" << (*it)->content.first;
					if ((*it)->getParent()->isNullNode() == false)
						std::cout  << "(" << (*it)->getParent()->content.first + ")   ";
				}
				std::cout << std::endl;
				for (typename ft::vector<pointer>::iterator it = current.begin(); it != current.end(); ++it){
					if ((*it)->getRight()->isNullNode() == false)
						children.push_back((*it)->getRight());
					if ((*it)->getLeft()->isNullNode() == false)
						children.push_back((*it)->getLeft());
				}
				current.clear();
				current.swap(children);
			}
		}

	private:
		pointer makeExtremety(){
			pointer node = makeNullNode();

			node->setRight(nullNode);
			node->setLeft(nullNode);
			node->setParent(nullNode);
			return node;
		}

		const_pointer findByKey(const TKey &i) const {
			pointer tmp = rootNode;

			while (tmp->isNullNode() == false) {
				if (tmp->content.first == i)
					return (tmp);
				if (_compare(tmp->content.first, i) == false) {
					if (tmp->getLeft()->isNullNode())
						return nullNode;
					tmp = tmp->getLeft();
				} else {
					if (tmp->getRight()->isNullNode())
						return nullNode;
					tmp = tmp->getRight();
				}
			}
			return nullNode;
		}

		void updateNodesForRotation(pointer pivot, pointer nodeToChangePlaceWith) {
			pointer parent = pivot->getParent();

			if (nodeToChangePlaceWith->getParent() == rootNode)
				rootNode = nodeToChangePlaceWith;
			linkChildAndParent(nodeToChangePlaceWith, &parent);
			linkChildAndParent(pivot, &nodeToChangePlaceWith);
		}

		pointer findInsertPlace(const TKey *keyOfNewNode) const {
			pointer tmp = rootNode;

			while ((tmp->getLeft()->isNullNode() == false || tmp->getRight()->isNullNode() == false)) {
				if (*keyOfNewNode == tmp->content.first)
					return tmp;
				if (_compare(*keyOfNewNode, tmp->content.first)) {
					if (tmp->getLeft()->isNullNode())
						return tmp;
					tmp = tmp->getLeft();
				} else {
					if (tmp->getRight()->isNullNode())
						return tmp;
					tmp = tmp->getRight();
				}
			}
			return tmp;
		}

		void deleteSubTreeFrom(pointer localRoot) {
			if (localRoot->isNullNode())
				return;
			deleteSubTreeFrom((localRoot)->getLeft());
			deleteSubTreeFrom((localRoot)->getRight());
			deleteNodeWithCleanUp(localRoot, true);
		}

		void copySubTree(pointer source, const_pointer sourceNullNode, pointer *dest) {
			pointer newNode;

			if (source != sourceNullNode) {
				newNode = copyNode(source);
				linkChildAndParent(newNode, dest);
				if (source->getRight() != sourceNullNode)
					copySubTree(source->getRight(), sourceNullNode, &newNode);
				if (source->getLeft() != sourceNullNode)
					copySubTree(source->getLeft(), sourceNullNode, &newNode);
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
			if (localRoot->getRight()->isNullNode() && localRoot->getLeft()->isNullNode()) {
				if (_compare(localRoot->content.first, currentOptimum->content.first) &&
					_compare(localRoot->content.first, biggerThan->content.first) == false)
					return localRoot;
				return currentOptimum;
			}
			leftMinimum = getInorderSuccessor(localRoot->getLeft(), biggerThan, currentOptimum);
			rightMinimum = getInorderSuccessor(localRoot->getRight(), biggerThan, currentOptimum);
			if (leftMinimum->isNullNode() == false &&
				_compare(leftMinimum->content.first, biggerThan->content.first) == false &&
				_compare(leftMinimum->content.first, currentOptimum->content.first)) {
				if (_compare(leftMinimum->content.first, localRoot->content.first))
					return leftMinimum;
				return localRoot;
			}
			if (rightMinimum->isNullNode() == false &&
				_compare(rightMinimum->content.first, biggerThan->content.first) == false &&
				_compare(rightMinimum->content.first, currentOptimum->content.first)) {
				if (_compare(rightMinimum->content.first, localRoot->content.first))
					return rightMinimum;
				return localRoot;
			}
			return currentOptimum;
		}

		void substituteNodeWithSuccessor(pointer nodeToBeRemoved) {
			pointer successor;

			successor = getInorderSuccessor(nodeToBeRemoved->getRight(), nodeToBeRemoved, nodeToBeRemoved->getRight());
			if (successor->getParent() != nodeToBeRemoved) {
				replaceNode(successor, successor->getRight());
				successor->setRight(nodeToBeRemoved->getRight());
				successor->getRight()->setParent(successor);
			}
			replaceNode(nodeToBeRemoved, successor);
			successor->setLeft(nodeToBeRemoved->getLeft());
			successor->getLeft()->setParent(successor);
		}

		void replaceNode(pointer nodeToBeReplaced, pointer replacer) {
			if (nodeToBeReplaced->getParent()->isNullNode()) {
				rootNode = nullNode;
				linkChildAndParent(replacer, &rootNode);
			} else if (nodeToBeReplaced == nodeToBeReplaced->getParent()->getLeft())
				nodeToBeReplaced->getParent()->setLeft(replacer);
			else
				nodeToBeReplaced->getParent()->setRight(replacer);
			replacer->setParent(nodeToBeReplaced->getParent());
		}

		void deleteNodeWithCleanUp(const pointer nodeToBeRemoved, bool clean) {
			if (nodeToBeRemoved == rootNode) {
				rootNode = nullNode;
				nullNode->setRight(nullNode);
				nullNode->setLeft(nullNode);
				nullNode->setParent(nullNode);
			}
			if (clean == false)
				updateExtremities();
			--current_size;
			_allocator.destroy(nodeToBeRemoved);
			_allocator.deallocate(nodeToBeRemoved, 1);
		}

	private:
		pointer makeNullNode() {
			pointer result;
			result = _allocator.allocate(1);
			_allocator.construct(result, Node());
			result->setRight(result);
			result->setLeft(result);
			result->setParent(result);
			return result;
		}

		void updateExtremities(){
			if (rootNode == nullNode){
				extremeties->setRight(nullNode);
				extremeties->setLeft(nullNode);
			}
			extremeties->setRight(ft::getHighest(nullNode));
			extremeties->setLeft(ft::getLowest(nullNode));
		}

		void destroyAndDeallocateNode(pointer in) {
			_allocator.destroy(in);
			_allocator.deallocate(in, 1);
		}

		void linkChildAndParent(pointer newNode, pointer *newParent) {
			if ((*newParent)->isNullNode() == false) {
				if (_compare(newNode->content.first, (*newParent)->content.first))
					(*newParent)->setLeft(newNode);
				else
					(*newParent)->setRight(newNode);
			} else {
				nullNode->setRight(newNode);
				nullNode->setLeft(newNode);
				rootNode = newNode;
			}
			newNode->setParent(*newParent);
		}

		pointer pairToChildOf(const pair<TKey, TValue> &in, pointer &newParent) {
			pointer newNode;

			newNode = _allocator.allocate(1);
			Node tmp(in, nullNode);
			_allocator.construct(newNode, tmp);
			linkChildAndParent(newNode, &newParent);
			++current_size;
			updateExtremities();
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
