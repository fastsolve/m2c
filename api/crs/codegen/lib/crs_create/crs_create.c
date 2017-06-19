#include "crs_create.h"
#include "m2c.h"

static void crs_sort(const emxArray_int32_T *row_ptr, emxArray_int32_T *col_ind,
                     emxArray_real_T *val);
static void crs_sort(const emxArray_int32_T *row_ptr, emxArray_int32_T *col_ind,
                     emxArray_real_T *val)
{
  int i2;
  int i;
  emxArray_real_T *buf_val;
  emxArray_int32_T *buf_indx;
  boolean_T ascend;
  int j;
  boolean_T exitg1;
  int n;
  unsigned int ind;
  int l;
  int exitg2;
  boolean_T guard1 = false;
  int r0;
  double t0;
  int exitg3;
  int b_i;
  boolean_T guard2 = false;
  i2 = row_ptr->size[0] - 1;
  i = 1;
  emxInit_real_T(&buf_val, 1);
  emxInit_int32_T(&buf_indx, 1);
  while (i <= i2) {
    ascend = true;
    j = row_ptr->data[i - 1];
    exitg1 = false;
    while ((!exitg1) && (j + 1 <= row_ptr->data[i] - 1)) {
      if (col_ind->data[j] < col_ind->data[j - 1]) {
        ascend = false;
        exitg1 = true;
      } else {
        j++;
      }
    }

    if (!ascend) {
      j = buf_indx->size[0];
      buf_indx->size[0] = row_ptr->data[i] - row_ptr->data[i - 1];
      emxEnsureCapacity((emxArray__common *)buf_indx, j, sizeof(int));
      n = row_ptr->data[i] - row_ptr->data[i - 1];
      for (j = 0; j < n; j++) {
        buf_indx->data[j] = 0;
      }

      j = buf_val->size[0];
      buf_val->size[0] = row_ptr->data[i] - row_ptr->data[i - 1];
      emxEnsureCapacity((emxArray__common *)buf_val, j, sizeof(double));
      n = row_ptr->data[i] - row_ptr->data[i - 1];
      for (j = 0; j < n; j++) {
        buf_val->data[j] = 0.0;
      }

      ind = 1U;
      for (j = row_ptr->data[i - 1]; j < row_ptr->data[i]; j++) {
        buf_indx->data[(int)ind - 1] = col_ind->data[j - 1];
        buf_val->data[(int)ind - 1] = val->data[j - 1];
        ind++;
      }

      n = buf_indx->size[0];
      if (!(n <= 1)) {
        l = (int)((unsigned int)n >> 1U);
        do {
          exitg2 = 0;
          guard1 = false;
          if (l + 1 <= 1) {
            r0 = buf_indx->data[n - 1];
            t0 = buf_val->data[n - 1];
            buf_indx->data[n - 1] = buf_indx->data[0];
            buf_val->data[n - 1] = buf_val->data[0];
            n--;
            if (n == 1) {
              exitg2 = 1;
            } else {
              guard1 = true;
            }
          } else {
            l--;
            r0 = buf_indx->data[l];
            t0 = buf_val->data[l];
            guard1 = true;
          }

          if (guard1) {
            j = l;
            do {
              exitg3 = 0;
              b_i = j;
              j = ((j + 1) << 1) - 1;
              ascend = false;
              guard2 = false;
              if (j + 1 >= n) {
                if (j + 1 == n) {
                  ascend = true;
                  guard2 = true;
                } else if (j + 1 > n) {
                  exitg3 = 1;
                } else {
                  guard2 = true;
                }
              } else {
                guard2 = true;
              }

              if (guard2) {
                if ((!ascend) && (buf_indx->data[j] < buf_indx->data[j + 1])) {
                  j++;
                }

                if (r0 >= buf_indx->data[j]) {
                  exitg3 = 1;
                } else {
                  buf_indx->data[b_i] = buf_indx->data[j];
                  buf_val->data[b_i] = buf_val->data[j];
                }
              }
            } while (exitg3 == 0);

            buf_indx->data[b_i] = r0;
            buf_val->data[b_i] = t0;
          }
        } while (exitg2 == 0);

        buf_indx->data[0] = r0;
        buf_val->data[0] = t0;
      }

      ind = 1U;
      for (j = row_ptr->data[i - 1]; j < row_ptr->data[i]; j++) {
        col_ind->data[j - 1] = buf_indx->data[(int)ind - 1];
        val->data[j - 1] = buf_val->data[(int)ind - 1];
        ind++;
      }
    }

    i++;
  }

  emxFree_int32_T(&buf_indx);
  emxFree_real_T(&buf_val);
}

