#include "rrnni.h"
#include "tree.h"
#include "dist.h"

SEXP hello_tree(SEXP phylo){
    PROTECT(phylo);
    Tree* tree = tree_from_phylo(phylo);
    print_tree(tree);
    free(tree);
    UNPROTECT(1);

    return(R_NilValue);
    }


Tree* tree_from_phylo(SEXP phylo){
    // derive edges, n and rank from phylo
    int* edges = INTEGER(VECTOR_ELT(phylo, 0));
    int n_tips = length(VECTOR_ELT(phylo, 1));
    int* ranks = INTEGER(VECTOR_ELT(phylo, 4));

    Tree* tree = new_tree(n_tips, edges, ranks);

    return(tree);
}


SEXP rnni_distance(SEXP x, SEXP y){
    PROTECT(x);
    PROTECT(y);
    Tree* xtree = tree_from_phylo(x);
    Tree* ytree = tree_from_phylo(y);
    sort_tree(xtree);
    sort_tree(ytree);

    long dist = distance(xtree, ytree);
    free_tree(xtree);
    free_tree(ytree);

    UNPROTECT(2);

    return(ScalarInteger(dist));
}
