// rrnni.h
//
// Binding between R and C functions

#ifndef RRNNI_H
#define RRNNI_H

#include <R.h>
#include <Rinternals.h>
#include "tree.h"



// calculate RNNI distance between two trees
SEXP rnni_distance(SEXP x, SEXP y);

// convert SEXP rankedPhylo to Tree
Tree* tree_from_phylo(SEXP phylo);

#endif
