#' Create a ranked tree
#'
#' Create a new, or coerce existing, tree into a ranked tree.
#'
#' If `x` is a numeric vector, create `n = length(x)` random ranked phylogenies.
#' If `x` is a character vector, try to read the character as a newick-formatted tree.
#' If `x` is object of a class `phylo` or `multiPhylo`, coerce these objects into `rankedPhylo` or `rankedMultiPhylo`.
rankedPhylo = function(x){
    UseMethod("rankedPhylo", x)
    }


rankedPhylo.numeric = function(x){
    if(length(x) == 1)
        return(random_tree(x))

    structure(
        lapply(x, random_tree),
        class=c("multiRankedPhylo", "multiPhylo")
        )
    }


rankedPhylo.character = function(x){
    # TODO unimplemented
    stop("Unimplemented")
    }


rankedPhylo.phylo = function(x){
    # TODO unimplemented
    stop("Unimplemented")
    }


rankedPhylo.multiPhylo = function(x){
    y = lapply(x, rankedPhylo.phylo)
    structure(y, class=c("multiRankedPhylo", "multiPhylo"))
    }


#' Remove values from a vector
#'
#' Remove one or more values from a vector.
#' This is a shorthand for `x[!x %in% values]`
#'
#' @param x a vector
#' @param value a value
rmv = function(x, values){
    x[!x %in% values]
    }
