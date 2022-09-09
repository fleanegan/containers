//
// Created by fleanegan on 30.08.22.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include "RedBlackTree.hpp"
#include "MapIterator.hpp"
#include "ReverseIterator.hpp"

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
		typedef typename BinarySearchTree<key_type, value_type, NodeType, Compare, Allocator>::difference_type difference_type;

	private:
		typedef typename allocator_type::template rebind<NodeType>::other rb_allocator_type;
		typedef ft::RedBlackTree<key_type, mapped_type, NodeType, Compare, rb_allocator_type> RbTree;

	public:
		typedef MapIterator<value_type, key_type, mapped_type, NodeType, Compare> iterator;
		typedef MapIterator<const value_type, key_type, mapped_type, const NodeType, Compare> const_iterator;
		typedef ft::ReverseIterator<iterator> reverse_iterator;
		typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;
		typedef typename RbTree::size_type size_type;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

	private:
		typedef typename ft::map<Key, T, Compare, Allocator> this_type;
		RbTree rbTree;
		Compare compare;
		allocator_type alloc;

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
				  alloc(alloc),
				  compare(comp){
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
			insert(first, last);
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

		const_iterator begin() const {
			NodeType const * nullNode = rbTree.getNullNode();
			return const_iterator(rbTree.getLowest(rbTree.root()), compare);
		}

		iterator begin() {
			return iterator(rbTree.getLowest(rbTree.root()), compare);
		}

		const_iterator end() const {
			return const_iterator(rbTree.getNullNode(), compare);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const{
			return reverse_iterator(end());
		}

		const_reverse_iterator rend() const {
			return reverse_iterator(begin());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		iterator end() {
			return iterator(rbTree.getNullNode(), compare);
		}

		ft::pair<iterator,bool> insert (const value_type& val) {
			ft::pair<iterator, bool> result;
			size_type before = size();
			result.first = iterator(rbTree.insert(val));
			result.second = true;
			size_type after = size();
			if (before == after)
				result.second = false;
			return result;
		}

		ft::pair<iterator,bool> insert (iterator position, const value_type& val){
			(void) position;
			return insert(val);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){
			while (first != last)
				rbTree.insert(*first++);
		}

		void erase (iterator position){
			rbTree.popNodeByPointer(position.current());
		}

		size_type erase (const key_type& k){
			rbTree.popNode(k);
			return 1;
		}

		void erase (iterator first, iterator last){
			iterator tmp;

			--last;
			while (first != last)
				rbTree.popNodeByPointer(last--.current());
			rbTree.popNodeByPointer(last--.current());
		}

		void swap (map& x){
			rbTree.swap(x.rbTree);
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

		size_type count() const{
			return 1;
		}

		mapped_type& operator[] (const key_type& k) {
			iterator it = insert(ft::make_pair(k, mapped_type())).first;
			return it->second;
		}

		mapped_type& at (const key_type& k){
			return const_cast<mapped_type &>(static_cast<const this_type &>(*this).at(k));
		}

		const mapped_type& at(const key_type& k) const{
			NodeType const *result = rbTree.find(k);

			if (result == NULL)
				throw std::out_of_range("key not found");
			return result->content.second;
		}

		iterator find( const Key& key ){
			const_iterator result = static_cast<const this_type &>(*this).find(key);
			return iterator(const_cast<NodeType *>(result.current()));
		}

		const_iterator find( const Key& key ) const{
			NodeType const *  result = rbTree.find(key);
			if (result == NULL)
				return end();
			return const_iterator(result);
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
	bool operator<(const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y){
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template<class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key, T, Compare, Allocator> &x,
				   const map<Key, T, Compare, Allocator> &y) {
		return !(x < y) && (x != y);
	}

	template<class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y) {
		return !ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template<class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y) {
		return !ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
	}
}
#endif //CONTAINERS_MAP_HPP
