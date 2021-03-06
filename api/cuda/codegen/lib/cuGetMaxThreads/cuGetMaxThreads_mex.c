/*
 * codegen/lib/cuGetMaxThreads/cuGetMaxThreads_mex.c
 *
 * Auxiliary code for mexFunction of cuGetMaxThreads
 *
 * C source code generated by m2c.
 * %#m2c options:a86f06273668c7ee1c254c6a92bd888a
 *
 */

#include "mex.h"
#if !defined(MATLAB_MEX_FILE) && defined(printf)
#undef printf
#endif
/* Include the C header file generated by codegen in lib mode */
#include "cuGetMaxThreads.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void __cuGetMaxThreads_api(mxArray **plhs, const mxArray ** prhs) {
    int32_T             *nthreads;
    int32_T             *threadsPB;

    /* Marshall in inputs and preallocate outputs */
    nthreads = mxMalloc(sizeof(int32_T));

    threadsPB = mxMalloc(sizeof(int32_T));

    /* Invoke the target function */
    cuGetMaxThreads(nthreads, threadsPB);

    /* Deallocate input and marshall out function outputs */
    plhs[0] = move_scalar_to_mxArray(nthreads, mxINT32_CLASS);
    plhs[1] = move_scalar_to_mxArray(threadsPB, mxINT32_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Temporary copy for mex outputs. */
    mxArray *outputs[2];
    int i;
    int nOutputs = (nlhs < 1 ? 1 : nlhs);

    if (nrhs == 0) {
        if (nlhs > 2)
            mexErrMsgIdAndTxt("cuGetMaxThreads:TooManyOutputArguments",
                "Too many output arguments for entry-point cuGetMaxThreads.\n");
        /* Call the API function. */
        __cuGetMaxThreads_api(outputs, prhs);
    }
    else
        mexErrMsgIdAndTxt("cuGetMaxThreads:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point cuGetMaxThreads.");

    /* Copy over outputs to the caller. */
    for (i = 0; i < nOutputs; ++i) {
        plhs[i] = outputs[i];
    }
}
