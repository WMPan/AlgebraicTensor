# AlgebraicTensor
t is about A standard way to represent sparse tensor which is inspired by real word APIs in popular DL Frameworks.
It is also about An approach to use sparse data in GPU, TPU and other AI accelerators. That is a theory about how we can use sparse data parallelly in AI accelerators.
# ScatterX
Currently, There are two Ways of Storing a Sparse Tensor in DL Frameworks , such as TensorFlow and pyTorch . The first way is to Use an Index List and a Value List (like sparse matrix), and the second way is to Use an index Tensor and a Value Tensor as used in scatter APIs of TensorFlow and pyTorch.

What is the problem? First, Current scattering APIs really provide a kind of sparse tensor data structure that is different than sparse matrix. However, The scattering APIs of different DL frameworks are not compatible with each other. Both cannot efficiently mock the behavior of each other. Second, Sparsely stored matrixes or tensors are difficult to use the hardware features of machine learning accelerators.
So, there needs a theory to address the sparse tensor representation problem and how they are used in AI accelerators as GPUs and TPUs.

Let us see An Example of My Approach.

Firstly, let’s see a tensor.
![image](https://user-images.githubusercontent.com/55385310/132236159-cc74d1dd-3c3d-4519-b865-a8fddade6007.png)

We visualize a tensor as nested rectangles, with each box in the innermost layer representing a number.
![image](https://user-images.githubusercontent.com/55385310/132236251-0083a6f3-1d9b-42de-9377-cd92801b6a99.png)

We add index numbers to the rectangles in the first three dimensions. We set numbers for 6 boxes, and then we get a sparse tensor.
![image](https://user-images.githubusercontent.com/55385310/132236281-8fb2e4ad-e311-458c-b590-160e642f2446.png)

This is an Ordinary Way to Represent the Sparse Tensor. Here is an index list and a value list.
![image](https://user-images.githubusercontent.com/55385310/132236379-2e2f89ed-c6ec-4637-88a7-3a162304b29b.png)

My Solution for Representing the Sparse Tensor is to use three picks and two tensors. A pick is a one-dimensional tensor which is used to select dimensions. The X-variator tensor is used to map indices from value tensor to the original tensor.
![image](https://user-images.githubusercontent.com/55385310/132236442-f45fd9c4-e33b-48ff-8e40-95b29647e2b2.png)

We need an algorithm to restore the original tensor.
![image](https://user-images.githubusercontent.com/55385310/132236480-cb72a560-660b-4591-b92e-afcf2acb4dde.png)

This is the Index Map Formula, the red I will be an index of any value tensor data.
![image](https://user-images.githubusercontent.com/55385310/132236532-009242a4-2bcf-4db1-bd8b-cf38bd3daff0.png)

For example, 1 has the index (0,0) in value tensor. The formula will compute its original index as (0,0,2,4).
![image](https://user-images.githubusercontent.com/55385310/132236581-778c2a2a-761c-4fe9-9e9c-93c02980fd28.png)

For another example, 5 has the index (5,0) in value tensor. The formula will compute its original index as (2,0,0,4).
![image](https://user-images.githubusercontent.com/55385310/132236645-46f0d6cd-4049-4315-93bd-e6988334bfea.png)

The advantages of my method are in three aspects. Firstly, Index tensor has less data than index list of ordinary way, i.e., in this example the indices data size is 12 vs 24. Secondly, It has a more comprehensive representation capability than the current scatter APIs, i.e., TensorFlow and pyTorch scatter APIs. Thirdly, Indices and values are stored in tensors, which facilitates the use of sparse tensors in AI accelerators such as GPU and TPU.

Once a sparse tensor is expressed with my method, we can measure its sparsity.
![image](https://user-images.githubusercontent.com/55385310/132236683-cf602402-b42c-4f4c-9e22-a78be0421295.png)

A theorem:
![image](https://user-images.githubusercontent.com/55385310/132236764-8c69dce8-d5a7-4afb-ac5b-dd2386c170a1.png)

Now I can summarize my solution. X-sparse tensor is a standard way to represent sparse tensor. And the theory is inspired by real word APIs in popular DL Frameworks.
X-sparse tensor opens a way to use sparse data in GPU, TPU and other AI accelerators.
Significant influence on the future: We can express DL theory on tensors instead of matrix operations. Please look forward to our work of algebraic tensor theory.
