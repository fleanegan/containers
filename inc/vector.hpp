#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "VectorIterator.hpp"
#include "reverse_iterator.hpp"
#include <limits>
#include "algorithm.hpp"
#include <iostream>
#include <stdexcept>

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef VectorIterator<T> iterator;
		typedef VectorIterator<const T> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef Allocator allocator_type;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef std::size_t size_type;
		typedef ft::ptrdiff_t difference_type;

	private:
		size_type _capacity;
		Allocator _allocator;
		size_type _size;
		T *_arr;

	public:
		explicit vector(const allocator_type &alloc = allocator_type()) : \
                _capacity(0), \
                _allocator(alloc), \
                _size(0), \
                _arr() {}

		explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator()){
			initSize(count);
			_allocator = alloc;
			_arr = _allocator.allocate(count);
			for (size_type i = 0; i < count; ++i)
				_allocator.construct(&_arr[i], value);
		}

		void initSize(const size_type &count){
			if (count >= max_size())
				throw std::length_error("cannot be bigger than max_size");
			_capacity = count;
			_size = count;
		}

		vector(const vector &rhs, const allocator_type &alloc = allocator_type()) : \
               _capacity(0), \
               _allocator(alloc), \
               _size(0),
			   _arr() {
			assign(rhs.begin(), rhs.end());
		}

		template<class InputIt>
		vector(InputIt first, InputIt last,
			   const Allocator &alloc = Allocator()) : \
               _capacity(0), \
               _allocator(alloc), \
               _size(0),
			   _arr() {
			assign(first, last);
		}

		virtual ~vector() {
			clear();
		}

		vector &operator=(const vector &rhs) {
			if (&rhs == this)
				return *this;
			assign(rhs.begin(), rhs.end());
			return *this;
		}

		size_type capacity() const {
			return _capacity;
		}

		size_type size() const {
			return _size;
		}

		reference front() {
			return _arr[0];
		}

		const_reference front() const {
			return _arr[0];
		}

		reference back() {
			return _arr[_size - 1];
		}

		const_reference back() const {
			return _arr[_size - 1];
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

		void push_back(const T &x) {
			if (_size == _capacity) {
				reserve(_capacity * 2);
			}
			_allocator.construct(&_arr[_size], x);
			_size++;
		}

		void clear() {
			if (_capacity != 0) {
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(&_arr[i]);
				_allocator.deallocate(_arr, _capacity);
				_capacity = 0;
				_size = 0;
				_arr = NULL;
			}
		}

		size_type max_size() const {
			return std::numeric_limits<difference_type>::max() / sizeof(T);
		}

		const_iterator begin() const {
			return const_iterator(_arr);
		}

		iterator begin() {
			return iterator(_arr);
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_iterator end() const {
			return const_iterator(&_arr[_size]);
		}

		iterator end() {
			return iterator(&_arr[_size]);
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		bool empty() const {
			return _size == 0;
		}

		template<class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		assign(InputIterator from, InputIterator to) {
			assign<InputIterator>(from, to, typename ft::iterator_traits<InputIterator>::iterator_category());
		}

		void assign(size_type count, const T &value) {
			erase(begin(), end());
			reserve(count);
			while (count--)
				push_back(value);
		}

		template<class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value, iterator>::type
		insert(InputIt pos, const T &value) {
			int index = pos - begin();
			insert(pos, 1, value);
			return (&_arr[index]);
		}

		template<class InputIterator>
		void
		insert(InputIterator pos, size_type count, const T &value) {
			int index = pos - begin();
			size_type newSize = _size + count;
			size_type offset = index + count - 1;

			reserve(newSize);
			//todo: segfault if pos > beginning and newSize == newCapacity
			moveBackwardElements(begin() + index, count);
			for (size_type i = index; i <= offset; ++i) {
				setElementAt(value, i);
			}
			_size = newSize;
		}

		template<class InputIt, class I>
		typename ft::enable_if<!ft::is_integral<I>::value, void>::type
		insert(InputIt pos, I first, I last) {
			int index = pos - begin();
			size_type count = ft::distance(first, last);
			size_type newSize = _size + count;

			reserve(newSize);
			moveBackwardElements(begin() + index, count);
			pos = begin() + index;
			for (size_type i = index; first != last; ++i, ++first)
				setElementAt(*first, i);
			_size = newSize;
		}

		iterator erase(iterator first, iterator last) {
			size_type distance = ft::distance(first, last);
			iterator tmp = moveForwardElements(first, distance);
			for (size_type i = 0; i < distance; ++i)
				pop_back();
			return tmp;
		}

		iterator erase(iterator pos) {
			return erase(pos, pos + 1);
		}

		void pop_back() {
			_allocator.destroy(&_arr[_size - 1]);
			--_size;
		}

		void reserve(size_type newCapacity) {
			if (!isReserveNecessary(newCapacity))
				return;
			arrayTooBigGuard(newCapacity);
			newCapacity = preventZeroCapacity(newCapacity);
			T *tmp = _allocator.allocate(newCapacity);
			for (size_type i = 0; i < _size; ++i) {
				_allocator.construct(&tmp[i], _arr[i]);
				_allocator.destroy(&_arr[i]);
			}
			freeOldArray();
			_arr = tmp;
			_capacity = newCapacity;
		}

		void swap(vector &other) {
			size_type tmpSize;
			pointer tmpArr;

			tmpSize = _size;
			_size = other._size;
			other._size = tmpSize;
			tmpSize = _capacity;
			_capacity = other._capacity;
			other._capacity = tmpSize;
			tmpArr = _arr;
			_arr = other._arr;
			other._arr = tmpArr;
		}

		void resize(size_type sz, T c = T()) {
			if (sz > _size)
				insert(end(), sz - _size, c);
			else if (sz < _size)
				erase(begin() + sz, end());
		}

		allocator_type get_allocator() {
			return _allocator;
		}

	private:
		void outOfRangeGuard(size_type i) const {
			if (i >= _size)
				throw std::out_of_range("index is out of range");
		}

		iterator moveForwardElements(iterator first, size_type distance) {
			iterator tmp = first;

			while (first + distance != end()) {
				setElementAt(*(first + distance), first - begin());
				++first;
			}
			return tmp;
		}

		iterator moveBackwardElements(iterator first, size_type distance) {
			iterator tmp = end() + distance - 1;

			while (tmp != first + distance - 1) {
				setElementAt(*(tmp - distance), tmp - begin());
				--tmp;
			}
			return tmp;
		}

		void setElementAt(const T &value, size_type i) {
			if (i >= _size)
				_allocator.construct(&_arr[i], value);
			else
				_arr[i] = value;
		}

		void freeOldArray() {
			if (_arr != NULL)
				_allocator.deallocate(_arr, _capacity);
		}

		bool isReserveNecessary(size_type newCapacity) const {
			if (newCapacity <= _capacity && _capacity != 0)
				return false;
			return true;
		}

		void arrayTooBigGuard(size_type newCapacity) const {
			if (newCapacity > max_size())
				throw std::length_error("the requested capacity is too big");
		}

		size_type preventZeroCapacity(size_type newCapacity) const {
			if (_capacity == 0 && newCapacity == 0)
				++newCapacity;
			return newCapacity;
		}

		template<class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		assign(InputIterator from, InputIterator to, std::forward_iterator_tag) {
			size_type requiredCapacity = ft::distance(from, to);
			erase(begin(), end());
			reserve(requiredCapacity);
			while (from != to) {
				push_back((*from));
				++from;
			}
		}

		template<class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		assign(InputIterator from, InputIterator to, std::input_iterator_tag) {
			erase(begin(), end());
			while (from != to) {
				push_back((*from));
				++from;
			}
		}
	};

	template<class T, class Allocator>
	bool operator==(const ft::vector<T, Allocator> &x,
					const ft::vector<T, Allocator> &y) {
		typename ft::vector<T, Allocator>::const_iterator ours = x.begin();
		typename ft::vector<T, Allocator>::const_iterator theirs = y.begin();
		if (x.size() != y.size())
			return false;
		while (ours != x.end() && theirs != y.end())
			if (*ours == *theirs) {
				++ours;
				++theirs;
			} else
				return false;
		return (ours == x.end() && theirs == y.end());
	}

	template<class T, class Allocator>
	bool operator!=(const ft::vector<T, Allocator> &x,
					const ft::vector<T, Allocator> &y) {
		return !(x == y);
	}

	template<class T, class Allocator>
	bool operator<(const vector<T, Allocator> &x,
				   const vector<T, Allocator> &y) {
		typedef typename ft::vector<T>::size_type size_type;
		size_type minSize = std::min(x.size(), y.size());
		for (size_type i = 0; i < minSize; ++i)
			if (x[i] != y[i])
				return x[i] < y[i];
		return x.size() < y.size();
	}

	template<class T, class Allocator>
	bool operator>(const vector<T, Allocator> &x,
				   const vector<T, Allocator> &y) {
		return !(x < y) && (x != y);
	}

	template<class T, class Allocator>
	bool operator>=(const vector<T, Allocator> &x,
					const vector<T, Allocator> &y) {
		return x == y || x > y;
	}

	template<class T, class Allocator>
	bool operator<=(const vector<T, Allocator> &x,
					const vector<T, Allocator> &y) {
		return x == y || x < y;
	}

	template<class T, class Allocator>
	void swap(vector<T, Allocator> &x, vector<T, Allocator> &y) {
		x.swap(y);
	}
}
#endif //CONTAINERS_VECTOR_HPP
