#include "mpi_Bsend_init.h"
#include "m2c.h"
#include "mpi.h"
#include <string.h>

static MPI_Comm b_m2c_castdata(const emxArray_uint8_T *data);
static void b_m2c_error(void);
static void c_m2c_error(const emxArray_char_T *varargin_3);
static void d_m2c_error(const emxArray_char_T *varargin_3);
static MPI_Datatype m2c_castdata(const emxArray_uint8_T *data);
static void m2c_error(const emxArray_char_T *varargin_3);
static MPI_Comm b_m2c_castdata(const emxArray_uint8_T *data)
{
  return *(MPI_Comm*)(&data->data[0]);
}

static void b_m2c_error(void)
{
  M2C_error("mpi_Bsend_init:OutOfBound",
            "Message size is larger than variable size.");
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

  M2C_error("m2c_opaque_obj:WrongInput",
            "Incorrect data type %s. Expected MPI_Comm.\n", &b_varargin_3->data
            [0]);
  emxFree_char_T(&b_varargin_3);
}

static void d_m2c_error(const emxArray_char_T *varargin_3)
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

  M2C_error("MPI:RuntimeError", "MPI_Bsend_init failed with error message %s\n",
            &b_varargin_3->data[0]);
  emxFree_char_T(&b_varargin_3);
}

static MPI_Datatype m2c_castdata(const emxArray_uint8_T *data)
{
  return *(MPI_Datatype*)(&data->data[0]);
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
            "Incorrect data type %s. Expected MPI_Datatype.\n",
            &b_varargin_3->data[0]);
  emxFree_char_T(&b_varargin_3);
}

