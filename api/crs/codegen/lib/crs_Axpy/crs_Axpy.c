#include "crs_Axpy.h"
#include "omp.h"
#include "m2c.h"

static void b_crs_Axpy_kernel(const emxArray_int32_T *row_ptr, const
  emxArray_int32_T *col_ind, const emxArray_real_T *val, const emxArray_real_T
  *x, int x_m, emxArray_real_T *y, int b_m, int nrows, int nrhs);
static void crs_Axpy_kernel(const emxArray_int32_T *row_ptr, const
  emxArray_int32_T *col_ind, const emxArray_real_T *val, const emxArray_real_T
  *x, int x_m, emxArray_real_T *y, int b_m, int nrows, int nrhs, boolean_T
  varargin_1);
static void m2c_error(void);
static void m2c_warn(void);
static void b_crs_Axpy_kernel(const emxArray_int32_T *row_ptr, const
  emxArray_int32_T *col_ind, const emxArray_real_T *val, const emxArray_real_T
  *x, int x_m, emxArray_real_T *y, int b_m, int nrows, int nrhs)
{
  int xoffset;
  int boffset;
  int k;
  int i;
  double t;
  int j;
  xoffset = -1;
  boffset = -1;
  for (k = 1; k <= nrhs; k++) {
    for (i = 1; i <= nrows; i++) {
      t = y->data[boffset + i];
      for (j = row_ptr->data[i - 1]; j < row_ptr->data[i]; j++) {
        t += val->data[j - 1] * x->data[xoffset + col_ind->data[j - 1]];
      }

      y->data[boffset + i] = t;
    }

    xoffset += x_m;
    boffset += b_m;
  }
}

static void crs_Axpy_kernel(const emxArray_int32_T *row_ptr, const
  emxArray_int32_T *col_ind, const emxArray_real_T *val, const emxArray_real_T
  *x, int x_m, emxArray_real_T *y, int b_m, int nrows, int nrhs, boolean_T
  varargin_1)
{
  int istart;
  int iend;
  int b_remainder;
  int threadID;
  int chunk;
  int i;
  double t;
  int j;
  if (varargin_1) {
    iend = omp_get_num_threads();
    if (iend == 1) {
      istart = 0;
      iend = nrows;
    } else {
      threadID = omp_get_thread_num();
      chunk = nrows / iend;
      b_remainder = nrows - iend * chunk;
      if (b_remainder < threadID) {
        iend = b_remainder;
      } else {
        iend = threadID;
      }

      istart = threadID * chunk + iend;
      iend = (istart + chunk) + (threadID < b_remainder);
    }
  } else {
    istart = 0;
    iend = nrows;
  }

  b_remainder = -1;
  threadID = -1;
  for (chunk = 1; chunk <= nrhs; chunk++) {
    for (i = istart + 1; i <= iend; i++) {
      t = y->data[threadID + i];
      for (j = row_ptr->data[i - 1]; j < row_ptr->data[i]; j++) {
        t += val->data[j - 1] * x->data[b_remainder + col_ind->data[j - 1]];
      }

      y->data[threadID + i] = t;
    }

    b_remainder += x_m;
    threadID += b_m;
  }
}

static void m2c_error(void)
{
  M2C_error("crs_Axpy:BufferTooSmal", "Buffer space for output y is too small.");
}

static void m2c_warn(void)
{
  M2C_warn("crs_Axpy:NestedParallel",
           "You are trying to use nested parallel regions. Solution may be incorrect.");
}

void crs_Axpy(const struct0_T *A, const emxArray_real_T *x, emxArray_real_T *y,
              int nthreads)
{
  int n;
  int i0;
  if ((y->size[0] < A->nrows) || (y->size[1] < x->size[1])) {
    m2c_error();
  }

  n = omp_get_nested();
  if (!(n != 0)) {
    n = omp_get_num_threads();
    if ((n > 1) && (nthreads > 1)) {

#pragma omp master
      {
        m2c_warn();
      }

    }
  }

#pragma omp parallel default(shared) num_threads(nthreads)
  {
    n = omp_get_num_threads();
    i0 = y->size[0];
    crs_Axpy_kernel(A->row_ptr, A->col_ind, A->val, x, x->size[0], y, i0, A->nrows,
                    x->size[1], n > 1);
  }

}

void crs_Axpy_initialize(void)
{
}

void crs_Axpy_ser1(const struct0_T *A, const emxArray_real_T *x, emxArray_real_T
                   *b)
{
  int i1;
  if ((b->size[0] < A->nrows) || (b->size[1] < x->size[1])) {
    m2c_error();
  }

  i1 = b->size[0];
  b_crs_Axpy_kernel(A->row_ptr, A->col_ind, A->val, x, x->size[0], b, i1,
                    A->nrows, x->size[1]);
}

void crs_Axpy_terminate(void)
{
}