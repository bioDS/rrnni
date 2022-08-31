#' Convert a tree to ranked tree
#'
#' Convert a tree of class "phylo" to a ranked tree of class "rankedPhylo".
#'
#' To convert a tree to a ranked tree, the tree needs to be binary (i.e., fully resolved),
#' be rooted, and ultrametric. Typically, such tree would be produced by coalescent process.
#'
#' Ranked trees are similar to time-trees, only instead of time, we care about the order
#' of the splits.
#'
#' @param x a tree of class "phylo"
#' @return a ranked tree of class "rankedPhylo"
#'
#' @examples
#'
#' # this will throw an error, the tree is not ultrametric
#' x = ape::rtree(5)
#' try(as_ranked(x))
#'
#' # coalescent trees can be converted without problem
#' y = ape::rcoal(5)
#' as_ranked(y)
#'
#' @export
as_ranked = function(x){
    if(!inherits(x, "phylo"))
        stop("Input tree must be of class \"phylo\"")
    if(!ape::is.ultrametric(x))
        stop("Input tree must be ultrametric.")
    if(!ape::is.binary(x))
        stop("Input tree must be binary.")
    if(!ape::is.rooted(x))
        stop("Input tree must be rooted.")

    if(inherits(x, "rankedPhylo"))
        return(x)

    ntip = length(x$tip.label)
    rank = ape::node.depth.edgelength(x)
    rank = max(rank) - rank
    rank[-c(seq_len(ntip))] = reseq(rank[-c(seq_len(ntip))])
    rank = as.integer(rank)

    if(any(rank[1:ntip] != 0))
        stop("First ", ntip, " elements should be tips.")

    x$edge.length = rank[x$edge[,1]] - rank[x$edge[,2]]
    x$rank = rank

    # enforce order of elements
    x = x[c("edge", "tip.label", "Nnode", "edge.length", "rank")]

    structure(x, class = c("rankedPhylo", "phylo"))
    }


reseq = function(x){
    match(x, sort(x))
    }
