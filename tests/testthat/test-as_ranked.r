test_that("a phylo is converted to ranked tree", {
    expect_silent(ape::rcoal(5) |> as_ranked() |> rrnni:::validate_rankedPhylo())

    # a particular potentially problematic example:
    expect_silent(read_newick("(t5:4,(t2:1,t4:1):3);") |> rrnni:::validate_rankedPhylo())
    })
