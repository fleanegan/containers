//
// Created by fleanegan on 17.06.22.
//

#ifndef CONTAINERS_VECTORITERATOR_HPP
#define CONTAINERS_VECTORITERATOR_HPP

#include "vector.hpp"
#include "Utils.hpp"

namespace ft {

	template<typename T>
	class VectorIterator {
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	private:
		pointer _ptr;
	public:
		VectorIterator() : _ptr() {}

		VectorIterator(const pointer ptr) : _ptr(ptr) {
		}

		template<class U>
		VectorIterator(const VectorIterator<U> &it) : _ptr(it.current()) {
		}

		VectorIterator(const VectorIterator &rhs) : _ptr(rhs._ptr) {}

		template<class NonConstIterator>
		VectorIterator &operator=(const NonConstIterator &rhs) {
			_ptr = rhs.current();
			return *this;
		}

		virtual ~VectorIterator(){

		}

		pointer current(){
			return _ptr;
		}

		pointer current() const{
			return _ptr;
		}

		template <typename Iterator>
		bool operator==(const Iterator &rhs) const {
			return _ptr == rhs.current();
		}

		template <typename Iterator>
		bool operator!=(const Iterator &rhs) const {
			return _ptr != rhs.current();
		}

		template <typename Iterator>
		bool operator<(const Iterator &rhs) const {
			return _ptr < rhs.current();
		}

		template <typename Iterator>
		bool operator>(const Iterator &rhs) const {
			return _ptr > rhs.current();
		}

		template <typename Iterator>
		bool operator>=(const Iterator &rhs) const {
			return _ptr >= rhs.current();
		}

		template <typename Iterator>
		bool operator<=(const Iterator &rhs) const {
			return _ptr <= rhs.current();
		}

		pointer operator->() const {
			return _ptr;
		}

		pointer operator->() {
			return _ptr;
		}

		reference operator*() {
			return *_ptr;
		}

		reference operator*() const {
			return *_ptr;
		}

		reference operator[](int index) {
			return _ptr[index];
		}

		reference operator[](int index) const {
			return _ptr[index];
		}

		VectorIterator &operator++() {
			++_ptr;
			return *this;
		}

		VectorIterator operator++(int i) {
			VectorIterator<T> result = *this;
			if (i == 0)
				_ptr++;
			else
				_ptr += i;
			return result;
		}

		VectorIterator &operator--() {
			--_ptr;
			return *this;
		}

		VectorIterator operator--(int i) {
			VectorIterator<T> result = *this;
			if (i == 0)
				_ptr--;
			else
				_ptr -= i;
			return result;
		}

		VectorIterator operator+(int i) {
			VectorIterator<T> result(*this);
			result += i;
			return result;
		}

		VectorIterator operator-(int i) {
			VectorIterator<T> result(*this);
			result -= i;
			return result;
		}

		VectorIterator &operator+=(int i) {
			_ptr += i;
			return *this;
		}

		VectorIterator &operator-=(int i) {
			_ptr -= i;
			return *this;
		}

		template<class Iterator>
		typename ft::enable_if<!ft::is_integral<Iterator>::value, difference_type>::type
		operator-(const Iterator &in) const {
			return const_cast<T *>(_ptr) - const_cast<T *>(in.current());
		}

		template<class Iterator>
		typename ft::enable_if<!ft::is_integral<Iterator>::value, difference_type>::type
		operator-(const Iterator &in) {
			return _ptr - in.current();
		}
	};

	template <typename T>
	VectorIterator<T> operator+(int i, const VectorIterator<T>& n)
	{
		VectorIterator<T> result(&*n + i);
		return result;
	}
}

#endif //CONTAINERS_VECTORITERATOR_HPP
