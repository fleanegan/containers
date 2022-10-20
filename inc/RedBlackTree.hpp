#ifndef CONTAINERS_REDBLACKTREE_H
#define CONTAINERS_REDBLACKTREE_H

#include "BinarySearchTree.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <iostream>

namespace ft {
	template<typename TKey, typename TValue, typename NodeType = ft::RedBlackNode<TKey, TValue>, typename Compare = std::less<TKey>, typename Allocator = std::allocator<NodeType> >
	class RedBlackTree : public ft::BinarySearchTree<TKey, TValue, ft::RedBlackNode<TKey, TValue>, Compare, Allocator > {
	public:
		typedef TKey key_type;
		typedef TValue mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef NodeType Node;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

	public:
		RedBlackTree(const Compare &compare = Compare(), const allocator_type &alloc = allocator_type())
				: ft::BinarySearchTree<key_type, mapped_type, NodeType, Compare, allocator_type>(compare, alloc) {
			this->nullNode->isBlack = true;
		}

		RedBlackTree(const RedBlackTree<key_type, mapped_type, NodeType, key_compare, allocator_type> &rhs, key_compare, const allocator_type &alloc = allocator_type())
				: ft::BinarySearchTree<key_type, mapped_type, NodeType, key_compare, allocator_type>(alloc) {
			BinarySearchTree<key_type, mapped_type, NodeType, key_compare , allocator_type>::operator=(rhs);
			this->nullNode->isBlack = true;
		}

		RedBlackTree<key_type, mapped_type, NodeType, key_compare, allocator_type> &
		operator=(const RedBlackTree<key_type, mapped_type, NodeType, key_compare, allocator_type> &rhs) {
			BinarySearchTree<key_type, mapped_type, NodeType, key_compare , allocator_type>::operator=(rhs);
			return *this;
		}

		pointer insertByValue(ft::pair<key_type, mapped_type> const &in) {
			return insert(in);
		}

		pointer insert(ft::pair<key_type, mapped_type> const &in) {
			Node *newNode = BinarySearchTree<key_type, mapped_type, NodeType, Compare, allocator_type>::insert(in);

			fixupInsertion(newNode);
			return newNode;
		}

		void popNodeByPointer(Node *nodeToBeRemoved) {
			Node *successor;
			Node *potentialColourTrouble;
			bool isNodeToBeRemovedBlack = nodeToBeRemoved->isBlack;

			if (nodeToBeRemoved->isNullNode())
				return;
			if (nodeToBeRemoved->getRight()->isNullNode()) {
				potentialColourTrouble = nodeToBeRemoved->getLeft();
				this->replaceNode(nodeToBeRemoved, nodeToBeRemoved->getLeft());
			} else if (nodeToBeRemoved->getLeft()->isNullNode()) {
				potentialColourTrouble = nodeToBeRemoved->getRight();
				this->replaceNode(nodeToBeRemoved, nodeToBeRemoved->getRight());
			} else {
				successor = this->getInorderSuccessor(nodeToBeRemoved->getRight(), nodeToBeRemoved, nodeToBeRemoved->getRight());
				isNodeToBeRemovedBlack = successor->isBlack;
				potentialColourTrouble = successor->getRight();
				replaceNodeBySuccessor(nodeToBeRemoved, successor);
				successor->isBlack = nodeToBeRemoved->isBlack;
			}
			this->deleteNodeWithCleanUp(nodeToBeRemoved, false);
			if (isNodeToBeRemovedBlack) {
				fixupDeletion(potentialColourTrouble);
			}
		}

		bool isValid() const {
			ft::vector<int> blackNodeCountPerBranch;

            if (this->ft::BinarySearchTree<key_type, mapped_type, NodeType, Compare, Allocator>::isValid() == false)
                throw std::invalid_argument("oh oh");
			countBranches(this->rootNode, 0, blackNodeCountPerBranch);
			if (!this->rootNode->isBlack)
				return false;
			if (!isBlackCountSameInAllBranches(blackNodeCountPerBranch))
				return false;
			if (isContainingDoubleRed(this->rootNode))
				return false;
			return true;
		}

	protected:
		virtual void fixupDeletion(Node *troubleMaker) {
			Node *parent = troubleMaker->getParent();
			Node *sibling;

			while (troubleMaker != this->rootNode && troubleMaker->isBlack && troubleMaker->isNullNode() == false) {
				sibling = getSibling(troubleMaker, parent);
				if (sibling->isBlack == false)
					troubleMaker = fixupDeletionCaseOne(parent, sibling);
				if (sibling->getLeft()->isBlack && sibling->getRight()->isBlack)
					troubleMaker = fixupDeletionCaseTwo(parent, sibling);
				else if (isOuterChildBlack(sibling))
					fixupDeletionCaseThree(parent, &sibling);
				else
					troubleMaker = fixupDeletionCaseFour(parent, sibling);
			}
			troubleMaker->isBlack = true;
		}

		void fixupInsertion(Node *currentNode) {
			Node *uncle;
			Node *grandParent;
			Node *parent;

			while (currentNode->getParent()->isBlack == false) {
				parent = currentNode->getParent();
				grandParent = parent->getParent();
				uncle = getUncle(grandParent, parent);
				if (uncle->isBlack == parent->isBlack) {
					fixupColourChange(parent, grandParent, uncle);
					currentNode = grandParent;
				} else {
					currentNode = fixupRotate(currentNode, parent, grandParent);
				}
			}
			this->rootNode->isBlack = true;
		}