void crs_create(const emxArray_int32_T *rows, const emxArray_int32_T *cols,
                const emxArray_real_T *vs, struct0_T *A)
{
  emxArray_int32_T *b_A;
  int mtmp;
  int i0;
  int j;
  int b_mtmp;
  int unnamed_idx_0;
  boolean_T ascend;
  boolean_T exitg1;
  emxInit_int32_T(&b_A, 1);
  if ((rows->size[0] == 1) && (cols->size[0] == 1)) {
    i0 = A->row_ptr->size[0];
    A->row_ptr->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)A->row_ptr, i0, sizeof(int));
    i0 = A->col_ind->size[0];
    A->col_ind->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)A->col_ind, i0, sizeof(int));
    i0 = A->val->size[0];
    A->val->size[0] = vs->size[0];
    emxEnsureCapacity((emxArray__common *)A->val, i0, sizeof(double));
    j = vs->size[0];
    for (i0 = 0; i0 < j; i0++) {
      A->val->data[i0] = vs->data[i0];
    }

    A->nrows = rows->data[0];
    A->ncols = cols->data[0];
  } else {
    mtmp = rows->data[0];
    if (rows->size[0] > 1) {
      for (j = 1; j + 1 <= rows->size[0]; j++) {
        if (rows->data[j] > mtmp) {
          mtmp = rows->data[j];
        }
      }
    }

    b_mtmp = cols->data[0];
    if (cols->size[0] > 1) {
      for (j = 1; j + 1 <= cols->size[0]; j++) {
        if (cols->data[j] > b_mtmp) {
          b_mtmp = cols->data[j];
        }
      }
    }

    j = cols->size[0];
    unnamed_idx_0 = cols->size[0];
    i0 = A->row_ptr->size[0];
    A->row_ptr->size[0] = mtmp + 1;
    emxEnsureCapacity((emxArray__common *)A->row_ptr, i0, sizeof(int));
    for (i0 = 0; i0 <= mtmp; i0++) {
      A->row_ptr->data[i0] = 0;
    }

    i0 = A->col_ind->size[0];
    A->col_ind->size[0] = j;
    emxEnsureCapacity((emxArray__common *)A->col_ind, i0, sizeof(int));
    for (i0 = 0; i0 < j; i0++) {
      A->col_ind->data[i0] = 0;
    }

    i0 = A->val->size[0];
    A->val->size[0] = unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)A->val, i0, sizeof(double));
    for (i0 = 0; i0 < unnamed_idx_0; i0++) {
      A->val->data[i0] = 0.0;
    }

    A->nrows = mtmp;
    A->ncols = b_mtmp;
    i0 = rows->size[0];
    for (b_mtmp = 0; b_mtmp + 1 <= i0; b_mtmp++) {
      A->row_ptr->data[rows->data[b_mtmp]]++;
    }

    A->row_ptr->data[0] = 1;
    for (b_mtmp = 1; b_mtmp <= mtmp; b_mtmp++) {
      A->row_ptr->data[b_mtmp] += A->row_ptr->data[b_mtmp - 1];
    }

    ascend = true;
    b_mtmp = 0;
    exitg1 = false;
    while ((!exitg1) && (b_mtmp <= rows->size[0] - 2)) {
      if (rows->data[1 + b_mtmp] < rows->data[b_mtmp]) {
        ascend = false;
        exitg1 = true;
      } else {
        b_mtmp++;
      }
    }

    if (ascend) {
      i0 = A->col_ind->size[0];
      A->col_ind->size[0] = cols->size[0];
      emxEnsureCapacity((emxArray__common *)A->col_ind, i0, sizeof(int));
      j = cols->size[0];
      for (i0 = 0; i0 < j; i0++) {
        A->col_ind->data[i0] = cols->data[i0];
      }

      i0 = A->val->size[0];
      A->val->size[0] = vs->size[0];
      emxEnsureCapacity((emxArray__common *)A->val, i0, sizeof(double));
      j = vs->size[0];
      for (i0 = 0; i0 < j; i0++) {
        A->val->data[i0] = vs->data[i0];
      }
    } else {
      i0 = A->col_ind->size[0];
      A->col_ind->size[0] = cols->size[0];
      emxEnsureCapacity((emxArray__common *)A->col_ind, i0, sizeof(int));
      i0 = A->val->size[0];
      A->val->size[0] = cols->size[0];
      emxEnsureCapacity((emxArray__common *)A->val, i0, sizeof(double));
      for (b_mtmp = 0; b_mtmp < rows->size[0]; b_mtmp++) {
        j = A->row_ptr->data[rows->data[b_mtmp] - 1];
        A->val->data[A->row_ptr->data[rows->data[b_mtmp] - 1] - 1] = vs->
          data[b_mtmp];
        A->col_ind->data[j - 1] = cols->data[b_mtmp];
        A->row_ptr->data[rows->data[b_mtmp] - 1]++;
      }

      j = A->row_ptr->size[0] - 2;
      i0 = (int)((2.0 + (-1.0 - (double)A->row_ptr->size[0])) / -1.0);
      for (b_mtmp = 0; b_mtmp < i0; b_mtmp++) {
        unnamed_idx_0 = j - b_mtmp;
        A->row_ptr->data[unnamed_idx_0 + 1] = A->row_ptr->data[unnamed_idx_0];
      }

      A->row_ptr->data[0] = 1;
    }

    i0 = b_A->size[0];
    b_A->size[0] = A->row_ptr->size[0];
    emxEnsureCapacity((emxArray__common *)b_A, i0, sizeof(int));
    j = A->row_ptr->size[0];
    for (i0 = 0; i0 < j; i0++) {
      b_A->data[i0] = A->row_ptr->data[i0];
    }

    crs_sort(b_A, A->col_ind, A->val);
  }

  emxFree_int32_T(&b_A);
}

