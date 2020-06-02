/*
 * mpi/codegen/lib/mpi_Intercomm_create/mpi_Intercomm_create_mex.c
 *
 * Auxiliary code for mexFunction of mpi_Intercomm_create
 *
 * C source code generated by m2c.
 * %#m2c options:4b1370cc2d9b88310deec2283721beac
 *
 */

#include "mex.h"
#if !defined(MATLAB_MEX_FILE) && defined(printf)
#undef printf
#endif
/* Include the C header file generated by codegen in lib mode */
#include "mpi_Intercomm_create.h"
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
            "Dimension 2 of data should be equal to 1.");
    pStruct->data = (emxArray_uint8_T*)mxMalloc(sizeof(emxArray_uint8_T));
    init_emxArray((emxArray__common*)(pStruct->data), 1);
    alias_mxArray_to_emxArray(sub_mx, (emxArray__common *)(pStruct->data), "data", 1);

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


    pStruct->data = (emxArray_uint8_T*)mxMalloc(sizeof(emxArray_uint8_T));
    init_emxArray((emxArray__common*)(pStruct->data), 1);

    pStruct->type = (emxArray_char_T*)mxMalloc(sizeof(emxArray_char_T));
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


static void __mpi_Intercomm_create_api(mxArray **plhs, const mxArray ** prhs) {
    struct0_T            local_comm;
    int32_T              local_leader;
    struct0_T            peer_comm;
    int32_T              remote_leader;
    int32_T              tag;
    struct0_T            newcomm;
    int32_T             *info;
    boolean_T           *toplevel;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongInputType",
            "Input argument local_comm has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongSizeOfInputArg",
            "Argument local_comm should be a scalar.");
    marshallin_const_struct0_T(&local_comm, prhs[0], "local_comm");

    if (mxGetNumberOfElements(prhs[1]) && mxGetClassID(prhs[1]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongInputType",
            "Input argument local_leader has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[1]) != 1)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongSizeOfInputArg",
            "Argument local_leader should be a scalar.");
    local_leader = *(int32_T*)mxGetData(prhs[1]);

    if (mxGetNumberOfElements(prhs[2]) && mxGetClassID(prhs[2]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongInputType",
            "Input argument peer_comm has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[2]) != 1)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongSizeOfInputArg",
            "Argument peer_comm should be a scalar.");
    marshallin_const_struct0_T(&peer_comm, prhs[2], "peer_comm");

    if (mxGetNumberOfElements(prhs[3]) && mxGetClassID(prhs[3]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongInputType",
            "Input argument remote_leader has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[3]) != 1)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongSizeOfInputArg",
            "Argument remote_leader should be a scalar.");
    remote_leader = *(int32_T*)mxGetData(prhs[3]);

    if (mxGetNumberOfElements(prhs[4]) && mxGetClassID(prhs[4]) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongInputType",
            "Input argument tag has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(prhs[4]) != 1)
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongSizeOfInputArg",
            "Argument tag should be a scalar.");
    tag = *(int32_T*)mxGetData(prhs[4]);
    prealloc_struct0_T(&newcomm);

    info = (int32_T*)mxMalloc(sizeof(int32_T));

    toplevel = (boolean_T*)mxMalloc(sizeof(boolean_T));

    /* Invoke the target function */
    mpi_Intercomm_create(&local_comm, local_leader, &peer_comm, remote_leader, tag, &newcomm, info, toplevel);

    /* Deallocate input and marshall out function outputs */
    destroy_struct0_T(&local_comm);
    /* Nothing to be done for local_leader */
    destroy_struct0_T(&peer_comm);
    /* Nothing to be done for remote_leader */
    /* Nothing to be done for tag */
    plhs[0] = marshallout_struct0_T(&newcomm);
    plhs[1] = move_scalar_to_mxArray(info, mxINT32_CLASS);
    plhs[2] = move_scalar_to_mxArray(toplevel, mxLOGICAL_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Temporary copy for mex outputs. */
    mxArray *outputs[3] = {NULL, NULL, NULL};
    int i;
    int nOutputs = (nlhs < 1 ? 1 : nlhs);

    if (nrhs == 5) {
        if (nlhs > 3)
            mexErrMsgIdAndTxt("mpi_Intercomm_create:TooManyOutputArguments",
                "Too many output arguments for entry-point mpi_Intercomm_create.\n");
        /* Call the API function. */
        __mpi_Intercomm_create_api(outputs, prhs);
    }
    else
        mexErrMsgIdAndTxt("mpi_Intercomm_create:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point mpi_Intercomm_create.");

    /* Copy over outputs to the caller. */
    for (i = 0; i < nOutputs; ++i) {
        plhs[i] = outputs[i];
    }
}
