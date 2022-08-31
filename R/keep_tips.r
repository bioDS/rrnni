#' Prune a tree
#'
#' Prune a tree or a collection of trees and keep only requested tips.
#'
#' @param x a tree of class "phylo" or "multiPhylo"
#' @param tips tip labels to keep
#' @return a pruned tree or a collection
#'
#' @examples
#' tree = rankedPhylo(5)
#' # select randomly 3 tips to keep
#' tips = sample(tips(tree), 3)
#' keep_tips(tree, tips)
#'
#' trees = rankedPhylo(3:7)
#' # get tips from the first tree
#' tips = tips(trees[[1]])
#' # prune all trees, all of them will have 3 tips
#' keep_tips(trees, tips)
#'
#' @export
keep_tips = function(x, tips){
    UseMethod("keep_tips", x)
    }


#' @rdname keep_tips
#' @export
keep_tips.phylo = function(x, tips){
    ape::keep.tip(x, tips)
    }


#' @rdname keep_tips
#' @export
keep_tips.multiPhylo = function(x, tips){
    # this will preserve attributes, such as the class
    x[] = lapply(x, keep_tips, tips)
    x
    }


#' @rdname keep_tips
#' @export
keep_tips.rankedPhylo = function(x, tips){
    # The best way to guarantee valid ranked tree after prunning
    # is to treat it as phylo and coerce to rankedPhylo again
    x = ape::keep.tip(x, tips)
    x$rank = NULL
    class(x) = "phylo"
    as_ranked(x)
    }
