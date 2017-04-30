/*
 * mpi/codegen/lib/mpi_Alltoallv/mpi_Alltoallv_mex.c
 *
 * Auxiliary code for mexFunction of mpi_Alltoallv
 *
 * C source code generated by m2c.
 * %#m2c options:32d5d5250566a891685e1026298d8083
 *
 */

#include "mex.h"
#if !defined(MATLAB_MEX_FILE) && defined(printf)
#undef printf
#endif
/* Include the C header file generated by codegen in lib mode */
#include "mpi_Alltoallv.h"
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
            "Dimension 1 of type should equal 1.");
    pStruct->type = mxMalloc(sizeof(emxArray_char_T));
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
            "Dimension 2 of data should equal 1.");
    pStruct->data = mxMalloc(sizeof(emxArray_uint8_T));
    init_emxArray((emxArray__common*)(pStruct->data), 1);
    alias_mxArray_to_emxArray(sub_mx, (emxArray__common *)(pStruct->data), "data", 1);

    sub_mx = mxGetField(mx, 0, "type");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxCHAR_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct1_T:WrongInputType",
            "Input argument type has incorrect data type; char is expected.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[0] != 1) 
        mexErrMsgIdAndTxt("marshallin_const_struct1_T:WrongSizeOfInputArg",
            "Dimension 1 of type should equal 1.");
    pStruct->type = mxMalloc(sizeof(emxArray_char_T));
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


static void __mpi_Alltoallv_api(mxArray **plhs, const mxArray ** prhs) {
    struct0_T            sptr;
    emxArray_int32_T     scounts;
    emxArray_int32_T     sdisps;
    struct1_T            stype;
    struct0_T            rptr;
    emxArray_int32_T     rcounts;
    emxArray_int32_T     rdisps;
    struct1_T            rtype;
    struct1_T            comm;
    int32_T             *info;
    boolean_T           *toplevel;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument sptr has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongSizeOfInputArg",
            "Argument sptr should be a scalar.");
    marshallin_const_struct0_T(&sptr, prhs[0], "sptr");

    if (mxGetNumberOfElements(prhs[1]) && mxGetClassID(prhs[1]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument scounts has incorrect data type; int32 is expected.");
    alias_mxArray_to_emxArray(prhs[1], (emxArray__common *)(&scounts), "scounts", 2);

    if (mxGetNumberOfElements(prhs[2]) && mxGetClassID(prhs[2]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument sdisps has incorrect data type; int32 is expected.");
    alias_mxArray_to_emxArray(prhs[2], (emxArray__common *)(&sdisps), "sdisps", 2);

    if (mxGetNumberOfElements(prhs[3]) && mxGetClassID(prhs[3]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument stype has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[3]) != 1)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongSizeOfInputArg",
            "Argument stype should be a scalar.");
    marshallin_const_struct1_T(&stype, prhs[3], "stype");

    if (mxGetNumberOfElements(prhs[4]) && mxGetClassID(prhs[4]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument rptr has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[4]) != 1)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongSizeOfInputArg",
            "Argument rptr should be a scalar.");
    marshallin_const_struct0_T(&rptr, prhs[4], "rptr");

    if (mxGetNumberOfElements(prhs[5]) && mxGetClassID(prhs[5]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument rcounts has incorrect data type; int32 is expected.");
    alias_mxArray_to_emxArray(prhs[5], (emxArray__common *)(&rcounts), "rcounts", 2);

    if (mxGetNumberOfElements(prhs[6]) && mxGetClassID(prhs[6]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument rdisps has incorrect data type; int32 is expected.");
    alias_mxArray_to_emxArray(prhs[6], (emxArray__common *)(&rdisps), "rdisps", 2);

    if (mxGetNumberOfElements(prhs[7]) && mxGetClassID(prhs[7]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument rtype has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[7]) != 1)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongSizeOfInputArg",
            "Argument rtype should be a scalar.");
    marshallin_const_struct1_T(&rtype, prhs[7], "rtype");

    if (mxGetNumberOfElements(prhs[8]) && mxGetClassID(prhs[8]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongInputType",
            "Input argument comm has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[8]) != 1)
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongSizeOfInputArg",
            "Argument comm should be a scalar.");
    marshallin_const_struct1_T(&comm, prhs[8], "comm");

    info = mxMalloc(sizeof(int32_T));

    toplevel = mxMalloc(sizeof(boolean_T));

    /* Invoke the target function */
    mpi_Alltoallv(&sptr, &scounts, &sdisps, &stype, &rptr, &rcounts, &rdisps, &rtype, &comm, info, toplevel);

    /* Deallocate input and marshall out function outputs */
    destroy_struct0_T(&sptr);
    free_emxArray((emxArray__common*)(&scounts));
    free_emxArray((emxArray__common*)(&sdisps));
    destroy_struct1_T(&stype);
    destroy_struct0_T(&rptr);
    free_emxArray((emxArray__common*)(&rcounts));
    free_emxArray((emxArray__common*)(&rdisps));
    destroy_struct1_T(&rtype);
    destroy_struct1_T(&comm);
    plhs[0] = move_scalar_to_mxArray(info, mxINT32_CLASS);
    plhs[1] = move_scalar_to_mxArray(toplevel, mxLOGICAL_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Temporary copy for mex outputs. */
    mxArray *outputs[2];
    int i;
    int nOutputs = (nlhs < 1 ? 1 : nlhs);

    if (nrhs == 9) {
        if (nlhs > 2)
            mexErrMsgIdAndTxt("mpi_Alltoallv:TooManyOutputArguments",
                "Too many output arguments for entry-point mpi_Alltoallv.\n");
        /* Call the API function. */
        __mpi_Alltoallv_api(outputs, prhs);
    }
    else
        mexErrMsgIdAndTxt("mpi_Alltoallv:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point mpi_Alltoallv.");

    /* Copy over outputs to the caller. */
    for (i = 0; i < nOutputs; ++i) {
        plhs[i] = outputs[i];
    }
}
