#include "libs.h"

PetscErrorCode MMTgetMatrix(char * fin, Mat * A, MatrixInfo * minfo){
	char buf[PETSC_MAX_PATH_LEN];
	PetscInt       i,m,n,nnz,nz,nztemp,nzmax,col,row;
	PetscScalar	   value;
	PetscReal	   r_value,i_value;
	FILE*          file;
	PetscInt 	   ierr;
	nz=1;
	nztemp=-1;
	nzmax=1;
	
	ierr = PetscFOpen(PETSC_COMM_WORLD,fin,"r",&file);CHKERRQ(ierr);
		
	/* Ignore the first line of the file*/
	fgets(buf,PETSC_MAX_PATH_LEN-1,file);
	PetscPrintf(PETSC_COMM_WORLD,"%s",buf);
	fscanf(file,"%d %d %d\n",&m,&n,&nnz);
	
	if(nnz<=0) SETERRQ(PETSC_COMM_WORLD,1,"Matrix Market Converter : you must verify the format of entry file\n");

	minfo->n=n;
	minfo->m=m;
	minfo->nnz=nnz;

	PetscPrintf(PETSC_COMM_WORLD,"Matrix properties : m = %d, n = %d, nnz = %d\n",m,n,nnz);
	
	MatCreateSeqAIJ(PETSC_COMM_SELF,m,n,PETSC_DEFAULT,PETSC_NULL,A);
	
	/*Matrix reading*/
	for (i=0; i<nnz; i++) {
		fscanf(file,"%d %d %le %le\n",&row,&col,(double*)&r_value,(double*)&i_value);
		row = row-1; col = col-1 ;
		if(nztemp!=col){
			nz=1;
			nztemp=col;
		} else {
			nz++;
		}
		if(nz>nzmax){
			nzmax=nz;
		}
		value=(PetscScalar)r_value+(PetscScalar)PETSC_i*i_value;
		ierr = MatSetValues(*A,1,&row,1,&col,&value,INSERT_VALUES);CHKERRQ(ierr);
		/*
		if (row != col) {
			ierr = MatSetValues(*A,1,&col,1,&row,&value,INSERT_VALUES);CHKERRQ(ierr);
		}
		*/
	}
	PetscPrintf(PETSC_COMM_WORLD,"Maximum number of NNZ on a line : %d\n",nz);
	
	
	/*Matrix assembly*/
	PetscPrintf(PETSC_COMM_WORLD,"Assembling matrix within PETSc.\n");
	MatAssemblyBegin(*A,MAT_FINAL_ASSEMBLY);
	MatAssemblyEnd(*A,MAT_FINAL_ASSEMBLY);
	PetscPrintf(PETSC_COMM_WORLD,"Finised matrix assembly.\n");
	
	fclose(file);
	
	return ierr;
}



PetscErrorCode MMTgetVector(char * fin, Vec * v, int * size){
	char buf[PETSC_MAX_PATH_LEN];
	PetscInt       i,m,n;
	PetscScalar	   value;
	PetscReal	   r_value,i_value;
	FILE*          file;
	PetscInt 	   ierr;

	
	ierr = PetscFOpen(PETSC_COMM_WORLD,fin,"r",&file);CHKERRQ(ierr);
		
	/* Ignore the first line of the file*/
	fgets(buf,PETSC_MAX_PATH_LEN-1,file);
	PetscPrintf(PETSC_COMM_WORLD,"%s",buf);
	fscanf(file,"%d\n",&m);
	
//      fscanf(file,"%d %d\n",&m,&n);

	if(m<=0) SETERRQ(PETSC_COMM_WORLD,1,"Vector Market Converter : you must verify the format of entry file\n");

	PetscPrintf(PETSC_COMM_WORLD,"Vector properties : m = %d\n",m);
	
	*size = m;
	PetscPrintf(PETSC_COMM_WORLD,"Creating vector\n");
	VecCreate(PETSC_COMM_WORLD,v);
	VecSetSizes(*v,PETSC_DECIDE,m);
	VecSetFromOptions(*v);	
	
	PetscPrintf(PETSC_COMM_WORLD,"Reading vector\n");
	/*Vector reading*/
	for (i=0; i<m; i++) {
		fscanf(file,"%le %le\n",(double*)&r_value,(double*)&i_value);
		value=(PetscScalar)r_value+PETSC_i*i_value;
		ierr = VecSetValue(*v,i,value,INSERT_VALUES);CHKERRQ(ierr);
	}
	
	/*Vector assembly*/
	PetscPrintf(PETSC_COMM_WORLD,"Assembling vector within PETSc.\n");
	VecAssemblyBegin(*v);
	VecAssemblyEnd(*v);
	PetscPrintf(PETSC_COMM_WORLD,"Finished vector assembly.\n");
	
	
	fclose(file);
	
	return ierr;
}



