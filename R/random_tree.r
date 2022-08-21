#' Create a random ranked phylogeny
#'
#' Create a random ranked phylogeny using the coalescent method.
#'
#' This is implementation of a ranked coalescent algorithm described in Collienne (2021).
#' Starting from `n` tips of a tree, all with rank 0, randommly select two tips and merge them
#' into a new node with rank 1, and add the new node to remaining tips. In next iteration, asign
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
