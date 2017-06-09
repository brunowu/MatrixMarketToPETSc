#include "main.h"


static const char help[] = "Matrix Market file to PETSc binary converter";

int main(int argc, char ** argv){
	PetscErrorCode ierr;
	Mat A;
	Vec b;
	PetscViewer    output_viewer;
	char           matrixInputFile[PETSC_MAX_PATH_LEN];
	char           vectorInputFile[PETSC_MAX_PATH_LEN];
	char           matrixOutputFile[PETSC_MAX_PATH_LEN];
	char           vectorOutputFile[PETSC_MAX_PATH_LEN];
  	PetscBool 		 flagMtx,flagVct;
  	PetscInt 			 sizen, cplex = PETSC_FALSE;
  	MatrixInfo		 minfo;
	

	/* Initalize PETSc */	
	PetscInitialize(&argc,&argv,(char *)0,help);
		
	/* Check how many processors are in use, one must use one node
		 in order to converte the matrix market file into PETSc binary format */
	MPI_Comm_size(PETSC_COMM_WORLD,&sizen);
	if (sizen > 1) SETERRQ(PETSC_COMM_WORLD,1,"Uniprocessor only\n");
	

	/* Check if we need to convert a matrix file */
	ierr=PetscOptionsGetString(NULL,PETSC_NULL,"-matrix_file",matrixInputFile,PETSC_MAX_PATH_LEN-1,&flagMtx);CHKERRQ(ierr);
	
	/* idem for the vector*/
	ierr=PetscOptionsGetString(NULL,PETSC_NULL,"-vector_file",vectorInputFile,PETSC_MAX_PATH_LEN-1,&flagVct);CHKERRQ(ierr);
	
        ierr=PetscOptionsGetBool(NULL,PETSC_NULL,"-complex",&cplex, NULL);CHKERRQ(ierr);
	/* Check if files where provided, raise an error if not */
	if(!flagMtx && !flagVct){
		SETERRQ(PETSC_COMM_WORLD,1,"No matrix file neither vector one where provided, what am I supposed to convert ? Void ???\n");
	}
	
		
	/* Now read input data and put it into defined structures */
	
	if(flagMtx){
		/* Get the matrix, either real or complex */
		if(cplex) // if using complex data
				MMTgetMatrix(matrixInputFile,&A,&minfo);
		else
				MMTgetMatrixReal(matrixInputFile,&A,&minfo);
		
		sprintf(matrixOutputFile,"%s_%dx%d_%dnnz.gz",matrixInputFile,minfo.n,minfo.m,minfo.nnz);
		
		
		PetscPrintf(PETSC_COMM_WORLD,"Dumping matrix to PETSc binary %s\n",matrixOutputFile);
			
		PetscViewerBinaryOpen(PETSC_COMM_WORLD,matrixOutputFile,FILE_MODE_WRITE,&output_viewer);
		PetscViewerPushFormat(output_viewer,PETSC_VIEWER_ASCII_INFO_DETAIL);
		MatView(A,output_viewer);
		PetscViewerDestroy(&output_viewer);
		
		PetscPrintf(PETSC_COMM_WORLD,"Matrix %s Dumped\n",matrixOutputFile);
		
	}
	if(flagVct){
		/* Get the vector, either real or complex */
		if(cplex) // if using complex data
			MMTgetVector(vectorInputFile,&b,&sizen);	
		else
			MMTgetVectorReal(vectorInputFile,&b,&sizen);
		
		
		sprintf(vectorOutputFile,"%s_%d.gz",vectorInputFile,sizen);
		
		PetscPrintf(PETSC_COMM_WORLD,"Dumping vector to PETSc binary %s\n",vectorOutputFile);
		PetscViewerBinaryOpen(PETSC_COMM_WORLD,vectorOutputFile,FILE_MODE_WRITE,&output_viewer);
		PetscViewerPushFormat(output_viewer,PETSC_VIEWER_ASCII_INFO_DETAIL);
		VecView(b,output_viewer);
		PetscViewerDestroy(&output_viewer);	
	}
	
	if(flagVct)VecDestroy(&b);
	if(flagMtx)MatDestroy(&A);
	PetscFinalize();
		
	return 0;
}



