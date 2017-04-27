/*
 * cuChooseDevice_mex.c
 *
 * Auxiliary code for mexFunction of cuChooseDevice
 *
 * C source code generated by m2c.
 * %#m2c options:f7b3d16df7f4635d2208e13d930903cd
 *
 */

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "matrix.h"
#endif
/* Include the C header file generated by codegen in lib mode */
#include "cuChooseDevice.h"
#include "m2c.c"

/* Include declaration of some helper functions. */
#include "lib2mex_helper.c"


static void marshallin_const_struct0_T(struct0_T *pStruct, const mxArray *mx, const char *mname) {
    mxArray             *sub_mx;

    if (!mxIsStruct(mx))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s has incorrect data type; struct is expected.", mname);
    if (!mxGetField(mx, 0, "name"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field name.", mname);
    if (!mxGetField(mx, 0, "multiProcessorCount"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field multiProcessorCount.", mname);
    if (!mxGetField(mx, 0, "maxThreadsPerMultiProcessor"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field maxThreadsPerMultiProcessor.", mname);
    if (!mxGetField(mx, 0, "maxThreadsPerBlock"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field maxThreadsPerBlock.", mname);
    if (!mxGetField(mx, 0, "warpSize"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field warpSize.", mname);
    if (!mxGetField(mx, 0, "concurrentKernels"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field concurrentKernels.", mname);
    if (!mxGetField(mx, 0, "totalGlobalMem"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field totalGlobalMem.", mname);
    if (!mxGetField(mx, 0, "sharedMemPerBlock"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field sharedMemPerBlock.", mname);
    if (!mxGetField(mx, 0, "sharedMemPerMultiprocessor"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field sharedMemPerMultiprocessor.", mname);
    if (!mxGetField(mx, 0, "totalConstMem"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field totalConstMem.", mname);
    if (!mxGetField(mx, 0, "clockRate"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field clockRate.", mname);
    if (!mxGetField(mx, 0, "asyncEngineCount"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field asyncEngineCount.", mname);
    if (!mxGetField(mx, 0, "computeMode"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field computeMode.", mname);
    if (!mxGetField(mx, 0, "major"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field major.", mname);
    if (!mxGetField(mx, 0, "minor"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field minor.", mname);
    if (!mxGetField(mx, 0, "maxGridSize"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field maxGridSize.", mname);
    if (!mxGetField(mx, 0, "maxThreadsDim"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field maxThreadsDim.", mname);
    if (!mxGetField(mx, 0, "isMultiGpuBoard"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field isMultiGpuBoard.", mname);
    if (!mxGetField(mx, 0, "canMapHostMemory"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field canMapHostMemory.", mname);
    if (!mxGetField(mx, 0, "managedMemory"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field managedMemory.", mname);
    if (!mxGetField(mx, 0, "unifiedAddressing"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field unifiedAddressing.", mname);
    if (!mxGetField(mx, 0, "globalL1CacheSupported"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field globalL1CacheSupported.", mname);
    if (!mxGetField(mx, 0, "l2CacheSize"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field l2CacheSize.", mname);
    if (!mxGetField(mx, 0, "regsPerBlock"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field regsPerBlock.", mname);
    if (!mxGetField(mx, 0, "regsPerMultiprocessor"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field regsPerMultiprocessor.", mname);
    if (!mxGetField(mx, 0, "memoryBusWidth"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field memoryBusWidth.", mname);
    if (!mxGetField(mx, 0, "memoryClockRate"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field memoryClockRate.", mname);
    if (!mxGetField(mx, 0, "memPitch"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field memPitch.", mname);
    if (!mxGetField(mx, 0, "textureAlignment"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field textureAlignment.", mname);
    if (!mxGetField(mx, 0, "deviceOverlap"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field deviceOverlap.", mname);
    if (!mxGetField(mx, 0, "kernelExecTimeoutEnabled"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field kernelExecTimeoutEnabled.", mname);
    if (!mxGetField(mx, 0, "integrated"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field integrated.", mname);
    if (!mxGetField(mx, 0, "ECCEnabled"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field ECCEnabled.", mname);
    if (!mxGetField(mx, 0, "pciBusID"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field pciBusID.", mname);
    if (!mxGetField(mx, 0, "tccDriver"))
        M2C_error("marshallin_const_struct0_T:WrongType",
            "Input argument %s is missing the field tccDriver.", mname);
    if (mxGetNumberOfFields(mx) > 35)
        M2C_warn("marshallin_const_struct0_T:ExtraFields",
            "Extra fields in %s and are ignored.", mname);

    sub_mx = mxGetField(mx, 0, "name");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxCHAR_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument name has incorrect data type; char is expected.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[0] != 1) 
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Dimension 1 of name should equal 1.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[1] > 256)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Dimension 2 of name should be no greater than 256.");
    pStruct->name = mxMalloc(sizeof(emxArray_char_T));
    init_emxArray((emxArray__common*)(pStruct->name), 2);
    alias_mxArray_to_emxArray(sub_mx, (emxArray__common *)(pStruct->name), "name", 2);

    sub_mx = mxGetField(mx, 0, "multiProcessorCount");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument multiProcessorCount has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument multiProcessorCount should be a scalar.");
    pStruct->multiProcessorCount = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "maxThreadsPerMultiProcessor");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument maxThreadsPerMultiProcessor has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument maxThreadsPerMultiProcessor should be a scalar.");
    pStruct->maxThreadsPerMultiProcessor = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "maxThreadsPerBlock");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument maxThreadsPerBlock has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument maxThreadsPerBlock should be a scalar.");
    pStruct->maxThreadsPerBlock = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "warpSize");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument warpSize has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument warpSize should be a scalar.");
    pStruct->warpSize = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "concurrentKernels");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument concurrentKernels has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument concurrentKernels should be a scalar.");
    pStruct->concurrentKernels = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "totalGlobalMem");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT64_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument totalGlobalMem has incorrect data type; uint64 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument totalGlobalMem should be a scalar.");
    pStruct->totalGlobalMem = *(uint64_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "sharedMemPerBlock");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT64_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument sharedMemPerBlock has incorrect data type; uint64 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument sharedMemPerBlock should be a scalar.");
    pStruct->sharedMemPerBlock = *(uint64_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "sharedMemPerMultiprocessor");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT64_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument sharedMemPerMultiprocessor has incorrect data type; uint64 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument sharedMemPerMultiprocessor should be a scalar.");
    pStruct->sharedMemPerMultiprocessor = *(uint64_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "totalConstMem");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT64_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument totalConstMem has incorrect data type; uint64 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument totalConstMem should be a scalar.");
    pStruct->totalConstMem = *(uint64_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "clockRate");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument clockRate has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument clockRate should be a scalar.");
    pStruct->clockRate = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "asyncEngineCount");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument asyncEngineCount has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument asyncEngineCount should be a scalar.");
    pStruct->asyncEngineCount = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "computeMode");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument computeMode has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument computeMode should be a scalar.");
    pStruct->computeMode = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "major");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument major has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument major should be a scalar.");
    pStruct->b_major = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "minor");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument minor has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument minor should be a scalar.");
    pStruct->b_minor = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "maxGridSize");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument maxGridSize has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[0] != 1) 
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Dimension 1 of maxGridSize should equal 1.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[1] != 3) 
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Dimension 2 of maxGridSize should equal 3.");
    copy_mxArray_to_DataSize(pStruct->maxGridSize, 2, NULL, sub_mx, "maxGridSize", 3);

    sub_mx = mxGetField(mx, 0, "maxThreadsDim");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument maxThreadsDim has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[0] != 1) 
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Dimension 1 of maxThreadsDim should equal 1.");
    if (mxGetNumberOfElements(sub_mx) && mxGetDimensions(sub_mx)[1] != 3) 
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Dimension 2 of maxThreadsDim should equal 3.");
    copy_mxArray_to_DataSize(pStruct->maxThreadsDim, 2, NULL, sub_mx, "maxThreadsDim", 3);

    sub_mx = mxGetField(mx, 0, "isMultiGpuBoard");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument isMultiGpuBoard has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument isMultiGpuBoard should be a scalar.");
    pStruct->isMultiGpuBoard = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "canMapHostMemory");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument canMapHostMemory has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument canMapHostMemory should be a scalar.");
    pStruct->canMapHostMemory = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "managedMemory");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument managedMemory has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument managedMemory should be a scalar.");
    pStruct->managedMemory = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "unifiedAddressing");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument unifiedAddressing has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument unifiedAddressing should be a scalar.");
    pStruct->unifiedAddressing = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "globalL1CacheSupported");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument globalL1CacheSupported has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument globalL1CacheSupported should be a scalar.");
    pStruct->globalL1CacheSupported = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "l2CacheSize");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument l2CacheSize has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument l2CacheSize should be a scalar.");
    pStruct->l2CacheSize = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "regsPerBlock");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument regsPerBlock has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument regsPerBlock should be a scalar.");
    pStruct->regsPerBlock = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "regsPerMultiprocessor");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument regsPerMultiprocessor has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument regsPerMultiprocessor should be a scalar.");
    pStruct->regsPerMultiprocessor = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "memoryBusWidth");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument memoryBusWidth has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument memoryBusWidth should be a scalar.");
    pStruct->memoryBusWidth = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "memoryClockRate");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument memoryClockRate has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument memoryClockRate should be a scalar.");
    pStruct->memoryClockRate = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "memPitch");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT64_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument memPitch has incorrect data type; uint64 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument memPitch should be a scalar.");
    pStruct->memPitch = *(uint64_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "textureAlignment");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxUINT64_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument textureAlignment has incorrect data type; uint64 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument textureAlignment should be a scalar.");
    pStruct->textureAlignment = *(uint64_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "deviceOverlap");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument deviceOverlap has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument deviceOverlap should be a scalar.");
    pStruct->deviceOverlap = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "kernelExecTimeoutEnabled");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument kernelExecTimeoutEnabled has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument kernelExecTimeoutEnabled should be a scalar.");
    pStruct->kernelExecTimeoutEnabled = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "integrated");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument integrated has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument integrated should be a scalar.");
    pStruct->integrated = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "ECCEnabled");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument ECCEnabled has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument ECCEnabled should be a scalar.");
    pStruct->ECCEnabled = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "pciBusID");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument pciBusID has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument pciBusID should be a scalar.");
    pStruct->pciBusID = *(int32_T*)mxGetData(sub_mx);

    sub_mx = mxGetField(mx, 0, "tccDriver");
    if (mxGetNumberOfElements(sub_mx) && mxGetClassID(sub_mx) != mxINT32_CLASS)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongInputType",
            "Input argument tccDriver has incorrect data type; int32 is expected.");
    if (mxGetNumberOfElements(sub_mx) != 1)
        mexErrMsgIdAndTxt("marshallin_const_struct0_T:WrongSizeOfInputArg",
            "Argument tccDriver should be a scalar.");
    pStruct->tccDriver = *(int32_T*)mxGetData(sub_mx);
}
static void destroy_struct0_T(struct0_T *pStruct) {

    free_emxArray((emxArray__common*)(pStruct->name));
    mxFree(pStruct->name);


}


static void __cuChooseDevice_api(mxArray **plhs, const mxArray ** prhs) {
    struct0_T            prop;
    int32_T             *dev;
    int32_T             *errCode;
    boolean_T           *toplevel;

    /* Marshall in inputs and preallocate outputs */
    if (mxGetNumberOfElements(prhs[0]) && mxGetClassID(prhs[0]) != mxSTRUCT_CLASS)
        mexErrMsgIdAndTxt("cuChooseDevice:WrongInputType",
            "Input argument prop has incorrect data type; struct is expected.");
    if (mxGetNumberOfElements(prhs[0]) != 1)
        mexErrMsgIdAndTxt("cuChooseDevice:WrongSizeOfInputArg",
            "Argument prop should be a scalar.");
    marshallin_const_struct0_T(&prop, prhs[0], "prop");

    dev = mxMalloc(sizeof(int32_T));

    errCode = mxMalloc(sizeof(int32_T));

    toplevel = mxMalloc(sizeof(boolean_T));

    /* Invoke the target function */
    cuChooseDevice(&prop, dev, errCode, toplevel);

    /* Deallocate input and marshall out function outputs */
    destroy_struct0_T(&prop);
    plhs[0] = move_scalar_to_mxArray(dev, mxINT32_CLASS);
    plhs[1] = move_scalar_to_mxArray(errCode, mxINT32_CLASS);
    plhs[2] = move_scalar_to_mxArray(toplevel, mxLOGICAL_CLASS);

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Temporary copy for mex outputs. */
    mxArray *outputs[3];
    int i;
    int nOutputs = (nlhs < 1 ? 1 : nlhs);

    if (nrhs == 1) {
        if (nlhs > 3)
            mexErrMsgIdAndTxt("cuChooseDevice:TooManyOutputArguments",
                "Too many output arguments for entry-point cuChooseDevice.\n");
        /* Call the API function. */
        __cuChooseDevice_api(outputs, prhs);
    }
    else
        mexErrMsgIdAndTxt("cuChooseDevice:WrongNumberOfInputs",
            "Incorrect number of input variables for entry-point cuChooseDevice.");

    /* Copy over outputs to the caller. */
    for (i = 0; i < nOutputs; ++i) {
        plhs[i] = outputs[i];
    }
}
