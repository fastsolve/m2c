#include "cuMatCopySubFromGPU.h"
#include "m2c.h"
#include "cuda4m.h"

static void b_m2c_error(void);
static void c_m2c_error(void);
static void cuBlasGetErrorString(int errCode, emxArray_char_T *cstr);
static void d_m2c_error(int varargin_3);
static void e_m2c_error(const emxArray_char_T *varargin_3);
static void emxFreeStruct_struct1_T(struct1_T *pStruct);
static void emxInitStruct_struct1_T(struct1_T *pStruct);
static void f_m2c_error(const emxArray_char_T *varargin_3);
static void m2c_error(void);
static void b_m2c_error(void)
{
  M2C_error("cuMatCopyToGPU:SizeMismatch", "Source matrix is too small.");
}

static void c_m2c_error(void)
{
  M2C_error("cuMatCopyToGPU:SizeMismatch", "Target matrix is too small.");
}

static void cuBlasGetErrorString(int errCode, emxArray_char_T *cstr)
{
  int val;
  int b_val;
  int c_val;
  int d_val;
  int e_val;
  int f_val;
  int g_val;
  int varargin_8;
  static const char cv0[14] = { 'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 'e', 'r',
    'r', 'o', 'r', '\x00' };

  static const char cv1[22] = { 'C', 'U', 'B', 'L', 'A', 'S', '_', 'S', 'T', 'A',
    'T', 'U', 'S', '_', 'S', 'U', 'C', 'C', 'E', 'S', 'S', '\x00' };

  static const char cv2[30] = { 'C', 'U', 'B', 'L', 'A', 'S', '_', 'S', 'T', 'A',
    'T', 'U', 'S', '_', 'N', 'O', 'T', '_', 'I', 'N', 'I', 'T', 'I', 'A', 'L',
    'I', 'Z', 'E', 'D', '\x00' };

  static const char cv3[27] = { 'C', 'U', 'B', 'L', 'A', 'S', '_', 'S', 'T', 'A',
    'T', 'U', 'S', '_', 'A', 'L', 'L', 'O', 'C', '_', 'F', 'A', 'I', 'L', 'E',
    'D', '\x00' };

  static const char cv4[28] = { 'C', 'U', 'B', 'L', 'A', 'S', '_', 'S', 'T', 'A',
    'T', 'U', 'S', '_', 'I', 'N', 'V', 'A', 'L', 'I', 'D', '_', 'V', 'A', 'L',
    'U', 'E', '\x00' };

  static const char cv5[28] = { 'C', 'U', 'B', 'L', 'A', 'S', '_', 'S', 'T', 'A',
    'T', 'U', 'S', '_', 'A', 'R', 'C', 'H', '_', 'M', 'I', 'S', 'M', 'A', 'T',
    'C', 'H', '\x00' };

  static const char cv6[28] = { 'C', 'U', 'B', 'L', 'A', 'S', '_', 'S', 'T', 'A',
    'T', 'U', 'S', '_', 'M', 'A', 'P', 'P', 'I', 'N', 'G', '_', 'E', 'R', 'R',
    'O', 'R', '\x00' };

  static const char cv7[31] = { 'C', 'U', 'B', 'L', 'A', 'S', '_', 'S', 'T', 'A',
    'T', 'U', 'S', '_', 'E', 'X', 'E', 'C', 'U', 'T', 'I', 'O', 'N', '_', 'F',
    'A', 'I', 'L', 'E', 'D', '\x00' };

  static const char cv8[29] = { 'C', 'U', 'B', 'L', 'A', 'S', '_', 'S', 'T', 'A',
    'T', 'U', 'S', '_', 'I', 'N', 'T', 'E', 'R', 'N', 'A', 'L', '_', 'E', 'R',
    'R', 'O', 'R', '\x00' };

  val = (CUBLAS_STATUS_SUCCESS);
  b_val = (CUBLAS_STATUS_NOT_INITIALIZED);
  c_val = (CUBLAS_STATUS_ALLOC_FAILED);
  d_val = (CUBLAS_STATUS_INVALID_VALUE);
  e_val = (CUBLAS_STATUS_ARCH_MISMATCH);
  f_val = (CUBLAS_STATUS_MAPPING_ERROR);
  g_val = (CUBLAS_STATUS_EXECUTION_FAILED);
  varargin_8 = (CUBLAS_STATUS_INTERNAL_ERROR);
  if (val == errCode) {
    val = 0;
  } else if (b_val == errCode) {
    val = 1;
  } else if (c_val == errCode) {
    val = 2;
  } else if (d_val == errCode) {
    val = 3;
  } else if (e_val == errCode) {
    val = 4;
  } else if (f_val == errCode) {
    val = 5;
  } else if (g_val == errCode) {
    val = 6;
  } else if (varargin_8 == errCode) {
    val = 7;
  } else {
    val = -1;
  }

  switch (val) {
   case 0:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 22;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 22; val++) {
      cstr->data[val] = cv1[val];
    }
    break;

   case 1:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 30;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 30; val++) {
      cstr->data[val] = cv2[val];
    }
    break;

   case 2:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 27;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 27; val++) {
      cstr->data[val] = cv3[val];
    }
    break;

   case 3:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 28;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 28; val++) {
      cstr->data[val] = cv4[val];
    }
    break;

   case 4:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 28;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 28; val++) {
      cstr->data[val] = cv5[val];
    }
    break;

   case 5:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 28;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 28; val++) {
      cstr->data[val] = cv6[val];
    }
    break;

   case 6:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 31;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 31; val++) {
      cstr->data[val] = cv7[val];
    }
    break;

   case 7:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 29;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 29; val++) {
      cstr->data[val] = cv8[val];
    }
    break;

   default:
    val = cstr->size[0] * cstr->size[1];
    cstr->size[0] = 1;
    cstr->size[1] = 14;
    emxEnsureCapacity((emxArray__common *)cstr, val, (int)sizeof(char));
    for (val = 0; val < 14; val++) {
      cstr->data[val] = cv0[val];
    }
    break;
  }
}

