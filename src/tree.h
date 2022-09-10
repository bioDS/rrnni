// tree.h
//
// Tree structure and related functions

#ifndef TREE_H
#define TREE_H

/** Node of a Tree
 *
 * The parent and children are not connected to node through pointers,
 * but using indices of the Tree Node array. This makes the underlying
 * structure significantly simpler.
 *
 * If the Node is a root, the parent value is -1.
 * If the Node is a leaf, the children values is -1.
 * Left child is children[0], right child is children[1].
 
 * All leaves have time 0, otherwise time for all nodes should be unique.
 */
typedef struct Node {
  long parent; // index of parent Node in Tree
  long children[2]; // index of children Nodes
  long time; // rank of a node.
} Node;



/** Tree
 *
 * node.tree is an array of pointers to the Node struct.
 * These are assumed to be ordered according to their time (rank),
 * with tips/leaves first (rank0) and then other internal nodes with
 * rank 1 to root_time.
 * The tips are assumed to be ordered as well, so that for two different trees,
 * tips with the same id are considered the same taxon.
 */
typedef struct Tree {
  Node * tree; // array of nodes with size: 2 * num_leaves - 1
  long num_leaves;
  long root_time;
} Tree;


// allocate Tree structure
Tree* alloc_tree(long n_tips);

// deep copy of Tree structure
Tree* copy_tree(Tree* tree); 

// create a new tree from an edge matrix
Tree* new_tree(int tips, int* edges, int* rank);

// sort nodes in tree according to their rank
void sort_tree(Tree* tree);

// Swap two nodes in tree, changing node IDs
void swap_nodes(Tree* tree, int i, int j);

// dealocate Tree structure and all nodes.
void free_tree(Tree* tree);

// compare two trees, return 0 if trees are the same, 1 otherwise
int compare_tree(Tree* x, Tree* y);

// compare two nodes, return 0 if nodes are identical, 1 otherwise
int compare_node(Node* x, Node* y);

// set parent from edge matrix
void set_parent(Node* node, int node_index, int n_edges, int* edges);

// set children from edge matrix
void set_children(Node* node, int node_index, int n_edges, int* edges);
#endif
