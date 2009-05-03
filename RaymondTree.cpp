#include "RaymondTree.h"
#include "site.h"
#include <cstdlib>
#include <ctime>

// creates a new empty tree
RaymondTree::RaymondTree()
{
	root_site = null;
	tree_size = 0;
}

// destroy the tree
RaymondTree::~RaymondTree()
{
	if (root_site != null)
		delete(root_site);
}

// build a tree of given size
void RaymondTree::build_tree(int size){

	int random_number = 0;
	// ensure the size of the network entered by user is valid
	if (size <= 0) {
		cout << "The size of the network has to be 1 or greater" << endl;
		return;
	}

	// generate random IDs for each site based on a seed provided by
	// the system time
	for (int i = 0; i < size; i++) {
		srand((unsigned)time(0));
		random_number = rand();
		insert_node(root_site, random_number);
	}
}

// do an insertion into the tree creating
// something similar to a binary tree
Site RaymondTree::insert_node(Site* node, int data){
	// if it's the first time, input site will
	// be the root site
	if (node == null) {
		node = new Site();
		node->set_id(data);
		node->left = null;
		node->right = null;
		return s;
	}

	// otherwise insert the node in the tree
	// according to the value of the ID
	if (data == node->id)
		data++;

	if (data < node->id ) {
		node->left = insert_node(dnode->left, data);
	}
	else {
		node->right = insert_node(node->right, data);
	}

	return s;
}

// return the root site
Site& RaymondTree::get_root(){
	return root_site;
}

// set the root site
void RaymondTree::set_root(Site* s) {
	root_site = s;
}

// print the network
void RaymondTree::print_tree() {

}
