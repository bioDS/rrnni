#' Calculate RNNNI distance
#'
#' @param x a tree of class "rankedPhylo"
#' @param y a tree of class "rankedPhylo"
#' @return an integer RNNI distance between `x` and `y`
#'
#' @export
rnni = function(x, y){
    return(.Call(C_rnni_distance, x, y))
    }
