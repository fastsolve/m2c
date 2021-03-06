#include "mpi_Comm_set_errhandler.h"
#include "m2c.h"
#include "mpi.h"
#include <string.h>

static MPI_Errhandler b_m2c_castdata(const emxArray_uint8_T *data);
static void b_m2c_error(const emxArray_char_T *varargin_3);
static void c_m2c_error(const emxArray_char_T *varargin_3);
static MPI_Comm m2c_castdata(const emxArray_uint8_T *data);
static void m2c_error(const emxArray_char_T *varargin_3);
static MPI_Errhandler b_m2c_castdata(const emxArray_uint8_T *data)
{
  return *(MPI_Errhandler*)(&data->data[0]);
}

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

  M2C_error("m2c_opaque_obj:WrongInput",
            "Incorrect data type %s. Expected MPI_Errhandler.\n",
            &b_varargin_3->data[0]);
  emxFree_char_T(&b_varargin_3);
}

static void c_m2c_error(const emxArray_char_T *varargin_3)
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

  M2C_error("MPI:RuntimeError",
            "MPI_Comm_set_errhandler failed with error message %s\n",
            &b_varargin_3->data[0]);
  emxFree_char_T(&b_varargin_3);
}

static MPI_Comm m2c_castdata(const emxArray_uint8_T *data)
{
  return *(MPI_Comm*)(&data->data[0]);
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
            "Incorrect data type %s. Expected MPI_Comm.\n", &b_varargin_3->data
            [0]);
  emxFree_char_T(&b_varargin_3);
}

void mpi_Comm_set_errhandler(const M2C_OpaqueType *comm, const M2C_OpaqueType
  *errhandler, int *info, boolean_T *toplevel)
{
  boolean_T p;
  int resultlen;
  boolean_T b_p;
  boolean_T exitg1;
  emxArray_char_T *b_comm;
  int i;
  static const char cv[8] = { 'M', 'P', 'I', '_', 'C', 'o', 'm', 'm' };

  MPI_Comm c_comm;
  MPI_Errhandler obj;
  static const char cv1[14] = { 'M', 'P', 'I', '_', 'E', 'r', 'r', 'h', 'a', 'n',
    'd', 'l', 'e', 'r' };

  unsigned char msg0[1024];
  char * ptr;
  short unnamed_idx_1;
  p = (comm->type->size[1] == 8);
  if (p && (comm->type->size[1] != 0)) {
    resultlen = 0;
    exitg1 = false;
    while ((!exitg1) && (resultlen < 8)) {
      if (!(comm->type->data[resultlen] == cv[resultlen])) {
        p = false;
        exitg1 = true;
      } else {
        resultlen++;
      }
    }
  }

  b_p = (int)p;
  emxInit_char_T(&b_comm, 2);
  if (!b_p) {
    i = b_comm->size[0] * b_comm->size[1];
    b_comm->size[0] = 1;
    b_comm->size[1] = comm->type->size[1] + 1;
    emxEnsureCapacity_char_T(b_comm, i);
    resultlen = comm->type->size[1];
    for (i = 0; i < resultlen; i++) {
      b_comm->data[i] = comm->type->data[i];
    }

    b_comm->data[comm->type->size[1]] = '\x00';
    m2c_error(b_comm);
  }

  c_comm = m2c_castdata(comm->data);
  p = (errhandler->type->size[1] == 14);
  if (p && (errhandler->type->size[1] != 0)) {
    resultlen = 0;
    exitg1 = false;
    while ((!exitg1) && (resultlen < 14)) {
      if (!(errhandler->type->data[resultlen] == cv1[resultlen])) {
        p = false;
        exitg1 = true;
      } else {
        resultlen++;
      }
    }
  }

  b_p = (int)p;
  if (!b_p) {
    i = b_comm->size[0] * b_comm->size[1];
    b_comm->size[0] = 1;
    b_comm->size[1] = errhandler->type->size[1] + 1;
    emxEnsureCapacity_char_T(b_comm, i);
    resultlen = errhandler->type->size[1];
    for (i = 0; i < resultlen; i++) {
      b_comm->data[i] = errhandler->type->data[i];
    }

    b_comm->data[errhandler->type->size[1]] = '\x00';
    b_m2c_error(b_comm);
  }

  obj = b_m2c_castdata(errhandler->data);
  *info = MPI_Comm_set_errhandler(c_comm, obj);
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

    i = b_comm->size[0] * b_comm->size[1];
    b_comm->size[0] = 1;
    b_comm->size[1] = unnamed_idx_1;
    emxEnsureCapacity_char_T(b_comm, i);
    resultlen = unnamed_idx_1;
    for (i = 0; i < resultlen; i++) {
      b_comm->data[i] = (signed char)msg0[i];
    }

    c_m2c_error(b_comm);
  }

  emxFree_char_T(&b_comm);
}

void mpi_Comm_set_errhandler_initialize(void)
{
}

void mpi_Comm_set_errhandler_terminate(void)
{
}
