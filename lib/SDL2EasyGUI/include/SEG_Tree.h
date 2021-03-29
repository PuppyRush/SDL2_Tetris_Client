#pragma once

#include <iostream>
#include <list>

namespace seg::tree {


template <class T>
struct nodeset;

template <class T>
struct node {

public:
	using key_type = T;
	using node_type = node<key_type>*;
	using nodeset_type = nodeset<key_type>*;

	node(key_type _key)
		:key(_key)
	{
		child->setParent(this);
	}

	inline node_type getLeft() const noexcept
	{
		return left;
	}

	inline void setLeft(node_type node)
	{
		left = node;
	}

	inline node_type getRight() const noexcept
	{
		return right;
	}

	inline void setRight(node_type node)
	{
		right = node;
	}

	inline nodeset_type getChild() const noexcept
	{
		return child;
	}

	inline void setChild(nodeset_type node)
	{
		child = node;
	}

private:

	key_type key = nullptr;
	node_type left = nullptr;
	node_type right = nullptr;
	nodeset_type child = nullptr;
};


template <class T>
struct nodeset_ : public std::list<T> {
public:

};

template <class T>
struct nodeset {
public:
	using node_type = node<T>*;
	using nodeset_type = nodeset<T>*;

	nodeset(node_type _parent)
		:parent(_parent)
	{}

	node_type getParent() const noexcept
	{
		return parent;
	}

	void setParent(node_type node)
	{
		parent = node;
	}

	node_type getHead() const noexcept
	{
		return siblings.fronst();
	}

	node_type getTail() const noexcept
	{
		return siblings.back();
	}


	void push_front(node_type node)
	{
		siblings.push_front(node);
	}

	void push_back(node_type node)
	{
		siblings.push_front(node);
	}


private:

	node_type parent = nullptr;

	std::list<node_type> siblings;
};



template <typename T>
class node_iterator_type
{
public:

	using node_type = typename node<T>::node_type;
	
	node_iterator_type(node_type node)
		: currentNode(node)
	{
		assert(node != nullptr);
	}

	bool operator!= (const node_iterator_type& other) const
	{
		return currentNode != other;
	}

	node_type& operator* ()
	{
		return currentNode;
	}

	node_iterator_type& operator++ ()
	{
		currentNode = _findNextNode(currentNode);
		return *this;
	}

	node_iterator_type& operator-- ()
	{
		return *this;
	}

private:

	node_type _findNextNode(node_type curNode)
	{
		//base condition
		if (curNode == nullptr || curNode->getRight() == nullptr)
		{
			return nullptr;
		}

		if (curNode->getChild() != nullptr)
		{
			curNode = curNode->getChild()->getHead();
			return curNode;
		}

		node_type node = curNode;
		while (node != nullptr)
		{
			node = node->getRight();
			if (node_type _node = _findNextNode(node);
				_node != nullptr)
			{
				curNode = _node;
				return _node;
			}
		}   

		return nullptr;
	}

private:

	node_type currentNode = nullptr;
};


template <typename T>
using node_iterator = node_iterator_type<T>;


template <class T>
class SEG_Tree {
public:

	using key_type = T;
	using node_type = node<T>*;
	using nodeset_type = nodeset<T>*;

	SEG_Tree() 
		:m_root(nullptr)
	{
	}

	~SEG_Tree() {
		destroy_tree();
	}

	void destroy_tree() {
		//destroy_tree(m_root);
	}

	nodeset_type getRoot() const noexcept
	{
		return m_root;
	}

	void push_node(nodeset_type nodeset, key_type key)
	{
	}

	//T* search(T* key) const noexcept
	//{
	//	search(key, root);
	//}

	void inorder_print();
	void postorder_print();
	void preorder_print();

private:

	key_type* _search(key_type* key, node_type leaf) const noexcept
	{
		for (node_type n : leaf->child)
		{
			if (key->getId() == n->key->getId()) {
				return n->key;
			}
			else
			{
				return search(key, n);
			}
		}
	}

	void destroy_tree(node_type leaf)
	{
		for (node_type node : leaf->child->nodes)
		{
			destroy_tree(node);
		}
		delete leaf;
	}


	void inorder_print(node_type leaf);
	void postorder_print(node_type leaf);
	void preorder_print(node_type leaf);


	nodeset_type m_root;
};

template <typename T>
inline node_iterator<T> begin(SEG_Tree<T>& tree)
{
	auto& root = tree.root();
	return node_iterator<T>(&root);
}

template <typename T>
inline node_iterator<T> end(SEG_Tree<T>& tree)
{
	auto& tail = tree.root();
	return node_iterator<T>(&tail);

}

}