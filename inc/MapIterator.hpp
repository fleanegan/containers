//
// Created by fleanegan on 02.09.22.
//

#ifndef CONTAINERS_MAPITERATOR_HPP
#define CONTAINERS_MAPITERATOR_HPP

namespace ft {

	template<typename Key, typename T, template<typename, typename> class NodeType = ft::RedBlackNode>
	class MapIterator {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef NodeType<key_type, mapped_type> Node;
	private:
		Node *currentNode;
		Node *nullNode;
	public:
		MapIterator() : currentNode() {}

		MapIterator(Node *const node, Node *const nullNode) : currentNode(node),
															  nullNode(nullNode) {
		}

		template<class UKey, class UValue, class UNode = ft::RedBlackNode<UKey, UValue> >
		MapIterator(const MapIterator<UKey, UValue> &it) : currentNode(it.currentNode),
														   nullNode(it.nullNode) {
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

		value_type *operator->() {
			return &currentNode->content;
		}

		value_type *operator->() const{
			return &currentNode->content;
		}

		value_type &operator*() {
			return currentNode->content;
		}

		value_type &operator*() const {
			return currentNode->content;
		}
	private:
		void moveToNextNode() {
			Key originalKey;

			if (currentNode == nullNode)
				currentNode =
						BinarySearchTree<key_type, mapped_type, NodeType>::getLowest(currentNode, nullNode);
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
						BinarySearchTree<key_type, mapped_type, NodeType>::getHighest(currentNode, nullNode);
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