	private:
		pointer fixupRotate(Node *currentNode, Node *parent, Node *grandParent) {
			if (parent == grandParent->getRight())
				return fixupRotateRightBranch(currentNode, parent, grandParent);
			else
				return fixupRotateLeftBranch(currentNode, parent, grandParent);
		}

		pointer getUncle(Node *grandParent, Node *parent) const {
			if (parent == grandParent->getRight())
				return grandParent->getLeft();
			return grandParent->getRight();
		}

		pointer fixupRotateRightBranch(Node *currentNode, Node *parent, Node *grandParent) {
			if (currentNode == parent->getRight()) {
				fixupInnerRotationReColour(parent, grandParent);
				this->leftRotate(grandParent);
				return grandParent;
			}
			this->rightRotate(parent);
			return parent;
		}

		pointer fixupRotateLeftBranch(Node *currentNode, Node *parent, Node *grandParent) {
			if (currentNode == parent->getLeft()) {
				fixupInnerRotationReColour(parent, grandParent);
				this->rightRotate(grandParent);
				return grandParent;
			}
			this->leftRotate(parent);
			return parent;
		}

		void fixupInnerRotationReColour(Node *parent, Node *grandParent) {
			parent->isBlack = true;
			grandParent->isBlack = false;
		}

		void fixupColourChange(Node *parent, Node *grandParent, Node *uncle) {
			uncle->isBlack = true;
			parent->isBlack = true;
			grandParent->isBlack = false;
		}

		void replaceNodeBySuccessor(Node *nodeToBeRemoved, Node *successor) {
			if (successor->getParent() != nodeToBeRemoved) {
				this->replaceNode(successor, successor->getRight());
				successor->setRight(nodeToBeRemoved->getRight());
				successor->getRight()->setParent(successor);
			} else
				successor->getRight()->setParent(successor);
			this->replaceNode(nodeToBeRemoved, successor);
			successor->setLeft(nodeToBeRemoved->getLeft());
			successor->getLeft()->setParent(successor);
		}

		pointer fixupDeletionCaseOne(Node *parent, Node *sibling) {
			Node *troubleMaker;

			sibling->isBlack = true;
			parent->isBlack = false;
			if (sibling == parent->getLeft()) {
				this->leftRotate(parent);
				troubleMaker = sibling->getRight();
			} else {
				this->rightRotate(parent);
				troubleMaker = sibling->getLeft();
			}
			return troubleMaker;
		}

		pointer fixupDeletionCaseTwo(Node *parent, Node *sibling) {
			Node *troubleMaker;

			sibling->isBlack = false;
			troubleMaker = parent;
			return troubleMaker;
		}

		bool isOuterChildBlack(const Node *sibling) const {
			if (sibling == sibling->getParent()->getRight())
				return sibling->getRight()->isBlack;
			return sibling->getLeft()->isBlack;
		}

		void fixupDeletionCaseThree(Node *parent, Node **sibling) {
			(*sibling)->isBlack = false;
			if ((*sibling) == parent->getRight()) {
				(*sibling)->getLeft()->isBlack = true;
				this->rightRotate((*sibling));
				(*sibling) = parent->getRight();
			} else {
				(*sibling)->getRight()->isBlack = true;
				this->leftRotate((*sibling));
				(*sibling) = parent->getLeft();
			}
		}

		pointer fixupDeletionCaseFour(Node *parent, Node *sibling) {
			Node *troubleMaker;

			sibling->isBlack = parent->isBlack;
			parent->isBlack = true;
			if (sibling == parent->getRight()) {
				sibling->getRight()->isBlack = true;
				this->leftRotate(parent);
			} else {
				sibling->getLeft()->isBlack = true;
				this->rightRotate(parent);
			}
			troubleMaker = this->rootNode;
			return troubleMaker;
		}

		pointer getSibling(const Node *troubleMaker, Node *parent) const {
			Node *sibling;

			if (troubleMaker == parent->getLeft())
				sibling = parent->getRight();
			else
				sibling = parent->getLeft();
			return sibling;
		}

		void countBranches(Node *current, int sum, ft::vector<int> &result) const {
			if (current->isNullNode() == false) {
				sum += current->isBlack;
				countBranches(current->getRight(), sum, result);
				countBranches(current->getLeft(), sum, result);
				if (current->getRight()->isNullNode() && current->getLeft()->isNullNode())
					result.push_back(sum);
			}
		}

		bool isContainingDoubleRed(Node *current) const {
			if (current->isNullNode() == false) {
				if (current->isBlack == current->getParent()->isBlack && current->isBlack == false)
					return true;
				return isContainingDoubleRed(current->getRight()) || isContainingDoubleRed(current->getLeft());
			}
			return false;
		}

		bool isBlackCountSameInAllBranches(vector<int> &blackNodeCountPerBranch) const {
			vector<int>::iterator start = blackNodeCountPerBranch.begin();
			vector<int>::iterator end = blackNodeCountPerBranch.end();

			while (start != end) {
				if (*start != blackNodeCountPerBranch.front())
					return false;
				start++;
			}
			return true;
		}
	};
}
#endif //CONTAINERS_REDBLACKTREE_H
