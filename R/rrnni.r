#' rrnni: Calculate a distance and a path in RNNI space
#'
#' RNNI stands for Ranked Nearest Neighbour Interchange and is an extension of the classical
#' NNI space (space of trees created by the NNI moves) to ranked trees, where internal nodes
#' are ordered according to their heights (usually assumed to be times).
#' Since ranked trees are variants of time trees, they keep the biologically relevant information
#' about the timing of events, such as splits.
#' Note that we assume ultrametric trees, i.e. all leaves have the same time, and unique order
#' of internal nodes, which means that two non-leaf nodes cannot have the same time.
#'
#' The RNNI distance takes the tree topology into account, as standard NNI does, but also penalizes
#' changes in the order of internal nodes, i.e. changes in the order of times of evolutionary events.
#'
#' @references
#' \cite{
#' Gavryushkin, A., Whidden, C., Matsen, IV. F. A. (2018).
#' The combinatorics of discrete time-trees: theory and open problems.
#' Journal of Mathematical Biology, 76(5):1101-1121.
#' \doi{10.1007/s00285-017-1167-9}
#' }
#'
#' \cite{
#' Collienne, L. and Gavryushkin A. (2021).
#' Computing Nearest Neighbour Interchange Distances Between Ranked Phylogenetic Trees.
#' Journal of Mathematical Biology, 82(1-2):8.
#' \doi{10.1007/s00285-021-01567-5}
#' }
#'
#' \cite{ Collienne, L. (2021). Spaces of Phylogenetic Time Trees. University of Otago. }
#'
#' @docType package
#' @name rrnni
#' @useDynLib rrnni, .registration=TRUE, .fixes="C_"
NULL