static void d_m2c_error(int varargin_3)
{
  M2C_error("cuGetSizePerElement:WrongType", "Unknow data type %d.\n",
            varargin_3);
}

static void e_m2c_error(const emxArray_char_T *varargin_3)
{
  emxArray_char_T *b_varargin_3;
  int i0;
  int loop_ub;
  emxInit_char_T(&b_varargin_3, 2);
  i0 = b_varargin_3->size[0] * b_varargin_3->size[1];
  b_varargin_3->size[0] = 1;
  b_varargin_3->size[1] = varargin_3->size[1];
  emxEnsureCapacity((emxArray__common *)b_varargin_3, i0, (int)sizeof(char));
  loop_ub = varargin_3->size[0] * varargin_3->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_varargin_3->data[i0] = varargin_3->data[i0];
  }

  M2C_error("CUDA:RuntimeError", "cublasGetMatrix returned error code %s\n",
            &b_varargin_3->data[0]);
  emxFree_char_T(&b_varargin_3);
}

static void emxFreeStruct_struct1_T(struct1_T *pStruct)
{
  emxFree_uint8_T(&pStruct->data);
  emxFree_char_T(&pStruct->type);
}

static void emxInitStruct_struct1_T(struct1_T *pStruct)
{
  emxInit_uint8_T(&pStruct->data, 1);
  emxInit_char_T(&pStruct->type, 2);
}

static void f_m2c_error(const emxArray_char_T *varargin_3)
{
  emxArray_char_T *b_varargin_3;
  int i1;
  int loop_ub;
  emxInit_char_T(&b_varargin_3, 2);
  i1 = b_varargin_3->size[0] * b_varargin_3->size[1];
  b_varargin_3->size[0] = 1;
  b_varargin_3->size[1] = varargin_3->size[1];
  emxEnsureCapacity((emxArray__common *)b_varargin_3, i1, (int)sizeof(char));
  loop_ub = varargin_3->size[0] * varargin_3->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_varargin_3->data[i1] = varargin_3->data[i1];
  }

  M2C_error("m2c_opaque_obj:WrongInput",
            "Incorrect data type %s. Expected cudaStream_t.\n",
            &b_varargin_3->data[0]);
  emxFree_char_T(&b_varargin_3);
}

static void m2c_error(void)
{
  M2C_error("cuMatCopyToGPU:TypeMismatch", "Real and complex numbers mismatch.");
}

void cuMatCopySubFromGPU(int nrows, int ncols, const struct0_T *cuMat, const
  emxArray_real_T *mat, int *errCode, boolean_T *toplevel)
{
  int sizepe;
  unsigned long data;
  void * output;
  void * ptr;
  emxArray_char_T *r0;
  *toplevel = true;
  if ((cuMat->type != 8) && (cuMat->type != 4)) {
    m2c_error();
  } else if ((nrows > mat->size[0]) || (ncols > mat->size[0])) {
    b_m2c_error();
  } else {
    if ((nrows > cuMat->dims[0]) || (ncols > cuMat->dims[1])) {
      c_m2c_error();
    }
  }

  if ((cuMat->type == 8) || (cuMat->type == 108) || (cuMat->type == 14) ||
      (cuMat->type == 24)) {
    sizepe = 8;
  } else if ((cuMat->type == 4) || (cuMat->type == 13) || (cuMat->type == 23)) {
    sizepe = 4;
  } else if ((cuMat->type == 12) || (cuMat->type == 22)) {
    sizepe = 2;
  } else if ((cuMat->type == 11) || (cuMat->type == 21)) {
    sizepe = 1;
  } else if (cuMat->type == 116) {
    sizepe = 16;
  } else {
    d_m2c_error(cuMat->type);
    sizepe = 0;
  }

  data = cuMat->data;
  output = *(void **)(&data);
  ptr = (void *)(&mat->data[0]);
  *errCode = cublasGetMatrix(nrows, ncols, sizepe, output, cuMat->dims[0], ptr,
    mat->size[0]);
  if (*errCode != 0) {
    emxInit_char_T(&r0, 2);
    cuBlasGetErrorString(*errCode, r0);
    e_m2c_error(r0);
    emxFree_char_T(&r0);
  }
}

