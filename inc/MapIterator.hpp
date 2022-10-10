//
// Created by fleanegan on 02.09.22.
//

#ifndef CONTAINERS_MAPITERATOR_HPP
#define CONTAINERS_MAPITERATOR_HPP

#include "map.hpp"

namespace ft {

	template<typename ValueType, typename Key, typename T, typename NodeType, typename Compare = std::less<Key> >
	class MapIterator {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef NodeType Node;
		typedef ValueType value_type;
		typedef ValueType* pointer;
		typedef ValueType const * const_pointer;
		typedef ValueType& reference;
		typedef ValueType const & const_reference;
		typedef ft::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef Compare compare_type;

		Compare compare;
	private:
		Node *currentNode;
		Node *ext;
	public:
		MapIterator(const compare_type &compare = compare_type()) :		compare(compare),
																		   currentNode(),
																		   ext(){}

		MapIterator(Node *const node, Node *const ext, const compare_type &compare = compare_type()) : 	compare(compare),
																										  currentNode(node),
																										  ext(ext){
		}

		template<class UVType, class UKey, class UValue, class UNode>
		MapIterator(const MapIterator<UVType, UKey, UValue, UNode> &it) : 	compare(it.compare),
																			currentNode(it.current()),
																			 ext(it.getExt()){
		}

		MapIterator(const MapIterator &rhs) : 	compare(rhs.compare),
												 currentNode(rhs.currentNode),
												 ext(rhs.ext){

		}

		MapIterator &operator--() {
			moveToPrevNode();
			return *this;
		}

		MapIterator &operator++() {
			moveToNextNode();
			return *this;
		}

		Node *current() {
			return currentNode;
		}

		Node *current() const {
			return currentNode;
		}


		Node *getExt() {
			return ext;
		}

		Node *getExt() const {
			return ext;
		}


		MapIterator operator--(int i) {
			MapIterator<ValueType, key_type, mapped_type, NodeType, Compare> result = *this;
			if (i == 0) {
				moveToPrevNode();
			}
			return result;
		}

		MapIterator operator++(int i) {
			MapIterator<ValueType, key_type, mapped_type, NodeType, Compare> result = *this;
			if (i == 0) {
				moveToNextNode();
			}
			return result;
		}

		pointer operator->() {
			return &currentNode->content;
		}


		const_pointer operator->() const{
			return &currentNode->content;
		}

		reference operator*() {
			return currentNode->content;
		}

		const_reference operator*() const{
			return currentNode->content;
		}
	private:
		void moveToNextNode() {
			Key originalKey;

//			std::cerr 	<< " Mapit: toNextNode, currently at:	" << currentNode->content.first
//						<< ", leftEx: " << ext->getLeft()->content.first
//						<< ", rightEx: " << ext->getRight()->content.first;
			/*if (currentNode->getLeft() != ext->getParent())
				std::cerr	<< ", nodeToLeft: " << currentNode->getLeft()->content.first;
			if (currentNode->getRight() != ext->getParent())
				std::cerr	<< ", nodeToRight: " << currentNode->getRight()->content.first;
			std::cerr <<  std::endl;
*/
			if (currentNode->isNullNode())
				currentNode = ext->getLeft();
			else {
				originalKey = currentNode->content.first;
				if (currentNode->getRight()->isNullNode() == false) {
					currentNode = currentNode->getRight();
					while (currentNode->getLeft()->isNullNode() == false)
						currentNode = currentNode->getLeft();
				} else {
					while (currentNode == currentNode->getParent()->getRight() && currentNode->getParent()->isNullNode() == false)
						currentNode = currentNode->getParent();
					if (currentNode->getParent()->isNullNode() == false &&
						currentNode == currentNode->getParent()->getLeft())
						currentNode = currentNode->getParent();
					if (compare(currentNode->content.first, originalKey))
						while (currentNode->isNullNode() == false)
							currentNode = currentNode->getRight();
					if (currentNode->isNullNode() == false && currentNode->content.first == originalKey)
						currentNode = currentNode->getRight();
				}
			}
		}

		void moveToPrevNode() {
			Key originalKey;

			if (currentNode->isNullNode())
				currentNode = ext->getRight();
			else {
				originalKey = currentNode->content.first;
				if (currentNode->getLeft()->isNullNode() == false) {
					currentNode = currentNode->getLeft();
					while (currentNode->getRight()->isNullNode() == false)
						currentNode = currentNode->getRight();
				} else {
					while (currentNode == currentNode->getParent()->getLeft() && currentNode->getParent()->isNullNode() == false)
						currentNode = currentNode->getParent();
					if (currentNode->getParent()->isNullNode() == false &&
						currentNode == currentNode->getParent()->getRight())
						currentNode = currentNode->getParent();
					if (compare(currentNode->content.first, originalKey) == false)
						while (currentNode->isNullNode() == false)
							currentNode = currentNode->getRight();
				}
			}
		}

	public:
		bool operator==(const MapIterator &rhs) const {
			return currentNode == rhs.currentNode;
		}

		template<class VT, class KT, class MT, class NT, class CP, class CVT, class CKT, class CMT, class CNT, class CCP>
		friend bool operator==(const MapIterator<VT, KT, MT, NT, CP> &lhs, const MapIterator<CVT, CKT, CMT, CNT, CCP> &rhs);

		bool operator!=(const MapIterator &rhs) const {
			return !(rhs == *this);
		}
	};

	template<class VT, class KT, class MT, class NT, class CP, class CVT, class CKT, class CMT, class CNT, class CCP>
	bool operator==(const MapIterator<VT, KT, MT, NT, CP> &lhs, const MapIterator<CVT, CKT, CMT, CNT, CCP> &rhs) {
		MapIterator<VT const, KT, MT, NT const, CP> mlhs(lhs);
		MapIterator<VT const, KT, MT, NT const, CP> mrhs(rhs);

		return mrhs.currentNode == mlhs.currentNode;
	}

	template<class VT, class KT, class MT, class NT, class CP, class CVT, class CKT, class CMT, class CNT, class CCP>
	bool operator!=(const MapIterator<VT, KT, MT, NT, CP> &lhs, const MapIterator<CVT, CKT, CMT, CNT, CCP> &rhs) {
		return !(lhs == rhs);
	}
}

#endif //CONTAINERS_MAPITERATOR_HPP
