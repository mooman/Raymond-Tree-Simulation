#include "main.h"
#include "queue.h"
#include "event.h"
#include "messenger.h"
#include "RaymondTree.h"
#include "simulator.h"
#include "site.h"

using namespace std;
// creates a new empty tree
RaymondTree::RaymondTree(Simulator * s, Messenger * m)
{
    this->s = s;
    this->m = m;

	root_site = NULL;
	tree_size = 0;

    postorder_q = new Queue();
}

// destroy the tree
RaymondTree::~RaymondTree()
{
	if (root_site != NULL)
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
		random_number = rand() % 50;
	//	cout << "DEBUG: node id: " << random_number << endl;
		root_site = insert_node(root_site, random_number, NULL);
	}
	// debug I/O
	print_tree(root_site);
	cout << "tree size: " << tree_size-1 << endl;
}

// do an insertion into the tree creating
// something similar to a binary tree
Site* RaymondTree::insert_node(Site* node, int data, Site* p_node){
	// if it's the first time, input site will
	// be the root site
	if (node == NULL) {
		node = new Site(this, this->s, this->m);
		node->id = data;
		node->left = NULL;
		node->right = NULL;

		if (tree_size == 0) {// root node
			tree_size += 1;
			node->parent = node; // make it it's own parent
		}

		node->parent = p_node; // point to the parent site
		tree_size++;
		return node;
	}
	// recursive insert
	if (data < node->id ) {
		node->left = insert_node(node->left, data, node);
	}
	else {
		node->right = insert_node(node->right, data, node);
	}

	return node;
}

// return the root site
Site* RaymondTree::get_root(){
	return root_site;
}

// set the root site
void RaymondTree::set_root(Site* s) {
	root_site = s;
}

// print the network
void RaymondTree::print_tree(Site* node) {

		// post order traversal
		if (node->left != NULL) {
			print_tree(node->left);
		}
		if (node->right != NULL) {
			print_tree(node->right);
		}
		cout << node->id << " ";
	return;
}

// construct a post order queue
void RaymondTree::traverse(Site* node) {

		// post order traversal
		if (node->left != NULL) {
			traverse(node->left);
		}
		if (node->right != NULL) {
			traverse(node->right);
		}

        postorder_q->enqueue(node);
	return;
}
