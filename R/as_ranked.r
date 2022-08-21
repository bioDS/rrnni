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
    rank[-seq_len(ntip)] = order(rank[-seq_len(ntip)])
    x$edge.length = rank[x$edge[,1]] - rank[x$edge[,2]]
    x$rank = rank
    
    structure(x, class = c("rankedPhylo", "phylo"))
    }
