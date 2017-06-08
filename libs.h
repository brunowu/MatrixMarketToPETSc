#ifndef _LIBS_H
#define _LIBS_H

#include "petscmat.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _MatrixInfo{
	int n;
	int m;
	int nnz;
} MatrixInfo;



PetscErrorCode MMTgetMatrix(char * fin, Mat * A, MatrixInfo * minfo);

PetscErrorCode MMTgetVector(char * fin, Vec * v, int * size);

PetscErrorCode MMTgetMatrixReal(char * fin, Mat * A, MatrixInfo * minfo);

PetscErrorCode MMTgetVectorReal(char * fin, Vec * v, int * size);




#endif


