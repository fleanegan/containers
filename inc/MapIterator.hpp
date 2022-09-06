//
// Created by fleanegan on 02.09.22.
//

#ifndef CONTAINERS_MAPITERATOR_HPP
#define CONTAINERS_MAPITERATOR_HPP

namespace ft {

	template<typename Key, typename T, typename NodeType>
	class MapIterator {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef NodeType Node;
		typedef value_type* pointer;
		typedef value_type const * const_pointer;
		typedef value_type& reference;
		typedef value_type const & const_reference;
	private:
		Node *currentNode;
		Node *nullNode;
	public:
		MapIterator() : currentNode() {}

		MapIterator(Node *const node, Node *const nullNode) : currentNode(node),
															  nullNode(nullNode) {
		}

		template<class UKey, class UValue, class UNode = ft::RedBlackNode<UKey, UValue> >
		MapIterator(const MapIterator<UKey, UValue, UNode> &it) : currentNode(it.current()),
														   nullNode(it.null()) {
		}

		MapIterator(const MapIterator &rhs) : currentNode(rhs.currentNode),
											  nullNode(rhs.nullNode) {}

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

		Node *null() {
			return nullNode;
		}


		Node *null() const {
			return nullNode;
		}

		MapIterator operator--(int i) {
			MapIterator<key_type, mapped_type, NodeType> result = *this;
			if (i == 0) {
				moveToPrevNode();
			}
			return result;
		}

		MapIterator operator++(int i) {
			MapIterator<key_type, mapped_type, NodeType> result = *this;
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

		template<typename Disabler = Node , typename ft::enable_if<!ft::is_const<Disabler>::value>::type* = nullptr>
		reference operator*() {
			return currentNode->content;
		}

		template<typename Disabler = Node , typename ft::enable_if<ft::is_const<Disabler>::value>::type* = nullptr>
		const_reference operator*() const {
			return currentNode->content;
		}

	private:
		void moveToNextNode() {
			Key originalKey;

			if (currentNode == nullNode)
				currentNode =
						BinarySearchTree<key_type, mapped_type, Node>::getLowest(currentNode, nullNode);
			else {
				originalKey = currentNode->content.first;
				if (currentNode->right != nullNode) {
					currentNode = currentNode->right;
					while (currentNode->left != nullNode)
						currentNode = currentNode->left;
				} else {
					while (currentNode == currentNode->parent->right && currentNode->parent != nullNode)
						currentNode = currentNode->parent;
					if (currentNode->parent != nullNode &&
						currentNode == currentNode->parent->left)
						currentNode = currentNode->parent;
					if (currentNode->content.first < originalKey)
						currentNode = nullNode;
				}
			}
		}

		void moveToPrevNode() {
			Key originalKey;

			if (currentNode == nullNode)
				currentNode =
						BinarySearchTree<key_type, mapped_type, Node>::getHighest(currentNode, nullNode);
			else {
				originalKey = currentNode->content.first;
				if (currentNode->left != nullNode) {
					currentNode = currentNode->left;
					while (currentNode->right != nullNode)
						currentNode = currentNode->right;
				} else {
					while (currentNode == currentNode->parent->left && currentNode->parent != nullNode)
						currentNode = currentNode->parent;
					if (currentNode->parent != nullNode &&
						currentNode == currentNode->parent->right)
						currentNode = currentNode->parent;
					if (currentNode->content.first > originalKey)
						currentNode = nullNode;
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
