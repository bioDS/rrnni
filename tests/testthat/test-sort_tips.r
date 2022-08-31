test_that("sorting tips works correctly", {
    t1 = ape::rcoal(5) |> rankedPhylo()
    t2 = ape::rcoal(5) |> rankedPhylo()
    t1s = sort_tips(t1)
    t2s = sort_tips(t2)
    expect_identical(tips(t1s), tips(t2s))

    trees = c(t1, t2)
    expect_identical(sort_tips(trees) |> tips(all=TRUE), list(tips(t1s), tips(t2s)))
    })


test_that("after sorting, valid rankedPhylo is produced", {
    tree = ape::rcoal(5) |> rankedPhylo()

    expect_silent(rrnni:::validate_rankedPhylo(tree))

    expect_silent(sort_tips(tree) |> rrnni:::validate_rankedPhylo())
    })
