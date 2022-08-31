test_that("trees are prunned correctly", {
    tree = rankedPhylo(5)
    tips = tips(tree)[1:3]
    expect_identical(keep_tips(tree, tips) |> tips(), tips)

    trees = rankedPhylo(3:7)
    n = length(trees)
    tips = tips(trees)
    expect_identical(keep_tips(trees, tips) |> tips(all=TRUE), rep(list(tips), n))
    })


test_that("class is preserved after prunning", {
    tree = rankedPhylo(5)
    tips = tips(tree)[1:3]
    expect_identical(keep_tips(tree, tips) |> class(), class(tree))

    trees = rankedPhylo(3:7)
    tips = tips(trees)
    pruned = keep_tips(trees, tips)
    expect_identical(class(pruned), class(trees))
    expect_identical(class(pruned[[1]]), class(trees[[1]]))
    })


test_that("produce a valid rankedPhylo", {
    tree = rankedPhylo(5)
    tips = tips(tree)[1:3]
    expect_silent(keep_tips(tree, tips) |> rrnni:::validate_rankedPhylo())
    })
