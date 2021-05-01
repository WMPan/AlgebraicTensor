#include <stdlib.h>
#include "IntList.h"
#include "Slice.h"
using namespace IntList;
namespace Slice
{
    extern "C" {

        int **CreateIntListSlice(int* shape, int *a, int *b)
        {
            int **slice;
            slice = reinterpret_cast<int **>(malloc( 3* sizeof(slice[0])));
            slice[0] = shape;
            slice[1] = a;
            slice[2] = b;
        }

        int *GetSliceShape(int **slice)
        {
            int nd = slice[0][0];
            int *s = CreateIntList(nd);
            for(int i = 1;i<=nd;i++)
            {
                s[i] = slice[1][i] - slice[2][i];
            }
            return s;
        }

    }

    int *GetSliceSize(int **slice)
    {
        int *s = GetSliceShape(slice);
        int *size = GetSizeFromShape(s);
        delete s;
        return size;
    }


    int *CombineIndexes(int * index1, int * index2)
    {
        int nd = index1[0];
        int *id = CreateIntList(nd);
        for(int i = 1;i<=nd;i++)
        {
            id[i] = index1[i] + index2[i];
        }


    }
}
