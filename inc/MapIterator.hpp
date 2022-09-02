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

		MapIterator operator--(int i) {
			MapIterator<key_type, mapped_type, NodeType> result = *this;
			if (i == 0) {
				moveToPrevNode();
			}
// todo: does this need to be implemented in bidirectional?
//			else
//				currentNode -= i;
			return result;
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

		value_type &operator*() {
			return currentNode->content;
		}

		value_type &operator*() const {
			return currentNode->content;
		}
	};
}

#endif //CONTAINERS_MAPITERATOR_HPP
