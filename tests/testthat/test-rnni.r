test_that("rnni distance for the same tree", {
    tree = rankedPhylo(5)
    expect_identical(rnni(tree, tree), 0L)
    })
