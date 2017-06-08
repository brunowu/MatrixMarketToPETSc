MatrixMarketToPETSc
===================

MatrixMarket file converter to PETSc bin format is a small software written in C and PETSc library to convert, as its name suggest, Matrix Market files to PETSc binary format. 
This is extremely useful if you have to benchmark your codes written in PETSc using standard matrices coming from [Matrix Market] [1] or the [University of Florida Sparse Matrix Collection] [2]


### Requirements :

Working [PETSc] [3] installation (I'm using petsc-3.3-p2)


### Installation :

Nothing much to do but : **make**

### How to use :

./converter -matrix\_file matrix\_market_file.mtx

or 

./converter -vector\_file matrix\_market\_vector\_file.mtx (typically ends with _b.mtx)

or 

./converter -matrix\_file matrix\_market\_file.mtx -vector\_file matrix_market_vector_file.mtx


The results will be placed in separate PETSc binary files (in tar.gz)

### Further notes :

This software is released using GPL. Please feel free to contact me for any suggestion or improvements. Thanks !


###GPL & Copyright :

Copyright 2012 Pierre-Yves Aquilanti

This file is part of MatrixMarketToPETSc.

MatrixMarketToPETSc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MatrixMarketToPETSc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MatrixMarketToPETSc.  If not, see <http://www.gnu.org/licenses/>.

[1]:http://math.nist.gov/MatrixMarket/
[2]:http://www.cise.ufl.edu/research/sparse/matrices/
[3]:http://www.mcs.anl.gov/petsc/