#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

// todo: probably needs to be removed before handing in
// -> how to compile independently?
#include "IteratorTraits.hpp"
#include "VectorIterator.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef VectorIterator<T>		iterator;
		//typedef ConstVectorIterator<T>		const_iterator;
		typedef Allocator allocator_type;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef size_t size_type;

		iterator begin() {
			return iterator(_arr);
		}

	private:
		Allocator _allocator;
		size_type _capacity;
		size_type _size;
		T *_arr;

	public:
		explicit vector(const allocator_type &alloc = allocator_type()) : \
        _capacity(0), \
        _allocator(alloc), \
        _size(0), \
        _arr() {}

		explicit vector(size_type n, const allocator_type &alloc = allocator_type()) : \
        _capacity(n), \
        _allocator(alloc), \
        _size(n) {
			_arr = _allocator.allocate(n);
			for (size_type i = 0; i < n; ++i) {
				_allocator.construct(_arr, T());
			}
		}

		virtual ~vector() {
			for (int i = 0; i < _size; ++i)
				_allocator.destroy(&_arr[i]);
			_allocator.deallocate(_arr, _capacity);
		}

		vector &operator=(const vector &rhs) {
			if (&rhs == this)
				return *this;
			_size = rhs._size;
			_capacity = rhs._capacity;
		}

		size_type capacity() const {
			return _capacity;
		}

		size_type size() const {
			return _size;
		}

		void push_back(const T &x) {
			if (_size == _capacity) {
				doubleCapacity();
			}
			_arr[_size++] = x;
		}

		reference front() {
			return _arr[0];
		}

		const_reference front() const {
			return _arr[0];
		}

		reference back() {
			return _arr[_capacity - 1];
		}

		const_reference back() const {
			return _arr[_capacity - 1];
		}

		reference operator[](size_type pos) {
			return (_arr[pos]);
		}

		const_reference operator[](size_type pos) const {
			return (_arr[pos]);
		}

		const_reference at(int i) const {
			outOfRangeGuard(i);
			return _arr[i];
		}

		reference at(int i) {
			outOfRangeGuard(i);
			return _arr[i];
		}

	private:
		void doubleCapacity() {
			size_type newCapacity = _capacity * 2;
			if (_capacity == 0)
				++newCapacity;
			T *tmp = _allocator.allocate(newCapacity);
			for (int i = 0; i < _size; ++i) {
				tmp[i] = _arr[i];
				_allocator.destroy(&_arr[i]);
			}
			_allocator.deallocate(_arr, _capacity);
			_arr = tmp;
			_capacity = newCapacity;
		}

		void outOfRangeGuard(int i) const {
			if (i >= _size)
				throw std::out_of_range("index is out of range");
		}
	};
}
#endif //CONTAINERS_VECTOR_HPP
