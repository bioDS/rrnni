#' Find shared tip labels
#'
#' Find shared tip labels of a collection of trees.
#' This function is useful when pruning a collection
#' of related trees to a trees of same size and taxa.
#'
#' @param x a collection of trees of class "multiPhylo"
#' @return intersection of tip labels across all trees
#'
#' @examples
#' trees = rankedPhylo(3:7)
#' common_tips(trees)
#'
#' @export
common_tips = function(x){
    tips = tips(x, all = TRUE)
    tips = Reduce(intersect, tips)
    tips
    }
