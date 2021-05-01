#include <stdlib.h>
#include "IntList.h"
namespace IntList
{
    extern "C" {
        int *CreateIntList (int n)
        {
            int *l_Int;
            l_Int = reinterpret_cast<int *>(malloc((n+1)* sizeof(l_Int[0])));
            l_Int[0] = n;
            return l_Int;
        }

        int *AddIntLists (int *l0, int *l1)
        {
            int nd0 = l0[0];
            int nd = nd0 + l1[0];
            int *l_Int = CreateIntList (nd);
            for(int i=1;i<=l0[0];i++)
            {
                l_Int [i] = l0[i];
            }
            for(int j= 1;j<=l1[0];j++)
            {
                l_Int [nd0+j] = l1[j];
            }
            return l_Int;
        }

        void SetNthInIntList (int * s, int n, int value)
        {
            using namespace std;
            s[n+1] = value;
        }

        int GetNthInIntList (int * s,int n)
        {
            using namespace std;
            return s[n+1] ;
        }

        

        void CopyIntList(int* la, int *lb)
        {
            for(int i=1;i<=la[0];i++)
            {
                lb[i] = la[i];
            }

        }


    }

    int * CopyIntList(int* l1)
    {
        int *l2 = CreateIntList(l1[0]);
        CopyIntList(l1,l2);
        return l2;
    }

    int * HeadList(int* l1)
    {
        int *l2 = CreateIntList(l1[0]-1);
        for(int i=1;i<=l2[0];i++)
        {
            l2[i] = l1[i];
        }
        return l2;
    }

    int * HeadList(int* l1,int n)
    {
        int *head = CreateIntList(n);
        for(int i=1;i<=n;i++)
        {
            head[i] = l1[i];
        }
        return head;
    }

    int * TailList(int* l1,int n)
    {
        int *tail = CreateIntList(n);
        int nd = l1[0];
        for(int i=1;i<=n;i++)
        {
            tail[i] = l1[nd-n+i];
        }
        return tail;
    }

    int * HeadToIndex(int* shape, int *head)
    {
        int nd = shape[0];
        int *id = CreateIntList (nd);
        
        for (int i = 1; i <= head[0]; i++) {
            
            id[i] = head[i];
        }
        return id;
    }

    int *GetSizeFromShape(int * shape)
    {
        int nd = shape[0];
        int *s = CreateIntList (nd);
        
        s[nd] = shape[nd];
        for (int i = nd -1; i > 0; i--) {
            
            s[i] = shape[i]*s[i+1];
        }
        return s;
    }

    bool IndexIsValid(int * shape, int * index)
    {
        int nd = shape[0];
        if(nd != index[0]) return false;
        for (int i = 1; i <= nd; i++) {
            if(index[i]<0 || index[i] > shape[i])
            {
                return false;
            }
        }
        return true;
    }

    int IndexPosition(int * shape, int * index)
    {
        int i,n,id;
        int nd = shape[0];
        if(nd>0)
        {
            n=shape[nd];
            id = index[nd];
        }
        for (i = nd-1; i > 0; i--) {
            if(index[i] > shape[i])
            {
                throw;
            }
            id = index[i]*n + id;
            n = shape[i]*n;
        }
    }

    int *PositionToIndex(int * size, int position)
    {
        int nd = size[0];
        int *index = CreateIntList (nd);
        if(nd==1)
        {
            index[1] = position;
        }
        else{
            int left = position;
            for(int i=1;i<nd;i++)
            {
                index[i] = left/size[i+1];
                left = left - index[i]*size[i+1];
            }
            index[nd] = left;
        }
        return index;

    }
    bool NextIndex(int * shape, int * index)    
    {
        int nd = shape[0];
        
        for (int i = nd; i > 0; i--) {
            int m = index[i] +1;
            if(m = shape[i])
            {
                index[i]=0;
                if(i==1) return false;
            }
            else{
                index[i] = m;
                return true;
            }
        }
    }

    int KernelIndexPosition(int * shape, int * kindex)
    {
        int i,n,id;
        int nd = shape[0];
        if(nd>0)
        {
            n=shape[nd];
            id = kindex[nd-1];
        }
        for (i = nd-1; i > 0; i--) {
            id = kindex[i-1]*n + id;
            n = shape[i]*n;
        }
    }

    int *PositionToIndex(int * size, int position, int * kindex)
    {
        int nd = size[0];
        if(nd==1)
        {
            kindex[0] = position;
        }
        else{
            int left = position;
            for(int i=1;i<nd-1;i++)
            {
                kindex[i-1] = left/size[i+1];
                left = left - kindex[i-1]*size[i+1];
            }
            kindex[nd-1] = left;
        }
        return kindex;

    }
    bool NextKernelIndex(int * shape, int * kindex, int * kindexnext)
    {
        int nd = shape[0];
        bool setted = false;
        for (int i = nd; i > 0; i--) {
            if(setted)
            {
                kindexnext[i-1] = kindex[i-1];
            }
            else{
                int m = kindex[i-1] +1;
            
                if(m = shape[i])
                {
                    kindexnext[i-1]=0;
                    if(i==1) return false;
                }
                else{
                    kindexnext[i-1] = m;
                    setted = true;
                }

            }
            
        }
    }
}