PetscErrorCode MMTgetMatrixReal(char * fin, Mat * A, MatrixInfo * minfo){
	char buf[PETSC_MAX_PATH_LEN];
	PetscInt       i,m,n,nnz,nz,nztemp,nzmax,col,row;
	PetscScalar	   value;
	PetscReal	   r_value;
	FILE*          file;
	PetscInt 	   ierr;
	nz=1;
	nztemp=-1;
	nzmax=1;
	
	ierr = PetscFOpen(PETSC_COMM_WORLD,fin,"r",&file);CHKERRQ(ierr);
		
	/* Ignore the first line of the file*/
	fgets(buf,PETSC_MAX_PATH_LEN-1,file);
	PetscPrintf(PETSC_COMM_WORLD,"%s",buf);
	fscanf(file,"%d %d %d\n",&m,&n,&nnz);
	
	if(nnz<=0) SETERRQ(PETSC_COMM_WORLD,1,"Matrix Market Converter : you must verify the format of entry file\n");

	minfo->n=n;
	minfo->m=m;
	minfo->nnz=nnz;

	PetscPrintf(PETSC_COMM_WORLD,"Matrix properties : m = %d, n = %d, nnz = %d\n",m,n,nnz);
	
	MatCreateSeqAIJ(PETSC_COMM_SELF,m,n,PETSC_DEFAULT,PETSC_NULL,A);
	
	/*Matrix reading*/
	for (i=0; i<nnz; i++) {
		fscanf(file,"%d %d %le\n",&row,&col,(double*)&r_value);
		row = row-1; col = col-1 ;
		if(nztemp!=col){
			nz=1;
			nztemp=col;
		} else {
			nz++;
		}
		if(nz>nzmax){
			nzmax=nz;
		}
		value=(PetscScalar)r_value;
		ierr = MatSetValues(*A,1,&row,1,&col,&value,INSERT_VALUES);CHKERRQ(ierr);
	/*
		if (row != col) {
			ierr = MatSetValues(*A,1,&col,1,&row,&value,INSERT_VALUES);CHKERRQ(ierr);
	*/
		}
	}
	PetscPrintf(PETSC_COMM_WORLD,"Maximum number of NNZ on a line : %d\n",nz);
	
	/*Matrix assembly*/
	PetscPrintf(PETSC_COMM_WORLD,"Assembling matrix within PETSc.\n");
	MatAssemblyBegin(*A,MAT_FINAL_ASSEMBLY);
	MatAssemblyEnd(*A,MAT_FINAL_ASSEMBLY);
	PetscPrintf(PETSC_COMM_WORLD,"Finished matrix assembly.\n");
	
	fclose(file);
	
	return ierr;
}

PetscErrorCode MMTgetVectorReal(char * fin, Vec * v, int * size){
	char buf[PETSC_MAX_PATH_LEN];
	PetscInt       i,m,n;
	PetscScalar	   value;
	PetscReal	   r_value;
	FILE*          file;
	PetscInt 	   ierr;

	
	ierr = PetscFOpen(PETSC_COMM_WORLD,fin,"r",&file);CHKERRQ(ierr);
		
	/* Ignore the first line of the file*/
	fgets(buf,PETSC_MAX_PATH_LEN-1,file);
	PetscPrintf(PETSC_COMM_WORLD,"%s",buf);
//	fscanf(file,"%d %d\n",&m,&n);


	fscanf(file,"%d\n",&m);

	
	if(m<=0) SETERRQ(PETSC_COMM_WORLD,1,"Vector Market Converter : you must verify the format of entry file\n");

	PetscPrintf(PETSC_COMM_WORLD,"Vector properties : m = %d\n",m);
	
	*size = m;
	
	VecCreateSeq(PETSC_COMM_WORLD,m,v);

	
	/*Matrix reading*/
	for (i=0; i<m; i++) {
		fscanf(file,"%le\n",(double*)&r_value);
		value=(PetscScalar)r_value;
		ierr = VecSetValue(*v,i,value,INSERT_VALUES);CHKERRQ(ierr);
	}
	
	/*Matrix assembly*/
	PetscPrintf(PETSC_COMM_WORLD,"Assembling vector within PETSc.\n");
	VecAssemblyBegin(*v);
	VecAssemblyEnd(*v);
	PetscPrintf(PETSC_COMM_WORLD,"Finished vector assembly.\n");
	
	fclose(file);
	
	return ierr;
}
