# Unit tests for C code

To make the code cleaner, and the development more comfortable, instead of testing only the exposed R code, we will unittest the C code as well.

We use the header-only [minunit](https://github.com/siu/minunit) framework.

We also achieve a higher modularity by separating the pure C code and the R binding.
This allows us to test the C code directly without having to include R headers `R.h` and `Rinternals.h`. 

C-unit tests are not included with the packaged code.

## Instructions
