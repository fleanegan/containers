#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef Container container_type;
	protected:
		Container c;

	public:
		explicit
		stack(const Container &c = Container())
				: c(c) {}

		bool empty() const { return c.empty(); }

		size_type size() const { return c.size(); }

		value_type &top() { return c.back(); }

		const value_type &top() const { return c.back(); }

		void push(const value_type &x) { c.push_back(x); }

		void pop() { c.pop_back(); }

	private:
		template<typename _T, typename _container>
		friend bool
		operator==(const stack<_T, _container> &, const stack<_T, _container> &);

		template<typename _Tp1, typename _Seq1>
		friend bool
		operator<(const stack<_Tp1, _Seq1> &, const stack<_Tp1, _Seq1> &);
	};

	template<class T, class Container>
	bool operator==(const stack<T, Container> &x,
					const stack<T, Container> &y) {
		return x.c == y.c;
	}

	template<class T, class Container>
	bool operator<(const stack<T, Container> &x,
				   const stack<T, Container> &y) {
		return x.c < y.c;
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container> &x,
					const stack<T, Container> &y) {
		return !(x == y);
	}

	template<class T, class Container>
	bool operator>(const stack<T, Container> &x,
				   const stack<T, Container> &y) {
		return !(x < y) && x != y;
	}

	template<class T, class Container>
	bool operator>=(const stack<T, Container> &x,
					const stack<T, Container> &y) {
		return x == y || x > y;
	}

	template<class T, class Container>
	bool operator<=(const stack<T, Container> &x,
					const stack<T, Container> &y) {
		return x == y || x < y;
	}
}

#endif //CONTAINERS_STACK_HPP
