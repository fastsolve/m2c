#ifndef MPI_RECV_INIT_H
#define MPI_RECV_INIT_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "mpi_Recv_init_types.h"

extern void mpi_Recv_init(const M2C_OpaquePtrType *ptr, int count, const
  M2C_OpaqueType *datatype, int dest, int tag, const M2C_OpaqueType *comm,
  M2C_OpaqueType *req, int *info, boolean_T *toplevel);
extern void mpi_Recv_init_initialize(void);
extern void mpi_Recv_init_terminate(void);

#endif
