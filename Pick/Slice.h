#ifndef Slice_
#define Slice_
#include <stdlib.h>
#include "IntList.h"
using namespace IntList;
namespace Slice
{
    extern "C" {

        int **CreateIntListSlice(int* shape, int *a, int *b);

        int *GetSliceShape(int **slice);

    }

    int *GetSliceSize(int **slice);

    int *CombineIndexes(int * index1, int * index2);
}

#endif