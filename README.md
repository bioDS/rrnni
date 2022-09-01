# rrnni
## Manipulate with RNNI tree space

The **rrnni** package contains a collection of functions to create, convert and
manipulate ranked trees. The `rrnni::rnni` function then calculates
RNNI distance between two trees in the RNNI space.

## Install

**rrnni** is not currently on CRAN.

You can install the latest version of **rrnni** from github:

```{r}
devtools::install_github("biods/rrnni")
```

## Usage

Create a new random ranked tree with 5 tips:

```{r}
library("rrnni")
tree = rankedPhylo(5)
```

Convert an ultrametric tree, such as from `ape::rcoal`, to ranked tree:

```{r}
tree = ape::rcoal(5)
tree = rankedPhylo(tree)
```

Calculate RNNI distance between two ranked trees:

```{r}
x = rankedPhylo(5)
y = rankedPhylo(5)
rnni(x, y)
```

## What is RNNI?

RNNI stands for Ranked Nearest Neighbour Interchange and is an extension of the classical NNI to ranked trees, where internal nodes are ordered according to their heights (which we usually assume to be times).
Note that we assume ultrametric trees, i.e. all leaves have the same time, and a unique order of internal nodes, which means that two non-leaf nodes cannot have the same time.
The RNNI distance takes the tree topology into account, like standard NNI does, but also penalises changes in the order of internal nodes, i.e. changes in the order of times of evolutionary events.

### More details on the RNNI space

In the RNNI space, we allow two tree rearrangement moves (RNNI moves):
An NNI move can be performed on any edge connecting nodes of consecutive rank and swaps to neighbouring subtrees (just like standard NNI);
A rank move swaps the order of two internal nodes of consecutive ranks.
The distance between two ranked trees in RNNI is then defined as the minimum number of RNNI moves needed to convert one tree into the other.
This distance can be computed in polynomial time, using the FindPath algorithm described by [Collienne and Gavryushkin (2021)](https://link.springer.com/article/10.1007/s00285-021-01567-5).