#include <stdlib.h>
#include <stdio.h>
#include "tree.h"


void set_parent(Node* node, int node_index, int n_edges, int* edges){
    for(int i = 0; i < n_edges; i++){
        if( (edges[i + n_edges] - 1) == node_index ){
            node->parent = edges[i] - 1;
            return;
        }
    }

    node->parent = -1;
}


void set_children(Node* node, int node_index, int n_edges, int* edges){
    int k = 0;
    for(int i = 0; i < n_edges; i++){
        if(edges[i] == (node_index+1)){
            node->children[k] = edges[i + n_edges]-1;
            k++;
        }

    if(k == 2)
        return;
    }

    node->children[0] = -1;
    node->children[1] = -1;
}



// allocate, but not initialize, tree structure (except tips
Tree* alloc_tree(long n_tips){
    long n_nodes = 2 * n_tips - 1;
    Tree* tree = malloc(sizeof(Tree));
    tree->tree = calloc(n_nodes, sizeof(Node));
    tree->num_leaves = n_tips;
    return(tree);
}


// deep copy of Tree structure
Tree* tree_copy(Tree* tree){
    long n = tree->num_leaves;
    Tree* new = alloc_tree(n);
    for(long i = 0; i < 2 * n - 1; i++){
        new->tree[i] = tree->tree[i]; // is that really a deep copy?
    }
    return(new);
}


/* Create a new Tree struct out of edges and ranks.
 *
 * The edge array is a two column array with tips*2-2 edges, with first column specifying parents
 * and the second column specifying children in a 1-based indices.
 *
 * Ranks is an array of length tips*2-1 with the ranks of nodes.
 * The first elements belonging to tips should have ranks 0 and are ignored.
 */
Tree* new_tree(int tips, int* edges, int* ranks){
    int n_edges = tips*2 - 2;
    int n_nodes = tips*2 - 1;

    Tree* tree = alloc_tree(tips);
    // initialize tips
    Node * node;
    for(int i = 0; i < tips; i++){
        node = &(tree->tree[i]);
        set_parent(node, i, n_edges, edges);
        node->children[0] = -1;
        node->children[1] = -1;
        node->time = 0;
    }

    // initialize internal nodes
    for(int i = tips - 1; i < n_nodes; i++){
        node = &(tree->tree[i]);
        set_parent(node, i, n_edges, edges);
        set_children(node, i, n_edges, edges);
        node->time = ranks[i];
    }
    tree->root_time = ranks[tips]; // (tips+1)th node, - 1 for 0-indexed
    return(tree);
}


// free the Tree structure and all its nodes
void free_tree(Tree* tree){
    free(tree->tree);
    free(tree);
}


// compare two trees, return 0 if trees are the same, 1 otherwise
int compare_tree(Tree* x, Tree* y){
    if(x == y) // NULL or same pointer
        return(0);

    if(x->num_leaves != y->num_leaves)
        return(1);

    if(x->root_time != y->root_time)
        return(1);

    // number of nodes is already considered the same:
    int n_nodes = x->num_leaves * 2 - 1;
    for(int i = 0; i < n_nodes; i++){
        if(compare_node(&(x->tree[i]), &(y->tree[i])))
            return(1);
    }
    return(0);
}


// compare two nodes, return 0 if nodes are identical, 1 otherwise
int compare_node(Node* x, Node* y){
    if(x == y) // NULL or same pointer
        return(0);

    if(x->parent != y->parent)
        return(1);

    if(x->time != y->time)
        return(1);

    if(x->children[0] == y->children[0] && x->children[1] == y->children[1])
        return(0);

    if(x->children[0] == y->children[1] && x->children[1] == y->children[0])
        return(0);

    return(1);
}


void print_tree(Tree* tree){
    printf("Tree: leaves - %ld, height - %ld \n", tree->num_leaves, tree->root_time);
    Node* nodes = tree->tree;
    for(int i = 0; i < 2 * tree->num_leaves - 1; i++){
        Node* node = &nodes[i];
        printf("Node %d, parent: %ld, children: (%ld, %ld), rank: %ld\n",
                i, node->parent, node->children[0], node->children[1], node->time);
    }
}
