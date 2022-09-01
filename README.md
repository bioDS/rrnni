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

## What is RNNI space?
### Some useful properties of RNNI space

