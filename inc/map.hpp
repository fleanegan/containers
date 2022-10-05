//
// Created by fleanegan on 30.08.22.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include "RedBlackTree.hpp"
#include "MapIterator.hpp"
#include "reverse_iterator.hpp"

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
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
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
			insert(first, last);
		}

		map &operator=(const map &map) {
			if (rbTree.root() == map.rbTree.root())
				return *this;
			alloc = map.alloc;
			rbTree = map.rbTree;
			compare = map.compare;
			return *this;
		}

		~map(){

		}

		// todo: fix const time CALL IS STUPID
		const_iterator begin() const {
			return const_iterator(ft::getLowest(rbTree.root()), rbTree.getExtremeties(), compare);
		}

		iterator begin() {
			return iterator(ft::getLowest(rbTree.root()), rbTree.getExtremeties(), compare);
		}

		const_iterator end() const {
			return const_iterator(rbTree.getNullNode(), rbTree.getExtremeties(), compare);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		iterator end() {
			return iterator(rbTree.getNullNode(),  rbTree.getExtremeties(), compare);
		}

		ft::pair<iterator,bool> insert (const value_type& val) {
			ft::pair<iterator, bool> result;
			size_type before = size();
			result.first = iterator(rbTree.insert(val),  rbTree.getExtremeties(), compare);
			result.second = true;
			size_type after = size();
			if (before == after)
				result.second = false;
			return result;
		}

		iterator insert( iterator hint, const value_type& value ){
			(void) hint;
			return insert(value).first;
		}
		iterator insert( const_iterator hint, const value_type& value ){
			(void) hint;
			return insert(value).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){
			while (first != last)
			{
				rbTree.insert(*first);
				first++;
			}
		}

		void erase (iterator position){
			rbTree.popNodeByPointer(position.current());
		}

		size_type erase (const key_type& k){
			return rbTree.popNode(k);
		}

		void erase (iterator first, iterator last){
			iterator tmp;

			if (first == last)
				return ;
			--last;
			while (first != last)
				rbTree.popNodeByPointer(last--.current());
			rbTree.popNodeByPointer(last--.current());
		}

		void swap (map& x){
			rbTree.swap(x.rbTree);
		}

		size_type size() const {
			return rbTree.size();
		}

		size_type max_size(void) const {
			return rbTree.max_size();
		}

		bool empty() const{
			return size() == 0;
		}

		allocator_type get_allocator() const {
			return alloc;
		}

		void clear(){
			rbTree.clear();
		}

		size_type count( const Key& key ) const{
			return static_cast<size_type>(end() != find(key));
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

			if (result == rbTree.getNullNode())
				throw std::out_of_range("key not found");
			return result->content.second;
		}

		iterator find( const Key& key ){
			const_iterator result = static_cast<const this_type &>(*this).find(key);
			return iterator(const_cast<NodeType *>(result.current()),  rbTree.getExtremeties(), compare);
		}

		const_iterator find( const Key& key ) const{
			NodeType const *  result = rbTree.find(key);
			if (result == rbTree.getNullNode())
				return end();
			return const_iterator(result,  rbTree.getExtremeties(), compare);
		}

		iterator lower_bound( const Key& key ){
			const_iterator result = static_cast<const this_type &>(*this).lower_bound(key);
			return iterator(const_cast<NodeType *>(result.current()),  rbTree.getExtremeties(), compare);
		}

		const_iterator lower_bound( const Key& key ) const{
			const_iterator ite = end();
			const_iterator it = begin();

			if (key < rbTree.getExtremeties()->getLeft()->content.first)
				return begin();
			while (it != ite) {
				if (!compare((*it).first, key))
					return (const_iterator(it));
				++it;
			}
			return (this->end());
		}

		iterator upper_bound( const Key& key ){
			const_iterator result = static_cast<const this_type &>(*this).upper_bound(key);
			return iterator(const_cast<NodeType *>(result.current()),  rbTree.getExtremeties(), compare);
		}

		const_iterator upper_bound( const Key& key ) const{
			const_iterator ite = end();
			const_iterator it = begin();

			if (key > rbTree.getExtremeties()->getRight()->content.first)
				return end();
			while (ite != it){
				if (compare(key, it->first))
					return it;
				++it;
			}
			return end();
		}

		ft::pair<iterator,iterator> equal_range( const Key& key ){
			ft::pair<iterator, iterator> result;
			ft::pair<const_iterator, const_iterator> result_const = static_cast<const this_type &>(*this).equal_range(key);

			result.first = iterator(const_cast<NodeType *>(result_const.first.current()),  rbTree.getExtremeties(), compare);
			result.second = iterator(const_cast<NodeType *>(result_const.second.current()),  rbTree.getExtremeties(), compare);
			return result;
		}

		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const{
			ft::pair<const_iterator, const_iterator> result;
			result.first = lower_bound(key);
			result.second = upper_bound(key);
			return result;
		}

		key_compare key_comp() const{
			return compare;
		}

		value_compare value_comp() const{
			return value_compare(compare);
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

	template<typename K, typename T, typename Compare>
	void swap(map<K, T, Compare> &x, map<K, T, Compare> &y) {
		x.swap(y);
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
			   ft::map<Key,T,Compare,Alloc>& rhs ){
		lhs.swap(rhs);
	}
}
#endif //CONTAINERS_MAP_HPP

