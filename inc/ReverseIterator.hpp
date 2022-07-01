//
// Created by fleanegan on 23.06.22.
//

#ifndef CONTAINERS_REVERSEITERATOR_HPP
#define CONTAINERS_REVERSEITERATOR_HPP
#include "IteratorTraits.hpp"

template <typename T>
class ReverseIterator{
	T iterator;
public:
	typedef typename T::difference_type difference_type;
	typedef typename T::value_type value_type;
	typedef typename T::reference reference;
	typedef typename T::pointer pointer;
	typedef typename T::iterator_category iterator_category;

	ReverseIterator() : iterator(){
		std::cout << "default reverse iterator constructor called \n";
	}

	ReverseIterator(T it) : iterator(it) {}

	ReverseIterator(const ReverseIterator &revIt) : iterator(revIt.current()) {}

	template<class NonConstIterator>
	ReverseIterator(const ReverseIterator<NonConstIterator> &revIt) : iterator(T(revIt.current())) {}

	template<class NonConstIterator>
	ReverseIterator &operator=(const ReverseIterator<NonConstIterator> &rhs){
		iterator = T(rhs.current());
		return *this;
	}

	template<class NonConstIterator>
	T wtf(const ReverseIterator<NonConstIterator> &revIt){
		T result(revIt.current());
		return result;
	}

	pointer current(){
		return iterator.current();
	}

	pointer current() const{
		return iterator.current();
	}

	reference operator*(){
		return iterator.operator*();
	}

	ReverseIterator operator++(int i){
		ReverseIterator result = *this;
		iterator.operator--(i);
		return result;
	}

	ReverseIterator &operator++(){
		iterator.operator--();
		return *this;
	}

	ReverseIterator &operator--() {
		iterator.operator++();
		return *this;
	}

	ReverseIterator operator--(int i) {
		ReverseIterator result = *this;
		iterator.operator++(i);
		return result;
	}

	ReverseIterator operator+(int i) {
		iterator.operator-(i);
		return *this;
	}

	ReverseIterator operator-(int i) {
		iterator.operator+(i);
		return *this;
	}

	ReverseIterator &operator+=(int i) {
		iterator.operator-=(i);
		return *this;
	}

	ReverseIterator &operator-=(int i) {
		iterator.operator+=(i);
		return *this;
	}

	template<class Iterator>
	typename ft::enable_if<!ft::is_integral<Iterator>::value, difference_type>::type
	operator-(const Iterator &in) {
		iterator.operator+(in);
		return *this;
	}

	template <typename Iterator>
	bool operator==(const ReverseIterator<Iterator> &rhs) const {
		return iterator.operator==(rhs.base());
	}

	template <typename Iterator>
	bool operator!=(const ReverseIterator<Iterator> &rhs) const {
		return iterator.operator!=(rhs.base());
	}

	template <typename Iterator>
	bool operator<(const ReverseIterator<Iterator> &rhs) const {
		return iterator.operator<(rhs.base());
	}

	template <typename Iterator>
	bool operator>(const ReverseIterator<Iterator> &rhs) const {
		return iterator.operator>(rhs.base());
	}

	template <typename Iterator>
	bool operator>=(const ReverseIterator<Iterator> &rhs) const {
		return iterator.operator>=(rhs.base());
	}

	template <typename Iterator>
	bool operator<=(const ReverseIterator<Iterator> &rhs) const {
		return iterator.operator<=(rhs.base());
	}

	pointer operator->() const {
		return iterator.operator->();
	}

	pointer operator->() {
		return iterator.operator->();
	}

	reference operator*() const {
		return iterator.operator*();
	}

	reference operator[](int index) {
		return iterator.operator[](index);
	}

	reference operator[](int index) const {
		return iterator.operator[](index);
	}

	T base(){
		return iterator;
	}

	T base() const {
		return iterator;
	}
};

template <typename T>
ReverseIterator<T> operator+(int i, const ReverseIterator<T>& n)
{
	ReverseIterator<T> result(&*n + i);
	return result;
}

#endif //CONTAINERS_REVERSEITERATOR_HPP
