#' Calculate RNNNI distance
#'
#' @param x a tree of class "rankedPhylo"
#' @param y a tree of class "rankedPhylo"
#' @return an integer RNNI distance between `x` and `y`
#'
#' @export
rnni = function(x, y, normalize=FALSE, verbose=FALSE){
    trees = c(x,y)
    tips = common_tips(trees)
    trees = keep_tips(trees, tips)
    trees = sort_tips(trees)

    return(.Call(C_rnni_distance, trees[[1]], trees[[2]]))
    }
