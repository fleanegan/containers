#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

// todo: probably needs to be removed before handing in
// -> how to compile independently?
#define _DEBUG false

#include "IteratorTraits.hpp"
#include "VectorIterator.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef VectorIterator<T> iterator;
		//typedef ConstVectorIterator<T>		const_iterator;
		typedef Allocator allocator_type;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef size_t size_type;
		typedef ft::ptrdiff_t difference_type;

		iterator begin() const {
			return iterator(_arr);
		}

		iterator begin() {
			return iterator(_arr);
		}

		iterator end() const {
			return iterator(&_arr[_size]);
		}

		iterator end() {
			return iterator(&_arr[_size]);
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
			for (int i = 0; i < n; ++i)
				_allocator.construct(&_arr[i], T());
		}

		vector(const vector &rhs, const allocator_type &alloc = allocator_type()) : \
               _capacity(0), \
               _allocator(alloc), \
               _size(0),
			   _arr() {
			assign(rhs.begin(), rhs.end());
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
			_DEBUG && std::cout << "push back\n";
			if (_size == _capacity) {
				reserve(_capacity * 2);
			}
			_allocator.construct(&_arr[_size], x);
			_size++;
		}

		void clear() {
			if (_capacity != 0) {
				for (int i = 0; i < _size; ++i)
					_allocator.destroy(&_arr[i]);
				_allocator.deallocate(_arr, _capacity);
				_capacity = 0;
				_size = 0;
				_arr = NULL;
				_DEBUG && std::cout << "cleared" << std::endl;
			}
		}

		bool operator==(const vector &rhs) const {
			iterator ours = begin();
			iterator theirs = rhs.begin();
			if (_size != rhs._size)
				return false;
			while (ours != end() && theirs != rhs.end())
				if (*ours == *theirs) {
					++ours;
					++theirs;
				} else
					return false;
			return (ours == end() && theirs == rhs.end());
		}

		bool operator!=(const vector &rhs) const {
			return !(rhs == *this);
		}

		size_type max_size() const {
			return std::numeric_limits<difference_type>::max();
		}

		void assign(iterator from, iterator to) {
			size_type requiredCapacity = to - from;
			erase(begin(), end());
			reserve(requiredCapacity);
			while (from != to)
				push_back(*from++);
		}

		void assign(size_type count, const T &value) {
			erase(begin(), end());
			reserve(count);
			while (count--)
				push_back(value);
		}

		iterator insert(iterator pos, const T &value) {
			int index = pos - begin();
			insert(pos, 1, value);
			return (&_arr[index]);
		}

		void insert(iterator pos, size_type count, const T &value) {
			int index = pos - begin();
			size_type newSize = _size + count;
			size_type offset = index + count - 1;

			reserve(newSize);
			moveBackwardElements(begin() + index, count);
			for (size_type i = index; i <= offset; ++i){
				setElementAt(value, i);
			}
			_size = newSize;
		}

		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last){
			int index = pos - begin();
			size_type count = (last - first);
			//todo: replace with ft::distance(first, last);
			size_type newSize = _size + count;

			reserve(newSize);
			moveBackwardElements(begin() + index, count);
			pos = begin() + index;
			for (size_type i = index; first != last; ++i, ++first)
				setElementAt(*first, i);
			_size = newSize;
		}

		iterator erase(iterator first, iterator last) {
			int distance = last - first;
			iterator tmp = moveForwardElements(first, distance);
			for (int i = 0; i < distance; ++i)
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
			_DEBUG && std::cout << "reserving\n";
			if (! isReserveNecessary(newCapacity))
				return;
			arrayTooBigGuard(newCapacity);
			newCapacity = preventZeroCapacity(newCapacity);
			T *tmp = _allocator.allocate(newCapacity);
			for (int i = 0; i < _size; ++i) {
				_DEBUG && std::cout << "reserve loop\n";
				_allocator.construct(&tmp[i], _arr[i]);
				_allocator.destroy(&_arr[i]);
			}
			freeOldArray();
			_arr = tmp;
			_capacity = newCapacity;
		}


		void swap(vector &other){
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

		allocator_type get_allocator(){
			return _allocator();
		}

	private:
		void outOfRangeGuard(int i) const {
			if (i >= _size)
				throw std::out_of_range("index is out of range");
		}

		iterator moveForwardElements(iterator first, int distance) {
			iterator tmp = first + 1;

			while (first + distance != end()) {
				*first = *(first + distance);
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

	};
}
#endif //CONTAINERS_VECTOR_HPP
