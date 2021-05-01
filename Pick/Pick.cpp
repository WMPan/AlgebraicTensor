#include <stdlib.h>
#include "IntList.h"
#include "Slice.h"
#include <algorithm>

using namespace std;
using namespace IntList;
using namespace Slice;
namespace Pick
{
    int *ToPick(int *pick, int *intList)
    {
        int np = pick[0];
        int *picked = CreateIntList(np);
        for(int i=1;i<=np;i++)
        {
            picked[i]=intList[pick[i]+1];
        }
        return picked;

    }

    void ToPickInKernel(int *pick, int *list, int* picked)
    {
        int np = pick[0];
        for(int i=0;i<np;i++)
        {
            picked[i]=list[pick[i]];
        }
        

    }

    void ToPick2InKernel(int *pick, int n0, int n1, int *list0, int *list1, int* picked)
    {
        int np = pick[0];
        for(int i=0;i<np;i++)
        {
            int n = pick[i];
            if(n>=n0) 
            {
                int m = n-n0;
                picked[n]=list1[m];

            }
            else{
                picked[i]=list0[n];
            }
            
        }
    }

    int *Transform(int * shapetr, int * tr, int *index0)
    {
        int ndtr = shapetr[0];
        int ndout = shapetr[ndtr];
        int *index = CreateIntList(ndout);
        for(int i = 1;i<ndtr;i++)
        {
            index[i] = index0[i];
        }
        index[ndtr] = 0;
        int ps = IndexPosition(shapetr, index);
        for(int j=1;j<=ndout;j++)
        {
            index0[j] = tr[ps+j];

        }
        return index;

    }

    void TransformInKernel(int * shapein, int ndout, int * tr, int *index0, int *index)
    {
        int ndin = shapein[0];
        int ps0 = KernelIndexPosition(shapein, index0);
        int ps = ps0*ndout;
        for(int j=0;j<ndout;j++)
        {
            index[j] = tr[ps+j];

        }
    }

    int *MinShapeOfTransform(int * shapetr, int * tr)
    {
        int ndtr = shapetr[0];
        int ndout = shapetr[ndtr];
        int *index0 = CreateIntList(ndtr);
        int *minShape = CreateIntList(ndout);
        int n=0;
        int *size = GetSizeFromShape(shapetr);
        int s = size[1];
        while(n<s)
        {
            for(int i = 0;i<ndout;i++)
            {
                minShape[i+1] = max(minShape[i+1],tr[n+i]);
            }
            n = n + ndout;

        }
        
        return minShape;

    }


    int *XTransform(int * shapextr,  int ** xtr, int *index)
    {
        int *tr = xtr[0];
        int *pick0 = xtr[1];
        int *pick1 = xtr[2];
        int *pick2 = xtr[3];
        
        int *l0 = ToPick(pick0, index);
        int *s0 = ToPick(pick0, shapextr);
        int *l1 = ToPick(pick1, index);
        int *l01 = Transform(s0,tr,l0);
        int *l2 = AddIntLists(l01,l1);
        int *l3 = ToPick(pick2, l2);

        return l3;

    }

    int *XTransformInKernel(int * shape0,  int ** xtr, int tr_out, int *kernelindex, 
        int *kindex0, int *kindex1,
        int *kindex2,int *kindex3)
    {
        int *tr = xtr[0];
        int *pick0 = xtr[1];
        int *pick1 = xtr[2];
        int *pick2 = xtr[3];
        
        ToPickInKernel(pick0, kernelindex, kindex0);
        ToPickInKernel(pick1, kernelindex, kindex1);
        TransformInKernel(shape0,tr_out,tr,kindex0,kindex2);
        ToPick2InKernel(pick2, tr_out, pick1[0], kindex2, kindex1, kindex3);
        return kindex3;

    }
    
    int *SetTransformer(int *T, int *shape, int *index0, int *index1)
    {
        int nd = shape[0] + 1;
        int *index = CreateIntList(nd);
        for(int i=1;i<nd;i++)
        {
            index[i]=index0[i];
        }
        index[nd] = 0;
        int ps = IndexPosition(shape,index);
        int l = index1[0];
        for(int j=0;j<l;j++)
        {
            T[ps+j] = index1[j+1];
        }
        return T;
    }




}