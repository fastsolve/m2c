#ifndef MPI_STARTALL_H
#define MPI_STARTALL_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "mpi_Startall_types.h"

extern void mpi_Startall(int count, const M2C_OpaqueType *reqs, int *info,
  boolean_T *toplevel);
extern void mpi_Startall_initialize(void);
extern void mpi_Startall_terminate(void);

#endif
