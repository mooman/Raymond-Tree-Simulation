#ifndef RAYMONDTREE_H_
#define RAYMONDTREE_H_

class Site; // forward declaration
class Simulator;

class RaymondTree
{
public:
	RaymondTree(Simulator *, Messenger *);

	void build_tree(int size);
	void set_root(Site* s);
	Site* get_root();
	void print_tree(Site* node);
	void traverse(Site* node);
	Site* insert_node(Site* node, int data, Site* p_node);
	virtual ~RaymondTree();

    Queue * postorder_q;

private:
	// private variables
	Site* root_site;
    Simulator * s;
    Messenger * m;
    int tree_size;
};

#endif /*RAYMONDTREE_H_*/
