test_that("rnni distance for the same tree", {
    tree = rankedPhylo(5)
    expect_identical(rnni(tree, tree), 0L)
    })


test_that("rnni distance for different trees", {
    x = read_newick("((((A:1,B:1):1,C:2):1,D:3):1,E:4);")
    y = read_newick("(((A:1,D:1):2,(C:2,E:2):1):1,B:4);")
    expect_identical(rnni(x, y), 5L)
    })
