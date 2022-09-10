#include <stdio.h>
#include "debug.h"


void print_tree(Tree* tree){
    printf("Tree: leaves - %ld, height - %ld \n", tree->num_leaves, tree->root_time);
    Node* nodes = tree->tree;
    for(int i = 0; i < 2 * tree->num_leaves - 1; i++){
        Node* node = &nodes[i];
        printf("Node %d, parent: %ld, children: (%ld, %ld), rank: %ld\n",
                i, node->parent, node->children[0], node->children[1], node->time);
    }
}
