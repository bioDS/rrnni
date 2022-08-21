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
random_tree = function(n){
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
