MatrixMarketToPETSc
===================

MatrixMarket file converter to PETSc bin format is a small software written in C and PETSc library to convert, as its name suggest, Matrix Market files to PETSc binary format. 
This is extremely useful if you have to benchmark your codes written in PETSc using standard matrices coming from [Matrix Market] [1] or the [University of Florida Sparse Matrix Collection] [2]


### Requirements :

Working [PETSc] [3] installation


### Installation :

Nothing much to do but : **make**

### How to use :

./converter -matrix\_file matrix\_market_file.mtx

or 

./converter -vector\_file matrix\_market\_vector\_file.mtx (typically ends with _b.mtx)

or 

./converter -matrix\_file matrix\_market\_file.mtx -vector\_file matrix_market_vector_file.mtx


The results will be placed in separate PETSc binary files (in tar.gz)

[1]:http://math.nist.gov/MatrixMarket/
[2]:http://www.cise.ufl.edu/research/sparse/matrices/
[3]:http://www.mcs.anl.gov/petsc/
