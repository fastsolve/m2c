/*
 * cuVecCreate_mex.c
 *
 * Auxiliary code for mexFunction of cuVecCreate
 *
 * C source code generated by m2c.
 * %#m2c options:07a7675b90161662d09b46288b7b734b
 *
 */

#include "mex.h"
#if !defined(MATLAB_MEX_FILE) && defined(printf)
#undef printf
#endif
/* Include the C header file generated by codegen in lib mode */
#include "cuVecCreate.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static mxArray *marshallout_struct0_T(struct0_T *pStruct) {
    const char           *fields[] = {"data", "type", "dims"};
    int                  one=1;
    mxArray              *mx = create_struct_mxArray(1, &one, 3, fields);

    mxSetField(mx, 0, "data", copy_scalar_to_mxArray(&pStruct->data, mxUINT64_CLASS));
    mxSetField(mx, 0, "type", copy_scalar_to_mxArray(&pStruct->type, mxINT32_CLASS));
    mxSetField(mx, 0, "dims", copy_scalar_to_mxArray(&pStruct->dims, mxINT32_CLASS));
    return mx;
}



static void __cuVecCreate_api(mxArray **plhs, const mxArray ** prhs) {
    int32_T              n;
    int32_T              type;
    struct0_T            vec;
    int32_T             *errCode;
    boolean_T           *toplevel;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("cuVecCreate:WrongInputType",
            "Input argument n has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("cuVecCreate:WrongSizeOfInputArg",
            "Argument n should be a scalar.");
    n = *(int32_T*)mxGetData(prhs[0]);

    if (mxGetNumberOfElements(prhs[1]) && mxGetClassID(prhs[1]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("cuVecCreate:WrongInputType",
            "Input argument type has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[1]) != 1)
        mexErrMsgIdAndTxt("cuVecCreate:WrongSizeOfInputArg",
            "Argument type should be a scalar.");
    type = *(int32_T*)mxGetData(prhs[1]);

    errCode = mxMalloc(sizeof(int32_T));

    toplevel = mxMalloc(sizeof(boolean_T));

    /* Invoke the target function */
    cuVecCreate(n, type, &vec, errCode, toplevel);

    /* Deallocate input and marshall out function outputs */
    /* Nothing to be done for n */
    /* Nothing to be done for type */
    plhs[0] = marshallout_struct0_T(&vec);
    plhs[1] = move_scalar_to_mxArray(errCode, mxINT32_CLASS);
    plhs[2] = move_scalar_to_mxArray(toplevel, mxLOGICAL_CLASS);

}

static void __cuVecCreate_1arg_api(mxArray **plhs, const mxArray ** prhs) {
    int32_T              n;
    struct0_T            vec;
    int32_T             *errCode;
    boolean_T           *toplevel;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("cuVecCreate_1arg:WrongInputType",
            "Input argument n has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("cuVecCreate_1arg:WrongSizeOfInputArg",
            "Argument n should be a scalar.");
    n = *(int32_T*)mxGetData(prhs[0]);

    errCode = mxMalloc(sizeof(int32_T));

    toplevel = mxMalloc(sizeof(boolean_T));

    /* Invoke the target function */
    cuVecCreate_1arg(n, &vec, errCode, toplevel);

    /* Deallocate input and marshall out function outputs */
    /* Nothing to be done for n */
    plhs[0] = marshallout_struct0_T(&vec);
    plhs[1] = move_scalar_to_mxArray(errCode, mxINT32_CLASS);
    plhs[2] = move_scalar_to_mxArray(toplevel, mxLOGICAL_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Temporary copy for mex outputs. */
    mxArray *outputs[3];
    int i;
    int nOutputs = (nlhs < 1 ? 1 : nlhs);

    if (nrhs == 2) {
        if (nlhs > 3)
            mexErrMsgIdAndTxt("cuVecCreate:TooManyOutputArguments",
                "Too many output arguments for entry-point cuVecCreate.\n");
        /* Call the API function. */
        __cuVecCreate_api(outputs, prhs);
    }
    else if (nrhs == 1) {
        if (nlhs > 3)
            mexErrMsgIdAndTxt("cuVecCreate_1arg:TooManyOutputArguments",
                "Too many output arguments for entry-point cuVecCreate_1arg.\n");
        /* Call the API function. */
        __cuVecCreate_1arg_api(outputs, prhs);
    }
    else
        mexErrMsgIdAndTxt("cuVecCreate:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point cuVecCreate.");

    /* Copy over outputs to the caller. */
    for (i = 0; i < nOutputs; ++i) {
        plhs[i] = outputs[i];
    }
}
