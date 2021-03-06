#include "ccs_solve_utril.h"

void ccs_solve_utril(const CCS_Matrix *L, emxArray_real_T *b)
{
  int n;
  int j;
  int i;
  int i1;
  int k;
  int i2;
  n = L->col_ptr->size[0];
  for (j = 0; j <= n - 2; j++) {
    i = L->col_ptr->data[j];
    i1 = L->col_ptr->data[j + 1] - 1;
    for (k = i; k <= i1; k++) {
      i2 = L->row_ind->data[k - 1] - 1;
      b->data[i2] -= L->val->data[k - 1] * b->data[j];
    }
  }
}

void ccs_solve_utril_3args(const CCS_Matrix *L, emxArray_real_T *b, int offset)
{
  int n;
  int j;
  int i;
  int i1;
  int k;
  int i2;
  n = L->col_ptr->size[0];
  for (j = 0; j <= n - 2; j++) {
    i = L->col_ptr->data[j];
    i1 = L->col_ptr->data[j + 1] - 1;
    for (k = i; k <= i1; k++) {
      i2 = (L->row_ind->data[k - 1] + offset) - 1;
      b->data[i2] -= L->val->data[k - 1] * b->data[j + offset];
    }
  }
}

void ccs_solve_utril_initialize(void)
{
}

void ccs_solve_utril_terminate(void)
{
}
