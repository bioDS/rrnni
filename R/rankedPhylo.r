#' Create a ranked tree
#'
#' Create a new, or coerce character vector or an existing tree into a ranked tree.
#'
#' This is a wrapper for multiple functions that create a ranked tree.
#' As such, it accepts multiple types of inputs and produce either `rankedPhylo` or
#' a collated list of ranked trees as a `multiRankedPhylo`.
#'
#' If `x` is a numeric vector, create `n = length(x)` random ranked tree using the `random_tree`
#' function.
#' If `x` is a character vector, try to read the character as a newick-formatted tree.
#' If `x` is object of a class `phylo` or `multiPhylo`, coerce these objects into `rankedPhylo`
#' or `multiRankedPhylo` using the `as_ranked` function.
#'
#' @param x a numeric vector, character vector or a object of class `phylo` or `multiPhylo`, see details.
#' @return ranked tree or trees of class `rankedPhylo` or `multiRankedPhylo`
#'
#' @examples
#'
#' # Create a single random ranked tree with 5 tips
#' rankedPhylo(5)
#'
#' # Create multiple random ranked trees with 5 tips
#' rankedPhylo(c(5,5,5))
#'
#' # Convert a coalescent tree into a ranked tree
#' x = ape::rcoal(5) # random coalescent tree
#' rankedPhylo(x)
#'
#' @export
rankedPhylo = function(x){
    UseMethod("rankedPhylo", x)
    }


#' @rdname rankedPhylo
#' @export
rankedPhylo.default = function(x){
    stop("Sorry, I don't know how to make ranked phylogeny from this type of input.")
    }


#' @rdname rankedPhylo
#' @export
rankedPhylo.numeric = function(x){
    if(length(x) == 1)
        return(random_tree(x))

    structure(
        lapply(x, random_tree),
        class=c("multiRankedPhylo", "multiPhylo")
        )
    }


#' @rdname rankedPhylo
#' @export
rankedPhylo.character = function(x){
    if(length(x) == 1)
        return(read_newick(x))

    structure(
        lapply(x, read_newick),
        class=c("multiRankedPhylo", "multiPhylo")
        )
    }


#' @rdname rankedPhylo
#' @export
rankedPhylo.phylo = function(x){
    as_ranked(x)
    }


#' @rdname rankedPhylo
#' @export
rankedPhylo.multiPhylo = function(x){
    y = lapply(x, rankedPhylo.phylo)
    structure(y, class=c("multiRankedPhylo", "multiPhylo"))
    }
