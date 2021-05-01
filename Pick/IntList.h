#ifndef IntList_
#define IntList_
#include <stdlib.h>

namespace IntList
{
    extern "C" {
        int *CreateIntList (int n);

        void SetNthInIntList (int * s, int n, int value);

        int GetNthInIntList (int * s,int n);

        void CopyIntList(int* la, int *lb);
        
        int *AddIntLists (int *l0, int *l1);

    }

    int * CopyIntList(int* l);
    
    int * HeadList(int* l1);

    int * TailList(int* l1, int n);

    int * HeadToIndex(int* shape, int *head);

    int *GetSizeFromShape(int * shape);

    bool IndexIsValid(int * shape, int * index);

    int IndexPosition(int * shape, int * index);

    int *PositionToIndex(int * size, int position);

    bool NextIndex(int * shape, int * index);

    int KernelIndexPosition(int * shape, int * kindex);

    int *PositionToKernelIndex(int * size, int position, int * kindex);

    bool NextKernelIndex(int * shape, int * kindex, int * kindexnext);
}

#endif
