//
// Created by fleanegan on 23.06.22.
//

#ifndef CONTAINERS_REVERSEITERATOR_HPP
#define CONTAINERS_REVERSEITERATOR_HPP
#include "IteratorTraits.hpp"

template <typename It>
class ReverseIterator{
	It iterator;
public:
	typedef typename It::difference_type difference_type;
	typedef typename It::value_type value_type;
	typedef typename It::reference reference;
	typedef typename It::pointer pointer;
	typedef typename It::iterator_category iterator_category;

	explicit ReverseIterator(It iterator) : iterator(iterator) {}

	reference &operator*(){
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

	difference_type operator-(const It &in) {
		iterator.operator+(in);
		return *this;
	}

	bool operator==(const It &rhs) const {
		return iterator.operator==(rhs);
	}

	bool operator!=(const It &rhs) const {
		return iterator.operator!=(rhs);
	}

	bool operator<(const It &rhs) const {
		return iterator.operator<(rhs);
	}

	bool operator>(const It &rhs) const {
		return iterator.operator>(rhs);
	}

	bool operator>=(const It &rhs) const {
		return iterator.operator>=(rhs);
	}

	bool operator<=(const It &rhs) const {
		return iterator.operator<=(rhs);
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
};

#endif //CONTAINERS_REVERSEITERATOR_HPP
