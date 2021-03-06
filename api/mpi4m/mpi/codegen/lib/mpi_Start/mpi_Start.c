#include "mpi_Start.h"
#include "m2c.h"
#include "mpi.h"

static void b_m2c_error(int varargin_3);
static MPI_Request m2c_castdata(const emxArray_uint8_T *data);
static void m2c_error(const emxArray_char_T *varargin_3);
static void b_m2c_error(int varargin_3)
{
  M2C_error("MPI:RuntimeError", "MPI_Start error code %d\n", varargin_3);
}

static MPI_Request m2c_castdata(const emxArray_uint8_T *data)
{
  return *(MPI_Request*)(&data->data[0]);
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
            "Incorrect data type %s. Expected MPI_Request.\n",
            &b_varargin_3->data[0]);
  emxFree_char_T(&b_varargin_3);
}

void mpi_Start(const M2C_OpaqueType *req, int *info, boolean_T *toplevel)
{
  boolean_T p;
  int k;
  boolean_T b_p;
  boolean_T exitg1;
  emxArray_char_T *b_req;
  MPI_Request t_req;
  int i;
  static const char cv[11] = { 'M', 'P', 'I', '_', 'R', 'e', 'q', 'u', 'e', 's',
    't' };

  p = (req->type->size[1] == 11);
  if (p && (req->type->size[1] != 0)) {
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 11)) {
      if (!(req->type->data[k] == cv[k])) {
        p = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  b_p = (int)p;
  if (!b_p) {
    emxInit_char_T(&b_req, 2);
    i = b_req->size[0] * b_req->size[1];
    b_req->size[0] = 1;
    b_req->size[1] = req->type->size[1] + 1;
    emxEnsureCapacity_char_T(b_req, i);
    k = req->type->size[1];
    for (i = 0; i < k; i++) {
      b_req->data[i] = req->type->data[i];
    }

    b_req->data[req->type->size[1]] = '\x00';
    m2c_error(b_req);
    emxFree_char_T(&b_req);
  }

  t_req = m2c_castdata(req->data);
  *info = MPI_Start(&t_req);
  *toplevel = true;
  if (*info != 0) {
    b_m2c_error(*info);
  }
}

void mpi_Start_initialize(void)
{
}

void mpi_Start_terminate(void)
{
}
