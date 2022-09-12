#' Validate rankedPhylo class
#'
#' Validate that the object is a rankedPhylo object with a proper structure and type.
#'
#' This is internal function used for testing purposes.
#'
#' "rankedPhylo" is a subclass of "phylo" object with several restrictions given by the structure
#' of the represented ranked tree.
#' `validate_rankedPhylo` checks these restrictions and throw a particular error, if the object
#' fails any of these restrictions.
#'
#' @param x an object of class "rankedPhylo"
#' @return This function doesn't have a return value.
#'
#' @keywords internal
#
# @examples
# tree = rankedPhylo(5)
# rrnni:::validate_rankedPhylo(tree)
#
validate_rankedPhylo = function(x){
    if(methods::is(x) != "rankedPhylo")
        stop("x must be of class \"rankedPhylo\"")

    if(!inherits(x, "phylo"))
        stop("x must inherit from \"phylo\"")

    if(!identical(names(x), c("edge", "tip.label", "Nnode", "edge.length", "rank")))
        stop("x's names do not correspond to names of \"rankedPhylo\" object")

    if(!identical(sapply(x, typeof) |> unname(),
                  c("integer", "character", "integer", "integer", "integer"))
        )
        stop("x's types do not correspond to types of \"rankedPhylo\" object")

    if(!ape::is.rooted(x))
        stop("x must be rooted")

    if(!identical(c(rep.int(0L, ape::Ntip(x)), seq_len(x$Nnode)), sort(x$rank)))
        stop("x's ranks are malformed")

    if((ape::Ntip(x) + 1) %in% x$edge[,2])
        stop("Node ", ape::Ntip(x) + 1, " is not the root node.")

    if(!identical(dim(x$edge), c(ape::Ntip(x)*2L - 2L, 2L)))
        stop("x's edge matrix does not have correct dimension.")

    if(any(ape::node.depth.edgelength(x) < 0))
        stop("x's edge.length is malformed.")

    invisible(NULL)
    }

