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
		allocator_type alloc;
		Compare compare;

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

		explicit map(const Compare &comp = Compare(),
					 const allocator_type &alloc = allocator_type())
				: rbTree(RbTree(comp, rb_allocator_type(alloc))),
				compare(comp),
				alloc(alloc){
		}

		map(const map &rhs) {
			*this = rhs;
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) :
					compare(comp),
					alloc(alloc){
			while (first != last){
				insert(*first++);
			}
		}

		map &operator=(const map &map) {
			if (rbTree.root() == map.rbTree.root())
				return *this;
			rbTree = map.rbTree;
			alloc = map.alloc;
			compare = map.compare;
			return *this;
		}

		~map(){

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

		ft::pair<iterator, bool> insert(const value_type &in) {
			ft::pair<iterator, bool> result;
			size_type before = size();
			result.first = iterator(rbTree.insert(in), rbTree.getNullNode());
			result.second = true;
			size_type after = size();
			if (before == after)
				result.second = false;
			return result;
		}

		size_type size() {
			return rbTree.size();
		}

		size_type max_size() const{
			return rbTree.max_size();
		}

		bool empty() {
			return size() == 0;
		}

		allocator_type get_allocator() const {
			return alloc;
		}

		void clear(){
			rbTree.clear();
		}

		template<class VKey, class VT, class VCompare, class VAllocator>
		friend bool operator==(const map<VKey, VT, VCompare, VAllocator> &x,
							   const map<VKey, VT, VCompare, VAllocator> &y);
	};

	template<class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y) {
		return (x.rbTree == y.rbTree);
	}

	template<class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y) {
		return !(x == y);
	}

	template<class Key, class T, class Compare, class Allocator>
//	bool operator<(const map<Key,T,Compare,Allocator>& x,
//					const map<Key,T,Compare,Allocator>& y){
	bool operator<(map<Key, T, Compare, Allocator> &x,
				   map<Key, T, Compare, Allocator> &y) {
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template<class Key, class T, class Compare, class Allocator>
//	bool operator>(const map<Key,T,Compare,Allocator>& x,
//					const map<Key,T,Compare,Allocator>& y){
	bool operator>(map<Key, T, Compare, Allocator> &x,
				   map<Key, T, Compare, Allocator> &y) {
		return !(x < y) && (x != y);
	}

	template<class Key, class T, class Compare, class Allocator>
//	bool operator<=(const map<Key,T,Compare,Allocator>& x,
//					const map<Key,T,Compare,Allocator>& y){
	bool operator>=(map<Key, T, Compare, Allocator> &x,
					map<Key, T, Compare, Allocator> &y) {
		return !ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template<class Key, class T, class Compare, class Allocator>
//	bool operator<=(const map<Key,T,Compare,Allocator>& x,
//					const map<Key,T,Compare,Allocator>& y){
	bool operator<=(map<Key, T, Compare, Allocator> &x,
					map<Key, T, Compare, Allocator> &y) {
		return !ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
	}
}
#endif //CONTAINERS_MAP_HPP
