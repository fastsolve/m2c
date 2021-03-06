#ifndef MPI_ABORT_H
#define MPI_ABORT_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "mpi_Abort_types.h"

extern int mpi_Abort(const M2C_OpaqueType *comm, int errorcode);
extern void mpi_Abort_initialize(void);
extern void mpi_Abort_terminate(void);

#endif
