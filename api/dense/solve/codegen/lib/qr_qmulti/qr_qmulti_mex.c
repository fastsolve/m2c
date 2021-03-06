/*
 * dense/solve/codegen/lib/qr_qmulti/qr_qmulti_mex.c
 *
 * Auxiliary code for mexFunction of qr_qmulti
 *
 * C source code generated by m2c.
 * %#m2c options:b4474f530b5a58ec01bc2875b4d6dc9d
 *
 */

#include "mex.h"
#if !defined(MATLAB_MEX_FILE) && defined(printf)
#undef printf
#endif
/* Include the C header file generated by codegen in lib mode */
#include "qr_qmulti.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void __qr_qmulti_api(mxArray **plhs, const mxArray ** prhs) {
    emxArray_real_T      A;
    emxArray_real_T      bs;
    int32_T              ncols;
    emxArray_real_T      V;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxDOUBLE_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti:WrongInputType",
            "Input argument A has incorrect data type; double is expected.");
    alias_mxArray_to_emxArray(prhs[0], (emxArray__common *)(&A), "A", 2);

    if (mxGetNumberOfElements(prhs[1]) && mxGetClassID(prhs[1]) != mxDOUBLE_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti:WrongInputType",
            "Input argument bs has incorrect data type; double is expected.");
    copy_mxArray_to_emxArray(prhs[1], (emxArray__common *)(&bs), "bs", 2);

    if (mxGetNumberOfElements(prhs[2]) && mxGetClassID(prhs[2]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti:WrongInputType",
            "Input argument ncols has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[2]) != 1)
        mexErrMsgIdAndTxt("qr_qmulti:WrongSizeOfInputArg",
            "Argument ncols should be a scalar.");
    ncols = *(int32_T*)mxGetData(prhs[2]);

    if (mxGetNumberOfElements(prhs[3]) && mxGetClassID(prhs[3]) != mxDOUBLE_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti:WrongInputType",
            "Input argument V has incorrect data type; double is expected.");
    if (mxGetNumberOfElements(prhs[3]) && mxGetDimensions(prhs[3])[1] != 1) 
        mexErrMsgIdAndTxt("qr_qmulti:WrongSizeOfInputArg",
            "Dimension 2 of V should be equal to 1.");
    alias_mxArray_to_emxArray(prhs[3], (emxArray__common *)(&V), "V", 1);

    /* Invoke the target function */
    qr_qmulti(&A, &bs, ncols, &V);

    /* Deallocate input and marshall out function outputs */
    free_emxArray((emxArray__common*)(&A));
    plhs[0] = move_emxArray_to_mxArray((emxArray__common*)(&bs), mxDOUBLE_CLASS);
    mxFree(bs.size);
    /* Nothing to be done for ncols */
    free_emxArray((emxArray__common*)(&V));

}

static void __qr_qmulti_2args_api(mxArray **plhs, const mxArray ** prhs) {
    emxArray_real_T      A;
    emxArray_real_T      bs;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxDOUBLE_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti_2args:WrongInputType",
            "Input argument A has incorrect data type; double is expected.");
    alias_mxArray_to_emxArray(prhs[0], (emxArray__common *)(&A), "A", 2);

    if (mxGetNumberOfElements(prhs[1]) && mxGetClassID(prhs[1]) != mxDOUBLE_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti_2args:WrongInputType",
            "Input argument bs has incorrect data type; double is expected.");
    copy_mxArray_to_emxArray(prhs[1], (emxArray__common *)(&bs), "bs", 2);

    /* Invoke the target function */
    qr_qmulti_2args(&A, &bs);

    /* Deallocate input and marshall out function outputs */
    free_emxArray((emxArray__common*)(&A));
    plhs[0] = move_emxArray_to_mxArray((emxArray__common*)(&bs), mxDOUBLE_CLASS);
    mxFree(bs.size);

}

static void __qr_qmulti_3args_api(mxArray **plhs, const mxArray ** prhs) {
    emxArray_real_T      A;
    emxArray_real_T      bs;
    int32_T              ncols;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxDOUBLE_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti_3args:WrongInputType",
            "Input argument A has incorrect data type; double is expected.");
    alias_mxArray_to_emxArray(prhs[0], (emxArray__common *)(&A), "A", 2);

    if (mxGetNumberOfElements(prhs[1]) && mxGetClassID(prhs[1]) != mxDOUBLE_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti_3args:WrongInputType",
            "Input argument bs has incorrect data type; double is expected.");
    copy_mxArray_to_emxArray(prhs[1], (emxArray__common *)(&bs), "bs", 2);

    if (mxGetNumberOfElements(prhs[2]) && mxGetClassID(prhs[2]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("qr_qmulti_3args:WrongInputType",
            "Input argument ncols has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[2]) != 1)
        mexErrMsgIdAndTxt("qr_qmulti_3args:WrongSizeOfInputArg",
            "Argument ncols should be a scalar.");
    ncols = *(int32_T*)mxGetData(prhs[2]);

    /* Invoke the target function */
    qr_qmulti_3args(&A, &bs, ncols);

    /* Deallocate input and marshall out function outputs */
    free_emxArray((emxArray__common*)(&A));
    plhs[0] = move_emxArray_to_mxArray((emxArray__common*)(&bs), mxDOUBLE_CLASS);
    mxFree(bs.size);
    /* Nothing to be done for ncols */

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs == 4) {
        if (nlhs > 1)
            mexErrMsgIdAndTxt("qr_qmulti:TooManyOutputArguments",
                "Too many output arguments for entry-point qr_qmulti.\n");
        /* Call the API function. */
        __qr_qmulti_api(plhs, prhs);
    }
    else if (nrhs == 2) {
        if (nlhs > 1)
            mexErrMsgIdAndTxt("qr_qmulti_2args:TooManyOutputArguments",
                "Too many output arguments for entry-point qr_qmulti_2args.\n");
        /* Call the API function. */
        __qr_qmulti_2args_api(plhs, prhs);
    }
    else if (nrhs == 3) {
        if (nlhs > 1)
            mexErrMsgIdAndTxt("qr_qmulti_3args:TooManyOutputArguments",
                "Too many output arguments for entry-point qr_qmulti_3args.\n");
        /* Call the API function. */
        __qr_qmulti_3args_api(plhs, prhs);
    }
    else
        mexErrMsgIdAndTxt("qr_qmulti:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point qr_qmulti.");
}
