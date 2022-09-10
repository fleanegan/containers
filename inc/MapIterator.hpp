//
// Created by fleanegan on 02.09.22.
//

#ifndef CONTAINERS_MAPITERATOR_HPP
#define CONTAINERS_MAPITERATOR_HPP

#include "map.hpp"

namespace ft {

	template<typename ValueType, typename Key, typename T, typename NodeType, typename Compare = std::less<Key> >
	class MapIterator {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef NodeType Node;
		typedef ValueType value_type;
		typedef ValueType* pointer;
		typedef ValueType const * const_pointer;
		typedef ValueType& reference;
		typedef ValueType const & const_reference;
		typedef ft::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef Compare compare_type;

		Compare compare;
	private:
		Node *currentNode;
	public:
		MapIterator(const compare_type &compare = compare_type()) :		compare(compare),
																					currentNode(){}

		MapIterator(Node *const node, const compare_type &compare = compare_type()) : 	compare(compare),
																									currentNode(node){
		}

		template<class UVType, class UKey, class UValue, class UNode>
		MapIterator(const MapIterator<UVType, UKey, UValue, UNode> &it) : 	compare(it.compare),
																			currentNode(it.current()){
		}

		MapIterator(const MapIterator &rhs) : 	compare(rhs.compare),
												currentNode(rhs.currentNode){

		}

		MapIterator &operator--() {
			moveToPrevNode();
			return *this;
		}

		MapIterator &operator++() {
			moveToNextNode();
			return *this;
		}

		Node *current() {
			return currentNode;
		}

		Node *current() const {
			return currentNode;
		}

		MapIterator operator--(int i) {
			MapIterator<ValueType, key_type, mapped_type, NodeType> result = *this;
			if (i == 0) {
				moveToPrevNode();
			}
			return result;
		}

		MapIterator operator++(int i) {
			MapIterator<ValueType, key_type, mapped_type, NodeType> result = *this;
			if (i == 0) {
				moveToNextNode();
			}
			return result;
		}

		pointer operator->() {
			return &currentNode->content;
		}


		const_pointer operator->() const{
			return &currentNode->content;
		}

		reference operator*() {
			return currentNode->content;
		}

		const_reference operator*() const{
			return currentNode->content;
		}
	private:
		void moveToNextNode() {
			Key originalKey;

			if (currentNode->isNullNode())
				currentNode =
						BinarySearchTree<key_type, mapped_type, Node>::getLowest(currentNode);
			else {
				originalKey = currentNode->content.first;
				if (currentNode->getRight()->isNullNode() == false) {
					currentNode = currentNode->getRight();
					while (currentNode->getLeft()->isNullNode() == false)
						currentNode = currentNode->getLeft();
				} else {
					while (currentNode == currentNode->getParent()->getRight() && currentNode->getParent()->isNullNode() == false)
						currentNode = currentNode->getParent();
					if (currentNode->getParent()->isNullNode() == false &&
						currentNode == currentNode->getParent()->getLeft())
						currentNode = currentNode->getParent();
					if (compare(currentNode->content.first, originalKey))
						//todo: replace with direct link to nullNode
						while (currentNode->isNullNode() == false)
							currentNode = currentNode->getRight();
					if (currentNode->isNullNode() == false && currentNode->content.first == originalKey)
						currentNode = currentNode->getRight();
				}
			}
		}

		void moveToPrevNode() {
			Key originalKey;

			if (currentNode->isNullNode())
				currentNode =
						BinarySearchTree<key_type, mapped_type, Node>::getHighest(currentNode);
			else {
				originalKey = currentNode->content.first;
				if (currentNode->getLeft()->isNullNode() == false) {
					currentNode = currentNode->getLeft();
					while (currentNode->getRight()->isNullNode() == false)
						currentNode = currentNode->getRight();
				} else {
					while (currentNode == currentNode->getParent()->getLeft() && currentNode->getParent()->isNullNode() == false)
						currentNode = currentNode->getParent();
					if (currentNode->getParent()->isNullNode() == false &&
						currentNode == currentNode->getParent()->getRight())
						currentNode = currentNode->getParent();
					if (compare(currentNode->content.first, originalKey) == false)
						//todo: replace with direct link to nullNode
						while (currentNode->isNullNode() == false)
							currentNode = currentNode->getRight();
				}
			}
		}

	public:
		bool operator==(const MapIterator &rhs) const {
			return currentNode == rhs.currentNode;
		}

		bool operator!=(const MapIterator &rhs) const {
			return !(rhs == *this);
		}
	};
}

#endif //CONTAINERS_MAPITERATOR_HPP
