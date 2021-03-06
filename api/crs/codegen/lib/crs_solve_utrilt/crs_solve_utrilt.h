#ifndef CRS_SOLVE_UTRILT_H
#define CRS_SOLVE_UTRILT_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "crs_solve_utrilt_types.h"

extern void crs_solve_utrilt(const CRS_Matrix *L, emxArray_real_T *b);
extern void crs_solve_utrilt_3args(const CRS_Matrix *L, emxArray_real_T *b, int
  offset);
extern void crs_solve_utrilt_initialize(void);
extern void crs_solve_utrilt_terminate(void);

#endif
