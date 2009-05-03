#ifndef RAYMONDTREE_H_
#define RAYMONDTREE_H_

class Site; // forward declaration

class RaymondTree
{
public:
	RaymondTree();
	void build_tree(int size);
	void set_root(Site* s);
	Site& get_root();
	void print_tree();
	virtual ~RaymondTree();

private:
	Site insert_node(int data);
	// private variables
	Site* root_site;
	int tree_size;

};

#endif /*RAYMONDTREE_H_*/
