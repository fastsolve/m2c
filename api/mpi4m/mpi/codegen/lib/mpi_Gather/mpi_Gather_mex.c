/*
 * mpi/codegen/lib/mpi_Gather/mpi_Gather_mex.c
 *
 * Auxiliary code for mexFunction of mpi_Gather
 *
 * C source code generated by m2c.
 * %#m2c options:630f83623fc480deabaee8131dea1889
 *
 */

#include "mex.h"
#if !defined(MATLAB_MEX_FILE) && defined(printf)
#undef printf
#endif
/* Include the C header file generated by codegen in lib mode */
#include "mpi_Gather.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void marshallin_const_struct0_T(struct0_T *pStruct, const mxArray *mx, const char *mname) {
    mxArray             *sub_mx;

    if (!mxIsStruct(mx))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s has incorrect data type; struct is expected.", mname);
    if (!mxGetField(mx, 0, "data"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field data.", mname);
    if (!mxGetField(mx, 0, "type"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field type.", mname);
    if (!mxGetField(mx, 0, "nbytes"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field nbytes.", mname);
    if (!mxGetField(mx, 0, "offset"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field offset.", mname);
    if (mxGetNumberOfFields(mx) > 4)
        M2C_warn("marshallin_const_struct0_T:ExtraFields",
            "Extra fields in %s and are ignored.", mname);

    sub_mx = mxGetField(mx, 0, "data");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT64_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument data has incorrect data type; uint64 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument data should be a scalar.");
    pStruct->data = *(uint64_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "type");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxCHAR_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument type has incorrect data type; char is expected.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[0] != 1) 
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Dimension 1 of type should be equal to 1.");
    pStruct->type = (emxArray_char_T*)mxMalloc(sizeof(emxArray_char_T));
    init_emxArray((emxArray__common*)(pStruct->type), 2);
    alias_mxArray_to_emxArray(sub_mx, (emxArray__common *)(pStruct->type), "type", 2);

    sub_mx = mxGetField(mx, 0, "nbytes");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument nbytes has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument nbytes should be a scalar.");
    pStruct->nbytes = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "offset");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument offset has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument offset should be a scalar.");
    pStruct->offset = *(int32_T*)mxGetData(sub_mx);
}
static void destroy_struct0_T(struct0_T *pStruct) {

    free_emxArray((emxArray__common*)(pStruct->type));
    mxFree(pStruct->type);


}


static void marshallin_const_struct1_T(struct1_T *pStruct, const mxArray *mx, const char *mname) {
    mxArray             *sub_mx;

    if (!mxIsStruct(mx))
        M2C_error("marshallin_const_struct1_T:WrongType",
            "Input argument %s has incorrect data type; struct is expected.", mname);
    if (!mxGetField(mx, 0, "data"))
        M2C_error("marshallin_const_struct1_T:WrongType",
            "Input argument %s is missing the field data.", mname);
    if (!mxGetField(mx, 0, "type"))
        M2C_error("marshallin_const_struct1_T:WrongType",
            "Input argument %s is missing the field type.", mname);
    if (!mxGetField(mx, 0, "nitems"))
        M2C_error("marshallin_const_struct1_T:WrongType",
            "Input argument %s is missing the field nitems.", mname);
    if (mxGetNumberOfFields(mx) > 3)
        M2C_warn("marshallin_const_struct1_T:ExtraFields",
            "Extra fields in %s and are ignored.", mname);

    sub_mx = mxGetField(mx, 0, "data");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT8_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct1_T:WrongInputType",
            "Input argument data has incorrect data type; uint8 is expected.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[1] != 1) 
        mexErrMsgIdAndTxt("marshallin_const_struct1_T:WrongSizeOfInputArg",
            "Dimension 2 of data should be equal to 1.");
    pStruct->data = (emxArray_uint8_T*)mxMalloc(sizeof(emxArray_uint8_T));
    init_emxArray((emxArray__common*)(pStruct->data), 1);
    alias_mxArray_to_emxArray(sub_mx, (emxArray__common *)(pStruct->data), "data", 1);

    sub_mx = mxGetField(mx, 0, "type");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxCHAR_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct1_T:WrongInputType",
            "Input argument type has incorrect data type; char is expected.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[0] != 1) 
        mexErrMsgIdAndTxt("marshallin_const_struct1_T:WrongSizeOfInputArg",
            "Dimension 1 of type should be equal to 1.");
    pStruct->type = (emxArray_char_T*)mxMalloc(sizeof(emxArray_char_T));
    init_emxArray((emxArray__common*)(pStruct->type), 2);
    alias_mxArray_to_emxArray(sub_mx, (emxArray__common *)(pStruct->type), "type", 2);

    sub_mx = mxGetField(mx, 0, "nitems");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct1_T:WrongInputType",
            "Input argument nitems has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct1_T:WrongSizeOfInputArg",
            "Argument nitems should be a scalar.");
    pStruct->nitems = *(int32_T*)mxGetData(sub_mx);
}
static void destroy_struct1_T(struct1_T *pStruct) {

    free_emxArray((emxArray__common*)(pStruct->data));
    mxFree(pStruct->data);

    free_emxArray((emxArray__common*)(pStruct->type));
    mxFree(pStruct->type);


}


static void __mpi_Gather_api(mxArray **plhs, const mxArray ** prhs) {
    struct0_T            sptr;
    int32_T              scount;
    struct1_T            stype;
    struct0_T            rptr;
    int32_T              rcount;
    struct1_T            rtype;
    int32_T              root;
    struct1_T            comm;
    int32_T             *info;
    boolean_T           *toplevel;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Gather:WrongInputType",
            "Input argument sptr has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("mpi_Gather:WrongSizeOfInputArg",
            "Argument sptr should be a scalar.");
    marshallin_const_struct0_T(&sptr, prhs[0], "sptr");

    if (mxGetNumberOfElements(prhs[1]) && mxGetClassID(prhs[1]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Gather:WrongInputType",
            "Input argument scount has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[1]) != 1)
        mexErrMsgIdAndTxt("mpi_Gather:WrongSizeOfInputArg",
            "Argument scount should be a scalar.");
    scount = *(int32_T*)mxGetData(prhs[1]);

    if (mxGetNumberOfElements(prhs[2]) && mxGetClassID(prhs[2]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Gather:WrongInputType",
            "Input argument stype has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[2]) != 1)
        mexErrMsgIdAndTxt("mpi_Gather:WrongSizeOfInputArg",
            "Argument stype should be a scalar.");
    marshallin_const_struct1_T(&stype, prhs[2], "stype");

    if (mxGetNumberOfElements(prhs[3]) && mxGetClassID(prhs[3]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Gather:WrongInputType",
            "Input argument rptr has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[3]) != 1)
        mexErrMsgIdAndTxt("mpi_Gather:WrongSizeOfInputArg",
            "Argument rptr should be a scalar.");
    marshallin_const_struct0_T(&rptr, prhs[3], "rptr");

    if (mxGetNumberOfElements(prhs[4]) && mxGetClassID(prhs[4]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Gather:WrongInputType",
            "Input argument rcount has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[4]) != 1)
        mexErrMsgIdAndTxt("mpi_Gather:WrongSizeOfInputArg",
            "Argument rcount should be a scalar.");
    rcount = *(int32_T*)mxGetData(prhs[4]);

    if (mxGetNumberOfElements(prhs[5]) && mxGetClassID(prhs[5]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Gather:WrongInputType",
            "Input argument rtype has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[5]) != 1)
        mexErrMsgIdAndTxt("mpi_Gather:WrongSizeOfInputArg",
            "Argument rtype should be a scalar.");
    marshallin_const_struct1_T(&rtype, prhs[5], "rtype");

    if (mxGetNumberOfElements(prhs[6]) && mxGetClassID(prhs[6]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Gather:WrongInputType",
            "Input argument root has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[6]) != 1)
        mexErrMsgIdAndTxt("mpi_Gather:WrongSizeOfInputArg",
            "Argument root should be a scalar.");
    root = *(int32_T*)mxGetData(prhs[6]);

    if (mxGetNumberOfElements(prhs[7]) && mxGetClassID(prhs[7]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Gather:WrongInputType",
            "Input argument comm has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[7]) != 1)
        mexErrMsgIdAndTxt("mpi_Gather:WrongSizeOfInputArg",
            "Argument comm should be a scalar.");
    marshallin_const_struct1_T(&comm, prhs[7], "comm");

    info = (int32_T*)mxMalloc(sizeof(int32_T));

    toplevel = (boolean_T*)mxMalloc(sizeof(boolean_T));

    /* Invoke the target function */
    mpi_Gather(&sptr, scount, &stype, &rptr, rcount, &rtype, root, &comm, info, toplevel);

    /* Deallocate input and marshall out function outputs */
    destroy_struct0_T(&sptr);
    /* Nothing to be done for scount */
    destroy_struct1_T(&stype);
    destroy_struct0_T(&rptr);
    /* Nothing to be done for rcount */
    destroy_struct1_T(&rtype);
    /* Nothing to be done for root */
    destroy_struct1_T(&comm);
    plhs[0] = move_scalar_to_mxArray(info, mxINT32_CLASS);
    plhs[1] = move_scalar_to_mxArray(toplevel, mxLOGICAL_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Temporary copy for mex outputs. */
    mxArray *outputs[2] = {NULL, NULL};
    int i;
    int nOutputs = (nlhs < 1 ? 1 : nlhs);

    if (nrhs == 8) {
        if (nlhs > 2)
            mexErrMsgIdAndTxt("mpi_Gather:TooManyOutputArguments",
                "Too many output arguments for entry-point mpi_Gather.\n");
        /* Call the API function. */
        __mpi_Gather_api(outputs, prhs);
    }
    else
        mexErrMsgIdAndTxt("mpi_Gather:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point mpi_Gather.");

    /* Copy over outputs to the caller. */
    for (i = 0; i < nOutputs; ++i) {
        plhs[i] = outputs[i];
    }
}
