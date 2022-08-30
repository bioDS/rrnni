#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP rnni_distance(SEXP x, SEXP y);

static const R_CallMethodDef CallEntries[] = {
    {"rnni_distance", (DL_FUNC) &rnni_distance, 2},
    {NULL, NULL, 0}
};

void R_init_rrnni(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    R_forceSymbols(dll, TRUE);
}

