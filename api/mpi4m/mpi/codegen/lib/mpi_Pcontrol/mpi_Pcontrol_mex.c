/*
 * mpi/codegen/lib/mpi_Pcontrol/mpi_Pcontrol_mex.c
 *
 * Auxiliary code for mexFunction of mpi_Pcontrol
 *
 * C source code generated by m2c.
 * %#m2c options:9f24c68e15bf2f81e606c54eee363e98
 *
 */

#include "mex.h"
#if !defined(MATLAB_MEX_FILE) && defined(printf)
#undef printf
#endif
/* Include the C header file generated by codegen in lib mode */
#include "mpi_Pcontrol.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void __mpi_Pcontrol_api(mxArray **plhs, const mxArray ** prhs) {
    int32_T              level;
    int32_T             *info;
    boolean_T           *toplevel;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Pcontrol:WrongInputType",
            "Input argument level has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("mpi_Pcontrol:WrongSizeOfInputArg",
            "Argument level should be a scalar.");
    level = *(int32_T*)mxGetData(prhs[0]);

    info = (int32_T*)mxMalloc(sizeof(int32_T));

    toplevel = (boolean_T*)mxMalloc(sizeof(boolean_T));

    /* Invoke the target function */
    mpi_Pcontrol(level, info, toplevel);

    /* Deallocate input and marshall out function outputs */
    /* Nothing to be done for level */
    plhs[0] = move_scalar_to_mxArray(info, mxINT32_CLASS);
    plhs[1] = move_scalar_to_mxArray(toplevel, mxLOGICAL_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Temporary copy for mex outputs. */
    mxArray *outputs[2] = {NULL, NULL};
    int i;
    int nOutputs = (nlhs < 1 ? 1 : nlhs);

    if (nrhs == 1) {
        if (nlhs > 2)
            mexErrMsgIdAndTxt("mpi_Pcontrol:TooManyOutputArguments",
                "Too many output arguments for entry-point mpi_Pcontrol.\n");
        /* Call the API function. */
        __mpi_Pcontrol_api(outputs, prhs);
    }
    else
        mexErrMsgIdAndTxt("mpi_Pcontrol:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point mpi_Pcontrol.");

    /* Copy over outputs to the caller. */
    for (i = 0; i < nOutputs; ++i) {
        plhs[i] = outputs[i];
    }
}