void cuMatCopySubFromGPU_async(int nrows, int ncols, const struct0_T *cuMat,
  const emxArray_real_T *mat, const struct1_T *strm, int *errCode, boolean_T
  *toplevel)
{
  int sizepe;
  unsigned long data;
  void * output;
  void * ptr;
  boolean_T p;
  boolean_T b_p;
  int k;
  int exitg2;
  int i2;
  boolean_T exitg1;
  emxArray_char_T *b_strm;
  static const char cv9[12] = { 'c', 'u', 'd', 'a', 'S', 't', 'r', 'e', 'a', 'm',
    '_', 't' };

  emxArray_uint8_T *b_data;
  cudaStream_t hdl;
  emxArray_char_T *r1;
  if ((cuMat->type != 8) && (cuMat->type != 4)) {
    m2c_error();
  } else if ((nrows > mat->size[0]) || (ncols > mat->size[0])) {
    b_m2c_error();
  } else {
    if ((nrows > cuMat->dims[0]) || (ncols > cuMat->dims[1])) {
      c_m2c_error();
    }
  }

  if ((cuMat->type == 8) || (cuMat->type == 108) || (cuMat->type == 14) ||
      (cuMat->type == 24)) {
    sizepe = 8;
  } else if ((cuMat->type == 4) || (cuMat->type == 13) || (cuMat->type == 23)) {
    sizepe = 4;
  } else if ((cuMat->type == 12) || (cuMat->type == 22)) {
    sizepe = 2;
  } else if ((cuMat->type == 11) || (cuMat->type == 21)) {
    sizepe = 1;
  } else if (cuMat->type == 116) {
    sizepe = 16;
  } else {
    d_m2c_error(cuMat->type);
    sizepe = 0;
  }

  data = cuMat->data;
  output = *(void **)(&data);
  ptr = (void *)(&mat->data[0]);
  p = false;
  b_p = false;
  k = 0;
  do {
    exitg2 = 0;
    if (k < 2) {
      i2 = strm->type->size[k];
      if (i2 != 11 * k + 1) {
        exitg2 = 1;
      } else {
        k++;
      }
    } else {
      b_p = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  if (b_p && (!(strm->type->size[1] == 0))) {
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 12)) {
      if (!(strm->type->data[k] == cv9[k])) {
        b_p = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (b_p) {
    p = true;
  }

  if (!p) {
    emxInit_char_T(&b_strm, 2);
    i2 = b_strm->size[0] * b_strm->size[1];
    b_strm->size[0] = 1;
    b_strm->size[1] = strm->type->size[1] + 1;
    emxEnsureCapacity((emxArray__common *)b_strm, i2, (int)sizeof(char));
    k = strm->type->size[1];
    for (i2 = 0; i2 < k; i2++) {
      b_strm->data[b_strm->size[0] * i2] = strm->type->data[strm->type->size[0] *
        i2];
    }

    b_strm->data[b_strm->size[0] * strm->type->size[1]] = '\x00';
    f_m2c_error(b_strm);
    emxFree_char_T(&b_strm);
  }

  emxInit_uint8_T(&b_data, 1);
  i2 = b_data->size[0];
  b_data->size[0] = strm->data->size[0];
  emxEnsureCapacity((emxArray__common *)b_data, i2, (int)sizeof(unsigned char));
  k = strm->data->size[0];
  for (i2 = 0; i2 < k; i2++) {
    b_data->data[i2] = strm->data->data[i2];
  }

  hdl = *(cudaStream_t*)(&b_data->data[0]);
  *errCode = cublasGetMatrixAsync(nrows, ncols, sizepe, output, cuMat->dims[0],
    ptr, mat->size[0], hdl);
  emxFree_uint8_T(&b_data);
  if (*errCode != 0) {
    emxInit_char_T(&r1, 2);
    cuBlasGetErrorString(*errCode, r1);
    e_m2c_error(r1);
    emxFree_char_T(&r1);
  }

  *toplevel = true;
}

void cuMatCopySubFromGPU_initialize(void)
{
}

void cuMatCopySubFromGPU_terminate(void)
{
}

void emxDestroy_struct1_T(struct1_T emxArray)
{
  emxFreeStruct_struct1_T(&emxArray);
}

void emxInit_struct1_T(struct1_T *pStruct)
{
  emxInitStruct_struct1_T(pStruct);
}