void crs_create0(int ni, int nj, struct1_T *A)
{
  A->nrows = ni;
  A->ncols = nj;
}

void crs_create1(const emxArray_int32_T *is, const emxArray_int32_T *js, const
                 emxArray_real_T *vs, int ni, int nj, struct0_T *A)
{
  unsigned int unnamed_idx_0;
  unsigned int b_unnamed_idx_0;
  int i1;
  int j;
  int i;
  boolean_T ascend;
  boolean_T exitg1;
  emxArray_int32_T *b_A;
  int b_i;
  unnamed_idx_0 = (unsigned int)js->size[0];
  b_unnamed_idx_0 = (unsigned int)js->size[0];
  i1 = A->row_ptr->size[0];
  A->row_ptr->size[0] = ni + 1;
  emxEnsureCapacity((emxArray__common *)A->row_ptr, i1, sizeof(int));
  for (i1 = 0; i1 <= ni; i1++) {
    A->row_ptr->data[i1] = 0;
  }

  i1 = A->col_ind->size[0];
  A->col_ind->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)A->col_ind, i1, sizeof(int));
  j = (int)unnamed_idx_0;
  for (i1 = 0; i1 < j; i1++) {
    A->col_ind->data[i1] = 0;
  }

  i1 = A->val->size[0];
  A->val->size[0] = (int)b_unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)A->val, i1, sizeof(double));
  j = (int)b_unnamed_idx_0;
  for (i1 = 0; i1 < j; i1++) {
    A->val->data[i1] = 0.0;
  }

  A->nrows = ni;
  A->ncols = nj;
  i1 = is->size[0];
  for (i = 0; i + 1 <= i1; i++) {
    A->row_ptr->data[is->data[i]]++;
  }

  A->row_ptr->data[0] = 1;
  for (i = 1; i <= ni; i++) {
    A->row_ptr->data[i] += A->row_ptr->data[i - 1];
  }

  ascend = true;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i <= is->size[0] - 2)) {
    if (is->data[1 + i] < is->data[i]) {
      ascend = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (ascend) {
    i1 = A->col_ind->size[0];
    A->col_ind->size[0] = js->size[0];
    emxEnsureCapacity((emxArray__common *)A->col_ind, i1, sizeof(int));
    j = js->size[0];
    for (i1 = 0; i1 < j; i1++) {
      A->col_ind->data[i1] = js->data[i1];
    }

    i1 = A->val->size[0];
    A->val->size[0] = vs->size[0];
    emxEnsureCapacity((emxArray__common *)A->val, i1, sizeof(double));
    j = vs->size[0];
    for (i1 = 0; i1 < j; i1++) {
      A->val->data[i1] = vs->data[i1];
    }
  } else {
    i1 = A->col_ind->size[0];
    A->col_ind->size[0] = js->size[0];
    emxEnsureCapacity((emxArray__common *)A->col_ind, i1, sizeof(int));
    i1 = A->val->size[0];
    A->val->size[0] = js->size[0];
    emxEnsureCapacity((emxArray__common *)A->val, i1, sizeof(double));
    for (i = 0; i < is->size[0]; i++) {
      j = A->row_ptr->data[is->data[i] - 1];
      A->val->data[A->row_ptr->data[is->data[i] - 1] - 1] = vs->data[i];
      A->col_ind->data[j - 1] = js->data[i];
      A->row_ptr->data[is->data[i] - 1]++;
    }

    j = A->row_ptr->size[0];
    i1 = (int)((2.0 + (-1.0 - (double)A->row_ptr->size[0])) / -1.0);
    for (i = 1; i - 1 < i1; i++) {
      b_i = j - i;
      A->row_ptr->data[b_i] = A->row_ptr->data[b_i - 1];
    }

    A->row_ptr->data[0] = 1;
  }

  emxInit_int32_T(&b_A, 1);
  i1 = b_A->size[0];
  b_A->size[0] = A->row_ptr->size[0];
  emxEnsureCapacity((emxArray__common *)b_A, i1, sizeof(int));
  j = A->row_ptr->size[0];
  for (i1 = 0; i1 < j; i1++) {
    b_A->data[i1] = A->row_ptr->data[i1];
  }

  crs_sort(b_A, A->col_ind, A->val);
  emxFree_int32_T(&b_A);
}

void crs_create_initialize(void)
{
}

void crs_create_terminate(void)
{
}