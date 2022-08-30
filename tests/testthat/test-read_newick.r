test_that("convert newick string into a valid rankedPhylo object", {
    expect_silent(read_newick("((A:1,B:1):1,C:2);") |> rrnni:::validate_rankedPhylo())
    expect_silent(read_newick("((((A:1,B:1):1,C:2):1,D:3):1,E:4);") |>
        rrnni:::validate_rankedPhylo())
    expect_silent(read_newick("(((A:1,D:1):2,(C:2,E:2):1):1,B:4);") |>
        rrnni:::validate_rankedPhylo())
    })


test_that("fails for non-valid ranked strings", {
    expect_error(read_newick("((A, B), C);"))
    expect_error(read_newick("((A:1,B:1):1,C:1);"))
    })
