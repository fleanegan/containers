//
// Created by fleanegan on 30.08.22.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include "RedBlackTree.hpp"
#include "MapIterator.hpp"

namespace ft {
	template<class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef ft::RedBlackNode<key_type, mapped_type> NodeType;

	private:
		typedef typename allocator_type::template rebind<NodeType>::other rb_allocator_type;
		typedef ft::RedBlackTree<key_type, mapped_type, NodeType, Compare, rb_allocator_type> RbTree;

	public:
		typedef MapIterator<key_type, mapped_type, NodeType> iterator;
		typedef MapIterator<key_type, mapped_type, const NodeType> const_iterator;
		typedef typename RbTree::size_type size_type;
		//typedef difference_type;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		//typedef std::reverse_iterator<iterator> reverse_iterator;
		//typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		RbTree rbTree;

	public:
		class value_compare : public std::binary_function<value_type, value_type, bool> {
			private:
				friend class map;
			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public:
				bool operator()(const value_type &x, const value_type &y) const {
					return comp(x.first, y.first);
				}
			};

		explicit map(const Compare& comp = Compare(),
					 const allocator_type & alloc = allocator_type())
					 : rbTree(RbTree(comp, rb_allocator_type(alloc))){

		}

//		const_iterator begin() const {
//			return const_iterator(_arr);
//		}

		iterator begin() {
			return iterator(rbTree.getLowest(rbTree.root(), rbTree.getNullNode()), rbTree.getNullNode());
		}

//		const_iterator end() const {
//			return const_iterator(_arr);
//		}

		iterator end() {
			return iterator(rbTree.getNullNode(), rbTree.getNullNode());
		}

		void insert(const value_type &in){
			rbTree.insert(in);
		}

		size_type size(){
			return rbTree.size();
		}
	};
}
#endif //CONTAINERS_MAP_HPP
