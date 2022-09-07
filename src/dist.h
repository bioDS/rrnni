// dist.h
//
// calculate RNNI distance between two trees

#ifndef DIST_H
#define DIST_H

#include "tree.h"


// Code checking interface from: https://stackoverflow.com/a/59221452/4868692

// Error codes for distance functions
typedef enum dist_error_e {
    DIST_ERROR_OK = 0,
    // when wrong error value is thrown
    DIST_ERROR_WRONG,
    DIST_ERROR_NOTREE,
    DIST_ERROR_DIFFSIZE,
    DIST_ERROR_NOMOVE,

    // total error count
    DIST_ERROR_COUNT,
} dist_error_e;


// Error messages
static const char* const DIST_ERROR_STRS[DIST_ERROR_COUNT] = {
    "No error occured.",
    "ERROR: An error occured, but incorrect error value was specified!",
    "ERROR: Input tree doesn't exist!",
    "ERROR: Input trees are of different size!",
    "ERROR: Cannot perform RNNI move!",
};

// code to message:
const char* dist_error_str(dist_error_e code);

// all functions assume that the nodes in tree are sorted according to their rank

// get RNNI distance between two trees
long distance(Tree *start_tree, Tree *dest_tree);

// get MRCA of two nodes
long mrca(Tree * input_tree, long node1, long node2);

// NNI move on edge bounded by rank rank_in_list and rank_in_list + 1
// moving child_stays (index) of the lower node up
int nni_move(Tree * input_tree, long rank_in_list, int child_moves_up);

// Make a rank move on tree between nodes of rank and rank + 1 (if possible)
int rank_move(Tree * input_tree, long rank_in_list);

// decrease the mrca of node1 and node2 in tree by a (unique) RNNI move
// this function ignores times, only considers ranks
// output: 0 if rank move, 1 if nni move where children[0] stays, 2 if nni move where children[1] stays
int decrease_mrca(Tree* tree, long node1, long node2);

// Move up internal nodes that are at position >i in node list
// so that there are no nodes with rank less than k in the tree at the end
// (i.e. length moves that move nodes up -- see pseudocode FindPath_matrix^+)
int move_up(Tree * itree, long i, long k);
#endif
