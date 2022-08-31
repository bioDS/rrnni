#' Extract tips from tree
#'
#' Extract tip labels from the object of class "phylo" or "multiPhylo"
#'
#' This is convenience method, it's purpose is to easily retrieve tip labels of a tree or
#' a collection of trees with the same tip labels. Due to this, when called on a collection of
#' trees (an object of class "multiPhylo"), only the first tree of a collection is accessed.
#' To obtain tip labels from all trees, specify the argument `all=TRUE`.
#'
#' @param x an object of class "phylo" or "multiPhylo"
#' @param all **optional** extract tips for all trees, only if `x` is "multiPhylo"
#' @param ... arguments to be passed to methods
#' @return a vector of tip labels, or list of vectors in case of "multiPhylo" with `all=TRUE`
#'
#' @examples
#' tree = rankedPhylo(5)
#' tips(tree)
#'
#' trees = rankedPhylo(3:7)
#' # only the first tree is accessed
#' tips(trees)
#'
#' # use this to obtain all tip labels
#' tips(trees, all=TRUE)
#'
#' @export
tips = function(x, ...){
    UseMethod("tips", x)
    }


#' @rdname tips
#' @export
tips.phylo = function(x, ...){
    x$tip.label
    }


#' @rdname tips
#' @export
tips.multiPhylo = function(x, all=FALSE, ...){
    if(!all)
        return(x[[1]] |> tips())

    lapply(x, tips)
    }
