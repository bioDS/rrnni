#include <R.h>
#include <Rinternals.h>

SEXP hello(){
    Rprintf("Hello World");

    return(R_NilValue);
    }
