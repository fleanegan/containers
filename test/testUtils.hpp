#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "gtest/gtest.h"
#include "../inc/IteratorTraits.hpp"
#include "../inc/Vector.hpp"
#include "../inc/VectorIterator.hpp"
#include "../inc/Stack.hpp"
#include "../inc/Utils.hpp"
#include "../inc/Pair.hpp"
#include "../inc/Map.hpp"
#include "../inc/MapIterator.hpp"
#include "../inc/BinarySearchTree.hpp"
#include "../inc/RedBlackTree.hpp"
#include <iostream>
#define _DEBUG_SD 0

struct simpleDummy {
	int *i = NULL;
	int moves;
	bool debug;

	simpleDummy() {
		debug = false;
		debug && std::cout << "default constructor" << std::endl;
		i = new int;
		moves = 0;
	}

	explicit simpleDummy(int in) {
		debug = false;
		debug && std::cout << "argument constructor. i is " << (void *) i << std::endl;
		i = new int;
		*i = in;
		moves = 0;
	}

	simpleDummy(const simpleDummy &other) {
		debug = other.debug;
		debug && std::cout << "copy constructor. i is " << (void *) i << std::endl;
		i = new int;
		*i = *(other.i);
		moves = other.moves + 1;
	}

	simpleDummy &operator=(const simpleDummy &other) {
		debug = other.debug;
		debug && std::cout << "assignment start, updating addr: " << (void *) i << " from addr: " << (void *) other.i << std::endl;
		*i = *(other.i);
		moves = other.moves + 1;
		debug && std::cout << "assignment end" << std::endl;
		return *this;
	}

	bool operator<(const simpleDummy &rhs) const {
		return *i < *rhs.i;
	}

	bool operator>(const simpleDummy &rhs) const {
		return rhs < *this;
	}

	bool operator<=(const simpleDummy &rhs) const {
		return !(rhs < *this);
	}

	bool operator>=(const simpleDummy &rhs) const {
		return !(*this < rhs);
	}

	bool operator==(const simpleDummy &rhs) const {
		return i == rhs.i;
	}

	bool operator!=(const simpleDummy &rhs) const {
		return !(rhs == *this);
	}

	int &operator*() {
		return *i;
	}

	int &operator*() const {
		return *i;
	}

	void dummyFunction() {}

	~simpleDummy() {
		debug && std::cout << "destructor" << std::endl;
		delete i;
	}
};

ft::vector<simpleDummy> createTestDummyVector() {
	ft::vector<simpleDummy> result;
	for (int i = 1; i < 6; ++i) {
		result.push_back(simpleDummy(i));
	}
	return result;
}
//
//template<class T>
//void testIterator(typename T::iterator it){
//	(void) it;
//}

template<typename It>
bool getHasSpecializedTag(std::bidirectional_iterator_tag a) {
	_DEBUG_SD && std::cout << "specialized function called" << std::endl;
	return true;
}

template<typename It>
bool getHasSpecializedTag(std::input_iterator_tag a) {
	_DEBUG_SD && std::cout << "generalized function called" << std::endl;
	return false;
}

template<typename It>
bool getHasSpecializedTag() {
	return getHasSpecializedTag<It>(typename It::iterator_category());
}

template<typename T>
class StupidInputIterator {
public:
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef std::input_iterator_tag iterator_category;
private:
	pointer _ptr;
public:
	StupidInputIterator(pointer ptr) : _ptr(ptr) {}

	bool operator==(const StupidInputIterator &rhs) const {
		return _ptr == rhs._ptr;
	}

	bool operator!=(const StupidInputIterator &rhs) const {
		return _ptr != rhs._ptr;
	}

	reference operator*() const {
		return *_ptr;
	}

	StupidInputIterator &operator++(){
		++_ptr;
		return *this;
	}

	StupidInputIterator operator++(int i) {
		StupidInputIterator<T> result = *this;
		if (i == 0)
			_ptr++;
		else
			while (i--)
				++_ptr;
		return result;
	}

	StupidInputIterator &operator--() {
		--_ptr;
		return *this;
	}

	StupidInputIterator operator--(int i) {
		StupidInputIterator<T> result = *this;
		if (i == 0)
			_ptr--;
		else
			while (i--)
				--_ptr;
		return result;
	}
};

