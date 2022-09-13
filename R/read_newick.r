#' Read a newick tree
#'
#' Read a tree in a newick format and convert it to a rankedPhylo
#'
#' @param x a single character string containing tree in a newick format
#' @return object of class "rankedPhylo"
#'
#' @examples
#' read_newick("((A:1,B:1):1,C:2);")
#'
#' # Note, not all valid newick trees are valid ranked trees
#' try( read_newick("((A,B),C);") ) 
#'
#' @export
read_newick = function(x){
    if(length(x) != 1)
        stop("only one newick tree is allowed")
    tree = ape::read.tree(text=x)
    tree = as_ranked(tree)
    tree
    }
