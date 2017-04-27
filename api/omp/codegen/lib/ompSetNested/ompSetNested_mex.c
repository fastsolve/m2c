/*
 * omp/codegen/lib/ompSetNested/ompSetNested_mex.c
 *
 * Auxiliary code for mexFunction of ompSetNested
 *
 * C source code generated by m2c.
 * %#m2c options:f0c8daf676ad9872b69ad961a41f2cd1
 *
 */

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "matrix.h"
#endif
/* Include the C header file generated by codegen in lib mode */
#include "ompSetNested.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void __ompSetNested_api(mxArray **plhs, const mxArray ** prhs) {
    int32_T              nested;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("ompSetNested:WrongInputType",
            "Input argument nested has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("ompSetNested:WrongSizeOfInputArg",
            "Argument nested should be a scalar.");
    nested = *(int32_T*)mxGetData(prhs[0]);

    /* Invoke the target function */
    ompSetNested(nested);

    /* Deallocate input and marshall out function outputs */
    /* Nothing to be done for nested */

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs == 1) {
        if (nlhs > 0)
            mexErrMsgIdAndTxt("ompSetNested:TooManyOutputArguments",
                "Too many output arguments for entry-point ompSetNested.\n");
        /* Call the API function. */
        __ompSetNested_api(plhs, prhs);
    }
    else
        mexErrMsgIdAndTxt("ompSetNested:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point ompSetNested.");
}