void assertEqualityOfValuesContainedBySimpleDummyVector(ft::vector<simpleDummy> &x, ft::vector<simpleDummy> &y, size_t forElements){
	ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";

	for (int i = 0; i < forElements; ++i) {
		EXPECT_EQ(*x[i], *y[i]) << "Vectors x and y differ at index " << i;
	}
}

/*
 * 		      3
	         / \
	        1  16
  		   /    \
  		 7      19
		/ \    /  \
	   5   8  18   20
	  / \
	 4   6
*/
ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> generateFiveLevelTree() {
	ft::BinarySearchTree<int, int, ft::SearchTreeStandardNode> result;
	result.insert(ft::make_pair(3, 0));
	result.insert(ft::make_pair(1, 0));
	result.insert(ft::make_pair(16, 0));
	result.insert(ft::make_pair(19, 0));
	result.insert(ft::make_pair(7, 0));
	result.insert(ft::make_pair(5, 0));
	result.insert(ft::make_pair(8, 0));
	result.insert(ft::make_pair(4, 0));
	result.insert(ft::make_pair(6, 0));
	result.insert(ft::make_pair(20, 0));
	result.insert(ft::make_pair(18, 0));
	return result;
}

template<typename TKey, typename TValue>
struct ExposedRedBlackTree : public ft::RedBlackTree<TKey, TValue>{
	typedef ft::RedBlackNode<TKey, TValue> Node;

	void fixupDeletion(Node *nodeToBeDeleted){
		ft::RedBlackTree<TKey, TValue>::fixupDeletion(nodeToBeDeleted);
	}
};


ft::RedBlackTree<simpleDummy, simpleDummy> generateBigRbt(){
	ft::RedBlackTree<simpleDummy, simpleDummy> rbt;
	rbt.insertByValue(ft::make_pair(simpleDummy(1), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(2), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(3), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(6), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(0), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(10), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(11), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(9), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(13), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(7), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(12), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(14), simpleDummy(0)));
	rbt.insertByValue(ft::make_pair(simpleDummy(19), simpleDummy(0)));
	return rbt;
}

ExposedRedBlackTree<int, int> generateBrokenRbtClassOne() {
	ExposedRedBlackTree<int, int> rbt;
	rbt.insert(ft::make_pair(1, 0));
	rbt.insert(ft::make_pair(2, 0));
	rbt.insert(ft::make_pair(0, 0));
	rbt.insert(ft::make_pair(3, 0));
	rbt.insert(ft::make_pair(4, 0));
	rbt.root()->right->right->isBlack = true;
	rbt.root()->right->left->isBlack = true;
	rbt.root()->right->isBlack = false;
	return rbt;
}

ExposedRedBlackTree<int, int> generateBrokenRbtClassTwo() {
	ExposedRedBlackTree<int, int> rbt = generateBrokenRbtClassOne();
	rbt.root()->right->isBlack = true;
	return rbt;
}

ExposedRedBlackTree<int, int> generateBrokenRbtClassThree() {
	ExposedRedBlackTree<int, int> rbt = generateBrokenRbtClassTwo();
	rbt.root()->right->left->isBlack = false;
	return rbt;
}

ExposedRedBlackTree<int, int> generateBrokenRbtClassFour() {
	ExposedRedBlackTree<int, int> rbt;
	rbt.insert(ft::make_pair(3, 0));
	rbt.insert(ft::make_pair(4, 0));
	rbt.insert(ft::make_pair(1, 0));
	rbt.insert(ft::make_pair(2, 0));
	rbt.insert(ft::make_pair(0, 0));
	rbt.root()->left->right->isBlack = true;
	rbt.root()->left->left->isBlack = true;
	rbt.root()->right->right->isBlack = false;
	return rbt;
}

//		 3
//	  1     4
//  0  2
ft::map<simpleDummy, simpleDummy> generateTestMap() {
	ft::map<simpleDummy, simpleDummy> map;
	map.insert(ft::make_pair(3, 0));
	map.insert(ft::make_pair(4, 0));
	map.insert(ft::make_pair(1, 0));
	map.insert(ft::make_pair(2, 0));
	map.insert(ft::make_pair(0, 0));
	return map;
}

#endif     // TEST_UTILS_H
