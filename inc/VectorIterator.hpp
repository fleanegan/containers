//
// Created by fleanegan on 17.06.22.
//

#ifndef CONTAINERS_VECTORITERATOR_HPP
#define CONTAINERS_VECTORITERATOR_HPP

#include "Vector.hpp"

namespace ft {

	template<typename T>
	class VectorIterator {
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	private:
		pointer _ptr;
	public:
		VectorIterator() : _ptr() {}

		VectorIterator(pointer ptr) : _ptr(ptr) {}

		VectorIterator(const VectorIterator &rhs) : _ptr(rhs._ptr) {}

		VectorIterator &operator=(const VectorIterator &rhs) {
			_ptr = rhs._ptr;
			return *this;
		}

		virtual ~VectorIterator(){

		}

		bool operator==(const VectorIterator &rhs) const {
			return _ptr == rhs._ptr;
		}

		bool operator!=(const VectorIterator &rhs) const {
			return _ptr != rhs._ptr;
		}

		bool operator<(const VectorIterator &rhs) const {
			return _ptr < rhs._ptr;
		}

		bool operator>(const VectorIterator &rhs) const {
			return _ptr > rhs._ptr;
		}

		bool operator>=(const VectorIterator &rhs) const {
			return _ptr >= rhs._ptr;
		}

		bool operator<=(const VectorIterator &rhs) const {
			return _ptr <= rhs._ptr;
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

		difference_type operator-(const VectorIterator &in) {
			return _ptr - in._ptr;
		}
	};

	template<typename T>
	class ConstVectorIterator {
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	private:
		pointer _ptr;
	public:
		ConstVectorIterator() : _ptr() {}

		ConstVectorIterator(pointer ptr) : _ptr(ptr) {}


		ConstVectorIterator(const ConstVectorIterator &rhs) : _ptr(rhs._ptr) {}

		ConstVectorIterator &operator=(const ConstVectorIterator &rhs) {
			_ptr = rhs._ptr;
			return *this;
		}

		virtual ~ConstVectorIterator(){

		}

		bool operator==(const ConstVectorIterator &rhs) const {
			return _ptr == rhs._ptr;
		}

		bool operator!=(const ConstVectorIterator &rhs) const {
			return _ptr != rhs._ptr;
		}

		bool operator<(const ConstVectorIterator &rhs) const {
			return _ptr < rhs._ptr;
		}

		bool operator>(const ConstVectorIterator &rhs) const {
			return _ptr > rhs._ptr;
		}

		bool operator>=(const ConstVectorIterator &rhs) const {
			return _ptr >= rhs._ptr;
		}

		bool operator<=(const ConstVectorIterator &rhs) const {
			return _ptr <= rhs._ptr;
		}

		pointer operator->() const {
			return _ptr;
		}

		reference operator*() const {
			return *_ptr;
		}

		reference operator[](int index) const {
			return _ptr[index];
		}

		ConstVectorIterator &operator++(){
			++_ptr;
			return *this;
		}

		ConstVectorIterator operator++(int i) {
			ConstVectorIterator<T> result = *this;
			if (i == 0)
				_ptr++;
			else
				_ptr += i;
			return result;
		}

		ConstVectorIterator &operator--() {
			--_ptr;
			return *this;
		}

		ConstVectorIterator operator--(int i) {
			ConstVectorIterator<T> result = *this;
			if (i == 0)
				_ptr--;
			else
				_ptr -= i;
			return result;
		}

		ConstVectorIterator operator+(int i) const {
			ConstVectorIterator<T> result(*this);
			result += i;
			return result;
		}

		ConstVectorIterator operator-(int i) const {
			ConstVectorIterator<T> result(*this);
			result -= i;
			return result;
		}

		ConstVectorIterator &operator+=(int i) {
			_ptr += i;
			return *this;
		}

		ConstVectorIterator &operator-=(int i) {
			_ptr -= i;
			return *this;
		}

		difference_type operator-(const ConstVectorIterator &in) const {
			return _ptr - in._ptr;
		}
	};
}

#endif //CONTAINERS_VECTORITERATOR_HPP
