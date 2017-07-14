#ifndef MPI_IRECV_TYPES_H
#define MPI_IRECV_TYPES_H
#include "rtwtypes.h"

#ifndef struct_emxArray_char_T
#define struct_emxArray_char_T

struct emxArray_char_T
{
  char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

#ifndef typedef_emxArray_char_T
#define typedef_emxArray_char_T

typedef struct emxArray_char_T emxArray_char_T;

#endif

#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T

struct emxArray_uint8_T
{
  unsigned char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T

typedef struct emxArray_uint8_T emxArray_uint8_T;

#endif

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  unsigned long data;
  emxArray_char_T *type;
  int nbytes;
  int offset;
} struct0_T;

#endif

#ifndef typedef_struct1_T
#define typedef_struct1_T

typedef struct {
  emxArray_uint8_T *data;
  emxArray_char_T *type;
  int nitems;
} struct1_T;

#endif
#endif
