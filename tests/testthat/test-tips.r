test_that("tips get tip labels", {
    tree = rankedPhylo(5)
    expect_identical(tips(tree), tree$tip.label)
    
    trees = rankedPhylo(3:7)
    expect_identical(tips(trees),trees[[1]]$tip.label)
    
    expect_identical(
        tips(trees, all=TRUE),
        lapply(trees, getElement, "tip.label")
        )
    })
