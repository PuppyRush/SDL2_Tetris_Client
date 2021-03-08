#pragma once

#include <iostream>
#include <vector>

namespace seg::tree {

template <class T>
struct nodeset;

template <class T>
struct node {

	node(T* _key)
		:key(_key), child(new nodeset<T>{})
	{
		child->parent = this;
	}

	T* key = nullptr;
	nodeset<T>* child = nullptr;
};


template <class T>
struct nodeset {

	std::vector<node<T>*> nodes;
	node<T>* parent = nullptr;
};

template <class T>
class SEG_Tree {
public:

	SEG_Tree() {
		root = nullptr;
	}

	~SEG_Tree() {
		destroy_tree();
	}


	void destroy_tree() {
		destroy_tree(root);
	}

	void insert(T* key, node<T>* leaf) 
	{
		leaf->child->nodes.emplace_back(key);
	}


	T* search(T* key, node<T>* leaf) 
	{
		for (node<T>* n : leaf->child)
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


	void inorder_print();
	void postorder_print();
	void preorder_print();

private:


	void destroy_tree(node<T>* leaf) 
	{
		for (node<T>* node : leaf->child->nodes)
		{
			destroy_tree(node);
		}
		delete leaf;
	}


	void inorder_print(node<T>* leaf);
	void postorder_print(node<T>* leaf);
	void preorder_print(node<T>* leaf);

	node<T>* root = nullptr;
};


}