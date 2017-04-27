/*
 * mpi/codegen/lib/mpi_Iprobe/mpi_Iprobe_mex.c
 *
 * Auxiliary code for mexFunction of mpi_Iprobe
 *
 * C source code generated by m2c.
 * %#m2c options:f21ad8bb54dbfd010094aaa26b163ddf
 *
 */

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "matrix.h"
#endif
/* Include the C header file generated by codegen in lib mode */
#include "mpi_Iprobe.h"
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
    if (!mxGetField(mx, 0, "nitems"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field nitems.", mname);
    if (mxGetNumberOfFields(mx) > 3)
        M2C_warn("marshallin_const_struct0_T:ExtraFields",
            "Extra fields in %s and are ignored.", mname);

    sub_mx = mxGetField(mx, 0, "data");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT8_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument data has incorrect data type; uint8 is expected.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[1] != 1) 
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Dimension 2 of data should equal 1.");
    pStruct->data = mxMalloc(sizeof(emxArray_uint8_T));
    init_emxArray((emxArray__common*)(pStruct->data), 1);
    alias_mxArray_to_emxArray(sub_mx, (emxArray__common *)(pStruct->data), "data", 1);

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

    sub_mx = mxGetField(mx, 0, "nitems");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument nitems has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument nitems should be a scalar.");
    pStruct->nitems = *(int32_T*)mxGetData(sub_mx);
}
static void prealloc_struct0_T(struct0_T *pStruct) {


    pStruct->data = mxMalloc(sizeof(emxArray_uint8_T));
    init_emxArray((emxArray__common*)(pStruct->data), 1);

    pStruct->type = mxMalloc(sizeof(emxArray_char_T));
    init_emxArray((emxArray__common*)(pStruct->type), 2);

}
static mxArray *marshallout_struct0_T(struct0_T *pStruct) {
    const char           *fields[] = {"data", "type", "nitems"};
    int                  one=1;
    mxArray              *mx = create_struct_mxArray(1, &one, 3, fields);

    mxSetField(mx, 0, "data", move_emxArray_to_mxArray((emxArray__common*)(pStruct->data), mxUINT8_CLASS));
    mxFree(pStruct->data->size);
    mxFree(pStruct->data);

    mxSetField(mx, 0, "type", move_emxArray_to_mxArray((emxArray__common*)(pStruct->type), mxCHAR_CLASS));
    mxFree(pStruct->type->size);
    mxFree(pStruct->type);

    mxSetField(mx, 0, "nitems", copy_scalar_to_mxArray(&pStruct->nitems, mxINT32_CLASS));
    return mx;
}
static void destroy_struct0_T(struct0_T *pStruct) {

    free_emxArray((emxArray__common*)(pStruct->data));
    mxFree(pStruct->data);

    free_emxArray((emxArray__common*)(pStruct->type));
    mxFree(pStruct->type);


}


static void __mpi_Iprobe_api(mxArray **plhs, const mxArray ** prhs) {
    int32_T              source;
    int32_T              tag;
    struct0_T            comm;
    int32_T             *flag;
    struct0_T            stat;
    int32_T             *info;
    boolean_T           *toplevel;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Iprobe:WrongInputType",
            "Input argument source has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("mpi_Iprobe:WrongSizeOfInputArg",
            "Argument source should be a scalar.");
    source = *(int32_T*)mxGetData(prhs[0]);

    if (mxGetNumberOfElements(prhs[1]) && mxGetClassID(prhs[1]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Iprobe:WrongInputType",
            "Input argument tag has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[1]) != 1)
        mexErrMsgIdAndTxt("mpi_Iprobe:WrongSizeOfInputArg",
            "Argument tag should be a scalar.");
    tag = *(int32_T*)mxGetData(prhs[1]);

    if (mxGetNumberOfElements(prhs[2]) && mxGetClassID(prhs[2]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Iprobe:WrongInputType",
            "Input argument comm has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[2]) != 1)
        mexErrMsgIdAndTxt("mpi_Iprobe:WrongSizeOfInputArg",
            "Argument comm should be a scalar.");
    marshallin_const_struct0_T(&comm, prhs[2], "comm");

    flag = mxMalloc(sizeof(int32_T));
    prealloc_struct0_T(&stat);

    info = mxMalloc(sizeof(int32_T));

    toplevel = mxMalloc(sizeof(boolean_T));

    /* Invoke the target function */
    mpi_Iprobe(source, tag, &comm, flag, &stat, info, toplevel);

    /* Deallocate input and marshall out function outputs */
    /* Nothing to be done for source */
    /* Nothing to be done for tag */
    destroy_struct0_T(&comm);
    plhs[0] = move_scalar_to_mxArray(flag, mxINT32_CLASS);
    plhs[1] = marshallout_struct0_T(&stat);
    plhs[2] = move_scalar_to_mxArray(info, mxINT32_CLASS);
    plhs[3] = move_scalar_to_mxArray(toplevel, mxLOGICAL_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Temporary copy for mex outputs. */
    mxArray *outputs[4];
    int i;
    int nOutputs = (nlhs < 1 ? 1 : nlhs);

    if (nrhs == 3) {
        if (nlhs > 4)
            mexErrMsgIdAndTxt("mpi_Iprobe:TooManyOutputArguments",
                "Too many output arguments for entry-point mpi_Iprobe.\n");
        /* Call the API function. */
        __mpi_Iprobe_api(outputs, prhs);
    }
    else
        mexErrMsgIdAndTxt("mpi_Iprobe:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point mpi_Iprobe.");

    /* Copy over outputs to the caller. */
    for (i = 0; i < nOutputs; ++i) {
        plhs[i] = outputs[i];
    }
}
