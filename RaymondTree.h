#ifndef RAYMONDTREE_H_
#define RAYMONDTREE_H_

class Site; // forward declaration

class RaymondTree
{
public:
	RaymondTree();
	void build_tree(int size);
	void set_root(Site* s);
	Site* get_root();
	void print_tree(Site* node);
	Site* insert_node(Site* node, int data, Site* p_node);
	virtual ~RaymondTree();

private:
	// private variables
	Site* root_site;
	int tree_size;

};

#endif /*RAYMONDTREE_H_*/
