#ifndef Pick_
#define Pick_

#include <stdlib.h>
#include "IntList.h"
#include "Slice.h"
namespace Pick
{
    int *ToPick(int *pick, int *index);
    void ToPickInKernel(int *pick, int *list, int* picked);
    int *MinShapeOfTransform(int * shapetr, int * tr);
    int *SetTransformer(int *T, int *shape, int *index0, int *index1);
    int *Transform(int * shapetr, int * tr, int *index0);
    int *XTransform(int * shapextr,  int ** xtr, int *index);
    void TransformInKernel(int * shapein, int ndout, int * tr, int *index0, int *index)
    
}

#endif