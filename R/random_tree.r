#' Create a random ranked phylogeny
#'
#' Create a random ranked phylogeny using the coalescent method.
#'
#' This is implementation of a ranked coalescent algorithm described in Collienne (2021).
#' Starting from `n` tips of a tree, all with rank 0, randomly select two tips and merge them
#' into a new node with rank 1, and add the new node to remaining tips. In next iteration, assign
#' rank 2 and so on, until only a single node, the root, remains.
#'
#' @references
#' \cite{ Collienne, L. (2021). Spaces of Phylogenetic Time Trees (p. 158). University of Otago. }
#'
#' @param n the number of tips
#' @return random ranked tree of class "rankedPhylo"
#'
#' @examples
#' random_tree(5)
#'
#' @export
random_tree = function(n){
    n = as.integer(n[1])

    if(n < 2)
        stop("Tree must have at least 2 tips")

    tips = seq_len(n)

    tip_label = paste0("t", tips)
    edge = matrix(NA_integer_, ncol=2, nrow=(2*n-2))
    edge_length = integer(2*n-2)
    rank = integer(2*n-1)

    # naive implementation according to Collienne's Algorithm 1
    for(i in seq_len(n - 1)){
        merged = sample(tips, 2)
        new = 2L*n - i
        idx = c(i*2L-1L, i*2L)

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
            "Nnode" = n-1L,
            "edge.length" = edge_length,
            "rank" = rank
            ),
        "class" = c("rankedPhylo", "phylo")
        )
    }
