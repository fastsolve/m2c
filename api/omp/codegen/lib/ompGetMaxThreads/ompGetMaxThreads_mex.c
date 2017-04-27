/*
 * omp/codegen/lib/ompGetMaxThreads/ompGetMaxThreads_mex.c
 *
 * Auxiliary code for mexFunction of ompGetMaxThreads
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
#include "ompGetMaxThreads.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void __ompGetMaxThreads_api(mxArray **plhs, const mxArray ** prhs) {
    int32_T              _n;

    /* Marshall in inputs and preallocate outputs */

    /* Invoke the target function */
    _n = ompGetMaxThreads();

    /* Deallocate input and marshall out function outputs */
    plhs[0] = copy_scalar_to_mxArray(&_n, mxINT32_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs == 0) {
        if (nlhs > 1)
            mexErrMsgIdAndTxt("ompGetMaxThreads:TooManyOutputArguments",
                "Too many output arguments for entry-point ompGetMaxThreads.\n");
        /* Call the API function. */
        __ompGetMaxThreads_api(plhs, prhs);
    }
    else
        mexErrMsgIdAndTxt("ompGetMaxThreads:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point ompGetMaxThreads.");
}
