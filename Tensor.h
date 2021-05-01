#include "IntList.h"
#include "Pick.h"

template <typename T>
class Tensor
{
    public:
        static T * CreateTensor (int * shape);
        static T * Shaffle(int * shape,int *pick,T *tensor);
        static T * Scatter(int * shapetr, int * shape, int * tr, T *u, T *tensor);
        static T * ScatterX(int * shapetr, int * shape, int ** xtr, T *u, T *tensor);
        
};

template <typename T>
T * Tensor<T>::CreateTensor (int * shape)
{
    T *t;
    int *size = GetSizeFromShape(shape);
    t = reinterpret_cast<T *>(malloc(size[1] * sizeof(t[0])));
    return t;
}

template <typename T>
T * Tensor<T>::Scatter(int * shapetr, int * shape, int * tr, T *u, T *tensor)
{
    int ndtr = shapetr[0];
    int nd0 = shapetr[ndtr];
    int nd = shape[0];
    int *index = CreateIntList(nd); 
    int *size = GetSizeFromShape(shapetr);
    int n=0;
    int m=0;
    while(n<size[1])
    {
        for(int i = 0;i<nd0;i++)
        {
            index[i] = tr[n+i];

        }
        int ps = IndexPosition(shape, index);
        int md = nd-nd0;
        for(int j=0;j<md;j++)
        {
            tensor[ps+j] = u[m+j];

        }
        
        n = n +nd;
        m = m + md;
    }
    
    return tensor;
}

template <typename T>
T * Tensor<T>::ScatterX(int * shapetr, int * shape, int ** xtr, T *u, T *tensor)
{
    
    int nd = shape[0];
    int *shapeu = HeadList(shapetr);
    int *index = CreateIntList(nd-1); 

    do{
        int ps0 = IndexPosition(shapeu, index);
        int *index1 = XTransform(int * shapextr,  int ** xtr, int *index);
        int ps1 = IndexPosition(shape, index1);
        tensor[ps1] = u[ps0];

    }while(NextIndex(shapeu, index))
    return tensor;
}

template <typename T>
T * Tensor<T>::Shaffle(int * shape,int *pick,T *tensor)
{
    int nd = shape[0];
    if(nd != pick[0]) return nullptr;
    int *index = CreateIntList(nd); 
    int *size = GetSizeFromShape(shape);
    int *newShape = ToPick(pick, shape);
    T *newTensor;
    newTensor = reinterpret_cast<T *>(malloc(size[1] * sizeof(newTensor[0])));
    
    do{
        int ps = IndexPosition(shape, index);
        int *newindex = ToPick(pick, index);
        int newps = IndexPosition(newShape, newindex);
        newTensor[ps1] = u[ps0];

    }while(NextIndex(shapeu, index))
    
    return newTensor;
}