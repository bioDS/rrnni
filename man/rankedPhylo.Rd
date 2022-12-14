% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/rankedPhylo.r
\name{rankedPhylo}
\alias{rankedPhylo}
\alias{rankedPhylo.default}
\alias{rankedPhylo.numeric}
\alias{rankedPhylo.character}
\alias{rankedPhylo.phylo}
\alias{rankedPhylo.multiPhylo}
\title{Create a ranked tree}
\usage{
rankedPhylo(x)

\method{rankedPhylo}{default}(x)

\method{rankedPhylo}{numeric}(x)

\method{rankedPhylo}{character}(x)

\method{rankedPhylo}{phylo}(x)

\method{rankedPhylo}{multiPhylo}(x)
}
\arguments{
\item{x}{a numeric vector, character vector or a object of class \code{phylo} or \code{multiPhylo}, see details.}
}
\value{
ranked tree or trees of class \code{rankedPhylo} or \code{multiRankedPhylo}
}
\description{
Create a new, or coerce character vector or an existing tree into a ranked tree.
}
\details{
This is a wrapper for multiple functions that create a ranked tree.
As such, it accepts multiple types of inputs and produce either \code{rankedPhylo} or
a collated list of ranked trees as a \code{multiRankedPhylo}.

If \code{x} is a numeric vector, create \code{n = length(x)} random ranked tree using the \code{random_tree}
function.
If \code{x} is a character vector, try to read the character as a newick-formatted tree.
If \code{x} is object of a class \code{phylo} or \code{multiPhylo}, coerce these objects into \code{rankedPhylo}
or \code{multiRankedPhylo} using the \code{as_ranked} function.
}
\examples{

# Create a single random ranked tree with 5 tips
rankedPhylo(5)

# Create multiple random ranked trees with 5 tips
rankedPhylo(c(5,5,5))

# Convert a coalescent tree into a ranked tree
x = ape::rcoal(5) # random coalescent tree
rankedPhylo(x)

}
