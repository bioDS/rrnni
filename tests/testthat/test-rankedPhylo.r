test_that("random_tree produce a valid rankedPhylo object", {
    expect_silent(random_tree(3) |> rrnni:::validate_rankedPhylo())
    expect_silent(random_tree(5) |> rrnni:::validate_rankedPhylo())
    expect_silent(random_tree(8) |> rrnni:::validate_rankedPhylo())
    expect_silent(random_tree(25) |> rrnni:::validate_rankedPhylo())
    expect_silent(random_tree(64) |> rrnni:::validate_rankedPhylo())
    })


test_that("rankedPhylo dispatch for numeric", {

    tree = rankedPhylo(5)
    expect_identical(is(tree), "rankedPhylo")   
    expect_silent(tree |> rrnni:::validate_rankedPhylo())
    
    trees = rankedPhylo(3:7)
    expect_identical(is(trees), "multiRankedPhylo")
    expect_silent(invisible(sapply(trees, rrnni:::validate_rankedPhylo)))
    })
