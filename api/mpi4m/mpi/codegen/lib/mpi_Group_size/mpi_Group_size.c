#include "mpi_Group_size.h"
#include "m2c.h"
#include "mpi.h"
#include <string.h>

static void b_m2c_error(const emxArray_char_T *varargin_3);
static MPI_Group m2c_castdata(const emxArray_uint8_T *data);
static void m2c_error(const emxArray_char_T *varargin_3);
static void b_m2c_error(const emxArray_char_T *varargin_3)
{
  emxArray_char_T *b_varargin_3;
  int i;
  int loop_ub;
  emxInit_char_T(&b_varargin_3, 2);
  i = b_varargin_3->size[0] * b_varargin_3->size[1];
  b_varargin_3->size[0] = 1;
  b_varargin_3->size[1] = varargin_3->size[1];
  emxEnsureCapacity_char_T(b_varargin_3, i);
  loop_ub = varargin_3->size[0] * varargin_3->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_varargin_3->data[i] = varargin_3->data[i];
  }

  M2C_error("MPI:RuntimeError", "MPI_Group_size failed with error message %s\n",
            &b_varargin_3->data[0]);
  emxFree_char_T(&b_varargin_3);
}

static MPI_Group m2c_castdata(const emxArray_uint8_T *data)
{
  return *(MPI_Group*)(&data->data[0]);
}

static void m2c_error(const emxArray_char_T *varargin_3)
{
  emxArray_char_T *b_varargin_3;
  int i;
  int loop_ub;
  emxInit_char_T(&b_varargin_3, 2);
  i = b_varargin_3->size[0] * b_varargin_3->size[1];
  b_varargin_3->size[0] = 1;
  b_varargin_3->size[1] = varargin_3->size[1];
  emxEnsureCapacity_char_T(b_varargin_3, i);
  loop_ub = varargin_3->size[0] * varargin_3->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_varargin_3->data[i] = varargin_3->data[i];
  }

  M2C_error("m2c_opaque_obj:WrongInput",
            "Incorrect data type %s. Expected MPI_Group.\n", &b_varargin_3->
            data[0]);
  emxFree_char_T(&b_varargin_3);
}

void mpi_Group_size(const M2C_OpaqueType *group, int *size, int *info, boolean_T
                    *toplevel)
{
  boolean_T p;
  int resultlen;
  boolean_T b_p;
  boolean_T exitg1;
  emxArray_char_T *b_group;
  int i;
  static const char cv[9] = { 'M', 'P', 'I', '_', 'G', 'r', 'o', 'u', 'p' };

  MPI_Group obj;
  unsigned char msg0[1024];
  char * ptr;
  short unnamed_idx_1;
  p = (group->type->size[1] == 9);
  if (p && (group->type->size[1] != 0)) {
    resultlen = 0;
    exitg1 = false;
    while ((!exitg1) && (resultlen < 9)) {
      if (!(group->type->data[resultlen] == cv[resultlen])) {
        p = false;
        exitg1 = true;
      } else {
        resultlen++;
      }
    }
  }

  b_p = (int)p;
  emxInit_char_T(&b_group, 2);
  if (!b_p) {
    i = b_group->size[0] * b_group->size[1];
    b_group->size[0] = 1;
    b_group->size[1] = group->type->size[1] + 1;
    emxEnsureCapacity_char_T(b_group, i);
    resultlen = group->type->size[1];
    for (i = 0; i < resultlen; i++) {
      b_group->data[i] = group->type->data[i];
    }

    b_group->data[group->type->size[1]] = '\x00';
    m2c_error(b_group);
  }

  obj = m2c_castdata(group->data);
  *info = MPI_Group_size(obj, size);
  *toplevel = true;
  if (*info != 0) {
    memset(&msg0[0], 0, 1024U * sizeof(unsigned char));
    ptr = (char *)(msg0);
    resultlen = 0;
    MPI_Error_string(*info, ptr, &resultlen);
    if (1 > resultlen) {
      unnamed_idx_1 = 0;
    } else {
      unnamed_idx_1 = (short)resultlen;
    }

    i = b_group->size[0] * b_group->size[1];
    b_group->size[0] = 1;
    b_group->size[1] = unnamed_idx_1;
    emxEnsureCapacity_char_T(b_group, i);
    resultlen = unnamed_idx_1;
    for (i = 0; i < resultlen; i++) {
      b_group->data[i] = (signed char)msg0[i];
    }

    b_m2c_error(b_group);
  }

  emxFree_char_T(&b_group);
}

void mpi_Group_size_initialize(void)
{
}

void mpi_Group_size_terminate(void)
{
}