void mpi_Bsend_init(const M2C_OpaquePtrType *ptr, int count, const
                    M2C_OpaqueType *datatype, int dest, int tag, const
                    M2C_OpaqueType *comm, M2C_OpaqueType *req, int *info,
                    boolean_T *toplevel)
{
  boolean_T p;
  int sizepe;
  boolean_T b_p;
  boolean_T exitg1;
  emxArray_char_T *b_datatype;
  int i;
  static const char cv[12] = { 'M', 'P', 'I', '_', 'D', 'a', 't', 'a', 't', 'y',
    'p', 'e' };

  MPI_Datatype c_datatype;
  int size;
  const char * b_ptr;
  emxArray_uint8_T *data0;
  static const char cv1[8] = { 'M', 'P', 'I', '_', 'C', 'o', 'm', 'm' };

  MPI_Comm b_comm;
  MPI_Request arg;
  static const char t0_type[11] = { 'M', 'P', 'I', '_', 'R', 'e', 'q', 'u', 'e',
    's', 't' };

  char * c_ptr;
  unsigned char msg0[1024];
  short unnamed_idx_1;
  p = (datatype->type->size[1] == 12);
  if (p && (datatype->type->size[1] != 0)) {
    sizepe = 0;
    exitg1 = false;
    while ((!exitg1) && (sizepe < 12)) {
      if (!(datatype->type->data[sizepe] == cv[sizepe])) {
        p = false;
        exitg1 = true;
      } else {
        sizepe++;
      }
    }
  }

  b_p = (int)p;
  emxInit_char_T(&b_datatype, 2);
  if (!b_p) {
    i = b_datatype->size[0] * b_datatype->size[1];
    b_datatype->size[0] = 1;
    b_datatype->size[1] = datatype->type->size[1] + 1;
    emxEnsureCapacity_char_T(b_datatype, i);
    sizepe = datatype->type->size[1];
    for (i = 0; i < sizepe; i++) {
      b_datatype->data[i] = datatype->type->data[i];
    }

    b_datatype->data[datatype->type->size[1]] = '\x00';
    m2c_error(b_datatype);
  }

  c_datatype = m2c_castdata(datatype->data);
  MPI_Type_size(c_datatype, &size);
  if (ptr->nbytes - ptr->offset < count * size) {
    b_m2c_error();
  }

  b_ptr = *(const char **)(&ptr->data);
  if (ptr->offset != 0) {
    b_ptr = b_ptr + ptr->offset;
  }

  p = (datatype->type->size[1] == 12);
  if (p && (datatype->type->size[1] != 0)) {
    sizepe = 0;
    exitg1 = false;
    while ((!exitg1) && (sizepe < 12)) {
      if (!(datatype->type->data[sizepe] == cv[sizepe])) {
        p = false;
        exitg1 = true;
      } else {
        sizepe++;
      }
    }
  }

  b_p = (int)p;
  if (!b_p) {
    i = b_datatype->size[0] * b_datatype->size[1];
    b_datatype->size[0] = 1;
    b_datatype->size[1] = datatype->type->size[1] + 1;
    emxEnsureCapacity_char_T(b_datatype, i);
    sizepe = datatype->type->size[1];
    for (i = 0; i < sizepe; i++) {
      b_datatype->data[i] = datatype->type->data[i];
    }

    b_datatype->data[datatype->type->size[1]] = '\x00';
    m2c_error(b_datatype);
  }

  c_datatype = m2c_castdata(datatype->data);
  p = (comm->type->size[1] == 8);
  if (p && (comm->type->size[1] != 0)) {
    sizepe = 0;
    exitg1 = false;
    while ((!exitg1) && (sizepe < 8)) {
      if (!(comm->type->data[sizepe] == cv1[sizepe])) {
        p = false;
        exitg1 = true;
      } else {
        sizepe++;
      }
    }
  }

  b_p = (int)p;
  if (!b_p) {
    i = b_datatype->size[0] * b_datatype->size[1];
    b_datatype->size[0] = 1;
    b_datatype->size[1] = comm->type->size[1] + 1;
    emxEnsureCapacity_char_T(b_datatype, i);
    sizepe = comm->type->size[1];
    for (i = 0; i < sizepe; i++) {
      b_datatype->data[i] = comm->type->data[i];
    }

    b_datatype->data[comm->type->size[1]] = '\x00';
    c_m2c_error(b_datatype);
  }

  emxInit_uint8_T(&data0, 1);
  b_comm = b_m2c_castdata(comm->data);
  *info = MPI_Bsend_init(b_ptr, count, c_datatype, dest, tag, b_comm, &arg);
  sizepe = sizeof(MPI_Request);
  i = data0->size[0];
  data0->size[0] = sizepe;
  emxEnsureCapacity_uint8_T(data0, i);
  i = req->data->size[0];
  req->data->size[0] = sizepe;
  emxEnsureCapacity_uint8_T(req->data, i);
  for (i = 0; i < sizepe; i++) {
    req->data->data[i] = data0->data[i];
  }

  emxFree_uint8_T(&data0);
  i = req->type->size[0] * req->type->size[1];
  req->type->size[0] = 1;
  req->type->size[1] = 11;
  emxEnsureCapacity_char_T(req->type, i);
  for (i = 0; i < 11; i++) {
    req->type->data[i] = t0_type[i];
  }

  req->nitems = 1;
  c_ptr = (char *)(&arg);
  for (size = 0; size < sizepe; size++) {
    req->data->data[size] = *(c_ptr);
    c_ptr = c_ptr + 1;
  }

  if (*info != 0) {
    memset(&msg0[0], 0, 1024U * sizeof(unsigned char));
    c_ptr = (char *)(msg0);
    sizepe = 0;
    MPI_Error_string(*info, c_ptr, &sizepe);
    if (1 > sizepe) {
      unnamed_idx_1 = 0;
    } else {
      unnamed_idx_1 = (short)sizepe;
    }

    i = b_datatype->size[0] * b_datatype->size[1];
    b_datatype->size[0] = 1;
    b_datatype->size[1] = unnamed_idx_1;
    emxEnsureCapacity_char_T(b_datatype, i);
    sizepe = unnamed_idx_1;
    for (i = 0; i < sizepe; i++) {
      b_datatype->data[i] = (signed char)msg0[i];
    }

    d_m2c_error(b_datatype);
  }

  emxFree_char_T(&b_datatype);
  *toplevel = true;
}

void mpi_Bsend_init_initialize(void)
{
}

void mpi_Bsend_init_terminate(void)
{
}
