#' Create a random ranked phylogeny
#'
#' Create a random ranked phylogeny using the coalescent method.
#'
#' Starting from `n` tips of a tree with rank 0, randomly select two tips and
#' coalesce them, and assign rank 1, in next iteration rank 2 and so on, until
#' only a single node, the root, remains.
#'
#' @param n the number of tips
#' @return object of class `rankedPhylo`
new_rankedPhylo = function(n){
    n = as.integer(n[1])
    tips = 1:n

    tip_label = paste0("t", 1:n)
    edge = matrix(NA, ncol=2, nrow=(2*n-2))
    edge_length = numeric(2*n-2)
    rank = numeric(2*n-1)

    # naive implementation according to Collienne's Algorithm 1
    for(i in seq_len(n - 1)){
        merged = sample(tips, 2)
        new = 2*n - i
        idx = c(i*2-1, i*2)

        edge[idx, 1] = new
        edge[idx, 2] = merged

        tips = rmv(tips, merged)
        tips = c(tips, new)
        rank[new] = i
        edge_length[idx] = i - rank[merged]
        }

    structure(
        list(
            "edge" = edge,
            "tip.label" = tip_label,
            "Nnode" = n-1,
            "edge.length" = edge_length,
            "rank" = rank
            ),
        "class" = c("rankedPhylo", "phylo")
        )
    }


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
        return(new_rankedPhylo(x))

    structure(
        lapply(x, new_rankedPhylo),
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
