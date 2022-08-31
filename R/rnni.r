#' Calculate RNNI distance
#'
#' Calculate Ranked Nearest Neighbour Interchange (RNNI) distance.
#'
#' The RNNI distance is the shortest distance between two trees in the RNNI space, which is defined
#' by rank and NNI moves. This space is defined only for ranked trees. Non-ranked ultrametric
#' trees can be coerced to ranked trees with `as_ranked` or `rankedPhylo` functions.
#'
#' The distance can be normalized to the maximum possible distance, the diameter of the tree-space.
#' The diameter is defined as `(n-1)(n-2)/2`, where `n` is the number of tips/leaves.
#'
#' The used algorithm implements the TREEPATH algorithm described in Collienne (2021).
#'
#' @references
#' \cite{ Collienne, L. (2021). Spaces of Phylogenetic Time Trees. University of Otago. }
#'
#' @param x a tree of class "rankedPhylo"
#' @param y a tree of class "rankedPhylo"
#' @param normalize normalize the distance to the maximum distance of diameter `(n-1)(n-2)/2`
#'   where `n` is the number of tips/leaves.
#' @return an integer RNNI distance between `x` and `y`
#'
#' @export
rnni = function(x, y, normalize=FALSE){
    trees = c(x,y)
    tips = common_tips(trees)
    n = length(tips)
    trees = keep_tips(trees, tips)
    trees = sort_tips(trees)

    dist = .Call(C_rnni_distance, trees[[1]], trees[[2]])
    
    if(normalize)
        dist = dist / ( (n-1)*(n-2)/2 )

    dist
    }
