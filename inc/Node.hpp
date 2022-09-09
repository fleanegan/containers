//
// Created by fschlute on 9/9/22.
//

#ifndef CONTAINERS_NODE_HPP
#define CONTAINERS_NODE_HPP

#include "Pair.hpp"

namespace ft {

	template<typename TKey, typename TValue>
	class SearchTreeStandardNode {
	protected:
		void *right;
		void *left;
		void *parent;
		bool isNull;
	public:
		ft::pair<const TKey, TValue> content;

		SearchTreeStandardNode(const TKey &key, const TValue &value, void *nullNode)
				: right(nullNode),
				  left(nullNode),
				  parent(nullNode),
				  isNull(false),
				  content(key, value){
		}

		SearchTreeStandardNode(const ft::pair<TKey, TValue> &in, void *nullNode)
				: right(nullNode),
				  left(nullNode),
				  parent(nullNode),
				  isNull(false),
				  content(in){
		}

		SearchTreeStandardNode(const SearchTreeStandardNode<TKey, TValue> &rhs,
							   void *nullNode) : right(nullNode),
												left(nullNode),
												parent(nullNode),
												isNull(false),
												content(rhs.content){
		}

		SearchTreeStandardNode() : right(this), left(this), parent(this), isNull(true) {
		}

		bool isNullNode() const {
			return isNull;
		}

		SearchTreeStandardNode *getRight() {
			return static_cast<SearchTreeStandardNode *>(right);
		}

		SearchTreeStandardNode *getRight() const {
			return static_cast<SearchTreeStandardNode *>(right);
		}

		void setRight(SearchTreeStandardNode *in) {
			right = in;
		}

		SearchTreeStandardNode *getLeft() {
			return static_cast<SearchTreeStandardNode *>(left);
		}

		SearchTreeStandardNode *getLeft() const {
			return static_cast<SearchTreeStandardNode *>(left);
		}

		void setLeft(SearchTreeStandardNode *in) {
			left = in;
		}

		SearchTreeStandardNode *getParent() {
			return static_cast<SearchTreeStandardNode *>(parent);
		}

		SearchTreeStandardNode *getParent() const {
			return static_cast<SearchTreeStandardNode *>(parent);
		}

		void setParent(SearchTreeStandardNode *in) {
			parent = in;
		}

		virtual ~SearchTreeStandardNode() {

		}
	};

	template<typename TKey, typename TValue>
	class RedBlackNode : public SearchTreeStandardNode<TKey, TValue>{
	public:
		bool isBlack;

		RedBlackNode(const TKey &key, const TValue &value, RedBlackNode<TKey, TValue> *nullNode) :
				SearchTreeStandardNode<TKey, TValue>(key, value, nullNode),
		        isBlack(false){

		}

		RedBlackNode(const ft::pair<TKey, TValue> &in, RedBlackNode<TKey, TValue> *nullNode) :
				SearchTreeStandardNode<TKey, TValue>(in, nullNode),
		        isBlack(false){
		}

		RedBlackNode(const RedBlackNode<TKey, TValue> &rhs, RedBlackNode<TKey, TValue> *nullNode) :
				SearchTreeStandardNode<TKey, TValue>(rhs, nullNode),
		        isBlack(rhs.isBlack){

		}

		RedBlackNode(const RedBlackNode<TKey, TValue> &rhs) : SearchTreeStandardNode<TKey, TValue>(rhs),
		        isBlack(rhs.isBlack){
		}

		RedBlackNode() : SearchTreeStandardNode<TKey, TValue>(), isBlack(false) {
		}

		bool isNullNode() const {
			return this->isNull;
		}

		RedBlackNode *getRight() {
			return static_cast<RedBlackNode *>(this->right);
		}

		RedBlackNode *getRight() const {
			return static_cast<RedBlackNode *>(this->right);
		}

		void setRight(RedBlackNode *in) {
			this->right = in;
		}

		RedBlackNode *getLeft() {
			return static_cast<RedBlackNode *>(this->left);
		}

		RedBlackNode *getLeft() const {
			return static_cast<RedBlackNode *>(this->left);
		}

		void setLeft(RedBlackNode *in) {
			this->left = in;
		}

		RedBlackNode *getParent() {
			return static_cast<RedBlackNode *>(this->parent);
		}

		RedBlackNode *getParent() const {
			return static_cast<RedBlackNode *>(this->parent);
		}

		void setParent(RedBlackNode *in) {
			this->parent = in;
		}

		virtual ~RedBlackNode() {

		}
	};

}



#endif //CONTAINERS_NODE_HPP
