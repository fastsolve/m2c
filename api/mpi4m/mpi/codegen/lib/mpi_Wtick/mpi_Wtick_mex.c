/*
 * mpi/codegen/lib/mpi_Wtick/mpi_Wtick_mex.c
 *
 * Auxiliary code for mexFunction of mpi_Wtick
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
#include "mpi_Wtick.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void __mpi_Wtick_api(mxArray **plhs, const mxArray ** prhs) {
    real64_T             _res;

    /* Marshall in inputs and preallocate outputs */

    /* Invoke the target function */
    _res = mpi_Wtick();

    /* Deallocate input and marshall out function outputs */
    plhs[0] = copy_scalar_to_mxArray(&_res, mxDOUBLE_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs == 0) {
        if (nlhs > 1)
            mexErrMsgIdAndTxt("mpi_Wtick:TooManyOutputArguments",
                "Too many output arguments for entry-point mpi_Wtick.\n");
        /* Call the API function. */
        __mpi_Wtick_api(plhs, prhs);
    }
    else
        mexErrMsgIdAndTxt("mpi_Wtick:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point mpi_Wtick.");
}
