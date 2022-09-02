//
// Created by fleanegan on 02.09.22.
//

#ifndef CONTAINERS_MAPITERATOR_HPP
#define CONTAINERS_MAPITERATOR_HPP

namespace ft {
	template<typename Key, typename T, typename Node = ft::RedBlackNode<Key, T> >
	class MapIterator{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
	private:
		Node *ptr;
	public:
		MapIterator() : ptr() {}

		MapIterator(Node * const node) : ptr(node) {
		}

		value_type &operator*() {
			return ptr->content;
		}

		value_type &operator*() const {
			return ptr->content;
		}
	};
}

#endif //CONTAINERS_MAPITERATOR_HPP
