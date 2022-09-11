//
// Created by fleanegan on 23.06.22.
//

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP
#include "iterator_traits.hpp"

namespace ft {

	template<typename T>
	class ReverseIterator {
		T iterator;
	public:
		typedef typename T::difference_type difference_type;
		typedef typename T::value_type value_type;
		typedef typename T::reference reference;
		typedef typename T::pointer pointer;
		typedef typename T::iterator_category iterator_category;

		ReverseIterator() : iterator() {}

		explicit ReverseIterator(T it) : iterator(it) {

		}

		ReverseIterator(const ReverseIterator &revIt) : iterator(revIt.base()) {}

		template<class NonConstIterator>
		ReverseIterator(const ReverseIterator<NonConstIterator> &revIt) : iterator(T(revIt.base())) {}

		template<class NonConstIterator>
		ReverseIterator &operator=(const ReverseIterator<NonConstIterator> &rhs) {
			iterator = T(rhs.current());
			return *this;
		}

		pointer current() {
			return iterator.current();
		}

		pointer current() const {
			return iterator.current();
		}

		reference operator*() {
			T result(base());
			--result;
			return *result;
		}

		ReverseIterator operator++(int i) {
			ReverseIterator result = *this;
			iterator.operator--(i);
			return result;
		}

		ReverseIterator &operator++() {
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
			T resultBase = iterator.operator-(i);
			ReverseIterator<T> result(resultBase);
			return result;
		}

		ReverseIterator operator-(int i) {
			T resultBase = iterator.operator+(i);
			ReverseIterator<T> result(resultBase);
			return result;
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
			return -1 * iterator.operator-(in);
		}

		template<typename Iterator>
		bool operator==(const Iterator &rhs) const {
			return iterator.operator==(rhs.base());
		}

		template<typename Iterator>
		bool operator!=(const Iterator &rhs) const {
			return iterator.operator!=(rhs.base());
		}

		template<typename Iterator>
		bool operator<(const Iterator &rhs) const {
			return iterator.operator>(rhs.base());
		}

		template<typename Iterator>
		bool operator>(const Iterator &rhs) const {
			return iterator.operator<(rhs.base());
		}

		template<typename Iterator>
		bool operator>=(const Iterator &rhs) const {
			return iterator.operator<=(rhs.base());
		}

		template<typename Iterator>
		bool operator<=(const Iterator &rhs) const {
			return iterator.operator>=(rhs.base());
		}

		pointer operator->() const {
			T result(base());
			--result;
			return result.operator->();
		}

		pointer operator->() {
			T result(base());
			--result;
			return result.operator->();
		}

		reference operator*() const {
			T result(base());
			--result;
			return *result;
		}

		reference operator[](int index) {
			return iterator.operator[](-index - 1);
		}

		reference operator[](int index) const {
			return iterator.operator[](-index - 1);
		}

		T base() {
			return iterator;
		}

		T base() const {
			return iterator;
		}
	};

	template<typename T>
	ReverseIterator<T> operator+(int i, const ReverseIterator<T> &n) {
		ReverseIterator<T> result(n.current() - i);
		return result;
	}
}
#endif //CONTAINERS_REVERSE_ITERATOR_HPP
