#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

namespace ft {
	template<class T, class Allocator = std::allocator <T> >
	class vector {
	private:
		size_t _capacity;
		size_t _size;
		T *_arr;
	public:
		typedef typename Allocator::reference reference;
		vector() : \
		_capacity(1), \
		_size(0){
			_arr = new T[1];
		}

		virtual ~vector() {
			delete[] _arr;
		}

		size_t capacity() const{
			return _capacity;
		}

		size_t size() const{
			return _size;
		}

		void push_back(const T& x) {
			if (_size == _capacity){
				size_t newCapacity = _capacity * 2;
				T *tmp = new T[newCapacity];
				for (int i = 0; i < _size; ++i)
					tmp[i] = _arr[i];
				delete[] _arr;
				_arr = tmp;
				_capacity = newCapacity;
			}
			_arr[_size] = x;
			++_size;
		}

		reference front() {
			return _arr[0];
		}

		reference back() {
			return _arr[_capacity - 1];
		}
	};
}
// types:
#endif //CONTAINERS_VECTOR_HPP
