#' Sort tip labels
#'
#' Sort tip labels in a tree or a collection of trees.
#'
#' The `rnni` function assumes tip labels in an unambiguous order.
#' This is due to the internal implementation not having tip labels,
#' tip/leave are instead identified by the index in the node matrix.
#' The `sort_tips` orders the tip labels and change the node indices
#' in the node matrix so that the tips for two different trees of the
#' same taxa have the same node id.
#'
#' @param x a tree of class "phylo" or a collection of trees of class "multiPhylo"
#' @return an input tree with sorted tips
#'
#' @examples
#' # generate random trees
#' # use rcoal(5) instead of rankedPhylo(5)
#' # as ranked phylo always generate tip.labels
#' # in the same order.
#' t1 = ape::rcoal(5) |> rankedPhylo()
#' t2 = ape::rcoal(5) |> rankedPhylo()
#' t1s = sort_tips(t1)
#' t2s = sort_tips(t2)
#' all(tips(t1s) == tips(t2s))
#'
#' # for collection of trees:
#' trees = c(t1, t2)
#' sort_tips(trees)
#'
#' @export
sort_tips = function(x){
    UseMethod("sort_tips", x)
    }


#' @rdname sort_tips
#' @export
sort_tips.phylo = function(x){
    sorted = tips(x) |> sort()    
    nodes = seq_len(x$Nnode) + x$Nnode + 1 |> as.integer()
    order = match(tips(x), sorted)
    norder = c(order, nodes)

    x$tip.label = sorted
    x$edge[,2] = norder[x$edge[,2]]
    x
    }


#' @rdname sort_tips
#' @export
sort_tips.multiPhylo = function(x){
    x[] = lapply(x, sort_tips.phylo)
    x
    }
