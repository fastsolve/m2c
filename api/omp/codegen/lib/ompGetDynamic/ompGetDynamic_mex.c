/*
 * omp/codegen/lib/ompGetDynamic/ompGetDynamic_mex.c
 *
 * Auxiliary code for mexFunction of ompGetDynamic
 *
 * C source code generated by m2c.
 * %#m2c options:c92b43727942398fd1cb3a62677cc8c1
 *
 */

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "matrix.h"
#endif
/* Include the C header file generated by codegen in lib mode */
#include "ompGetDynamic.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void __ompGetDynamic_api(mxArray **plhs, const mxArray ** prhs) {
    int32_T              _n;

    /* Marshall in inputs and preallocate outputs */

    /* Invoke the target function */
    _n = ompGetDynamic();

    /* Deallocate input and marshall out function outputs */
    plhs[0] = copy_scalar_to_mxArray(&_n, mxINT32_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs == 0) {
        if (nlhs > 1)
            mexErrMsgIdAndTxt("ompGetDynamic:TooManyOutputArguments",
                "Too many output arguments for entry-point ompGetDynamic.\n");
        /* Call the API function. */
        __ompGetDynamic_api(plhs, prhs);
    }
    else
        mexErrMsgIdAndTxt("ompGetDynamic:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point ompGetDynamic.");
}
