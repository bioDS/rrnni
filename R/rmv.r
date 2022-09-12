#' Remove values from a vector
#'
#' Remove one or more values from a vector.
#' This is a shorthand for `x[!x %in% values]`
#'
#' @param x a vector
#' @param values vector of values
#' @return x without values
#'
#' @keywords internal
#
# @examples
# x = c(1:4)
# y = rrnni:::rmv(x, c(1,3))
# y # 2, 4
#
rmv = function(x, values){
    x[!x %in% values]
    }
