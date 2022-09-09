//
// Created by fleanegan on 02.09.22.
//

#ifndef CONTAINERS_MAPITERATOR_HPP
#define CONTAINERS_MAPITERATOR_HPP

namespace ft {

	template<typename ValueType, typename Key, typename T, typename NodeType>
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

	private:
		Node *currentNode;
	public:
		MapIterator() : currentNode() {}

		MapIterator(Node *const node, Node *const nullNode) : currentNode(node){
		}

		template<class UVType, class UKey, class UValue, class UNode>
		MapIterator(const MapIterator<UVType, UKey, UValue, UNode> &it) : currentNode(it.current()){
		}

		MapIterator(const MapIterator &rhs) : currentNode(rhs.currentNode){}

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
				if (currentNode->right->isNullNode() == false) {
					currentNode = currentNode->right;
					while (currentNode->left->isNullNode() == false)
						currentNode = currentNode->left;
				} else {
					while (currentNode == currentNode->parent->right && currentNode->parent->isNullNode() == false)
						currentNode = currentNode->parent;
					if (currentNode->parent->isNullNode() == false &&
						currentNode == currentNode->parent->left)
						currentNode = currentNode->parent;
					if (currentNode->content.first < originalKey)
						//todo: replace with direct link to nullNode
						while (currentNode->isNullNode() == false)
							currentNode = currentNode->right;
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
				if (currentNode->left->isNullNode() == false) {
					currentNode = currentNode->left;
					while (currentNode->right->isNullNode() == false)
						currentNode = currentNode->right;
				} else {
					while (currentNode == currentNode->parent->left && currentNode->parent->isNullNode() == false)
						currentNode = currentNode->parent;
					if (currentNode->parent->isNullNode() == false &&
						currentNode == currentNode->parent->right)
						currentNode = currentNode->parent;
					if (currentNode->content.first > originalKey)
						//todo: replace with direct link to nullNode
						while (currentNode->isNullNode() == false)
							currentNode = currentNode->right;
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
