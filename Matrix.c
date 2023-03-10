//Amanda Yun, akyun, 1903241, pa4
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"
#include <assert.h>
#include <stdbool.h>

typedef struct EntryObj *Entry;

typedef struct EntryObj{
	int column;
	double value;
	
} EntryObj;

typedef struct MatrixObj{
	int size;
	int NNZ; 
	
	List* entries;

} MatrixObj;

Entry newEntry(int col, double val){
	Entry E = malloc(sizeof(EntryObj));
	assert(E!=NULL);
	
	E->column = col;
	E->value = val;
	
	return(E);
}


Matrix newMatrix(int n){
	if(n<1){
		printf("Matrix error: calling newGraph when number of vertices is less than 1\n");
		exit(EXIT_FAILURE);
	}
	
	Matrix M = malloc(sizeof(MatrixObj));
	assert(M!=NULL);
	
	M->size = n;
	M->NNZ = 0;
	
	M->entries = malloc(sizeof(List)*(n+1));
	

	
	for(int i =1; i<=n; i++){
		M->entries[i] = newList();
//		for(int k = 1; k<=n; k++){
//			//fill each row with 0's?
//			append(M->entries[i], N);
//		}
	}
	
	
	
	return(M);
}


void freeMatrix(Matrix* pM){
	if(pM==NULL){
		printf("Matrix Error: calling freeMatrix on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	
	makeZero(*pM);
	
	for(int i=1; i<=size(*pM); i++){
		freeList(&(*pM)->entries[i]);
	}
	
	free((*pM)->entries);
	free(*pM);
	*pM=NULL;

	
}




int size(Matrix M){
	if(M==NULL){
		printf("Matrix error: calling size() on a NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	
	return M->size;
}

int NNZ(Matrix M){
	if(M==NULL){
		printf("Matrix error: calling NNZ() on a NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	
	return M->NNZ;
}

void freeEntry(Entry *pE){
	free(*pE);
	*pE=NULL;
}


//void deleteEntry(List L){
//	int cursor = index(L);
//	delete(L);
//	moveFront(L);
//	while(index(L)>=0){
//		moveNext(L);
//		if(index(L)==cursor){
//			break;
//		}
//	}
//	
//	//now cursor is set at node before the deleted node
//}


void makeZero(Matrix M){
	if(M==NULL){
		printf("Matrix error: calling makeZero() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	if(M->size==0){
		printf("Matrix error: calling makeZero() on an empty matrix\n");
		exit(EXIT_FAILURE);
	}
	
	for(int i =1; i<=size(M); i++){
		List L = M->entries[i]; 
		if(length(L)>0){
			moveFront(L);
			while(index(L)>=0){
				Entry E = (Entry)(get(L));
				E = NULL;
				freeEntry(&E);
				moveNext(L);
			}
			clear(L);
		}
	}
	
	M->NNZ = 0;

	
}

//if(length(L)>0){
//	moveFront(L);
//	while(index(L)>=0){
//		free(get(L));
//		moveNext(L);
//	}
//}
//



void changeEntry(Matrix M, int i, int j, double x){
	if(M==NULL){
		printf("Matrix error: calling changeEntry() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	if(M->size==0){
		printf("Matrix error: calling changeEntry() on an empty matrix\n");
		exit(EXIT_FAILURE);
	}
	if(i<1 || i>size(M) || j<1 || j>size(M)){
		printf("Entry error: i or j out of range\n");
		exit(EXIT_FAILURE);
	}
	
	List L = M->entries[i];
	Entry E = NULL;
	
	if(length(L)>0){
		moveFront(L);
		while(index(L)>=0){
			//moveNext(L);
			E = (Entry)get(L);
			if(E->column>=j){
				break;
			}
			moveNext(L);
		}
		
	}
	
	if(E==NULL || index(L)<0){
		if(x!=0){
			append(L, newEntry(j, x));
			M->NNZ++;
		}
	}else if(E->column>j){
		if(x!=0){
			insertBefore(L, newEntry(j, x));
			M->NNZ++;
		}

	}else{
		if(x!=0){
			E->value =x;	
		}else{
			E = (Entry)get(L);
			delete(L);
			freeEntry(&E);
			M->NNZ--;
		}
	}
	
	
}

Matrix copy(Matrix A){
	if(A==NULL){
		printf("Matrix error: calling copy() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	
	Matrix B = newMatrix(size(A));
	for(int i = 1; i<=size(A); i++){
		List X = A->entries[i];
		List Y = B->entries[i];
		moveFront(X);
		moveFront(Y);
		while(index(X)>=0){
			Entry k = get(X);
			if(k->column>0){
				int j = k->column;
				double val = k->value;
				changeEntry(B, i, j, val);
			}
			moveNext(X);
	
		}
	}	
	
	return B;
}

Matrix transpose(Matrix A){
	if(A==NULL){
		printf("Matrix error: calling transpose() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	
	Entry k;
	
	Matrix B = newMatrix(size(A));
	B->NNZ=NNZ(A);
	
	for(int i =1; i<=size(A);i++){
		List X = A->entries[i];
		moveFront(X);
		while(index(X)>=0){
			k = (Entry)get(X);
			append(B->entries[k->column] ,newEntry(i, k->value));
			moveNext(X);
		}
	}
	
	
	return B;
}

Matrix scalarMult(double x, Matrix A){
	if(A==NULL){
		printf("Matrix error: calling scalarMult() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	
	Matrix B = newMatrix(size(A));
	
	for(int i =1; i<=size(A);i++){
		List X = A->entries[i];
		moveFront(X);
		while(index(X)>=0){
			Entry k = get(X);
			if(k->column>0){
				int j = k->column;
				double val = x*k->value;
				changeEntry(B, i, j, val);
			}
			moveNext(X);
		}
			
	}
	
	
	return B;

}

Matrix sum(Matrix A, Matrix B){
	if(A==NULL){
		printf("Matrix error: calling sum() on a NULL Matrix A\n");
		exit(EXIT_FAILURE);
	}
	if(B==NULL){
		printf("Matrix error: calling sum() on a NULL Matrix B\n");
		exit(EXIT_FAILURE);
	}
	
	if(size(A)!=size(B)){
		printf("Matrix error: calling sum() when size of Matrix A and Matrix B do not match\n");
		exit(EXIT_FAILURE);
	}
	
	double sum;
	int cA, cB;
	double valA, valB;
	Matrix S = newMatrix(size(A));
	
	if(equals(A, B)){
		S = scalarMult(2, A);
		return S;
	}
	
	
	
	for(int i=1; i<=size(A);i++){
		List X = A->entries[i];
		List Y = B->entries[i];
		
		moveFront(X);
		moveFront(Y);
		
		while(index(X)>=0 && index(Y)>=0){
			Entry k = (Entry)get(X);
			Entry f = (Entry)get(Y);
			cA = k->column;
			cB = f->column;
			valA = k->value;
			valB = f->value;
			if(cA==cB){
				sum = valA + valB;
				if(sum!=0){
					append(S->entries[i], newEntry(cA, sum));
					S->NNZ++;
				}
				moveNext(X);
				moveNext(Y);
				
			}else if(cA<cB){
				Entry E = newEntry(cA, valA);
				append(S->entries[i], E);
				S->NNZ++;
				moveNext(X);
			}else{
				Entry E = newEntry(cB, valB);
				append(S->entries[i], E);
				S->NNZ++;
				moveNext(Y);

			}
			
		}
		
		if(index(X)<0 && index(Y)>=0){
			while(index(Y)>=0){
				Entry k = (Entry)get(Y);
				append(S->entries[i], newEntry(k->column, k->value));
				S->NNZ++;
				moveNext(Y);
			}
		}else if(index(Y)<0 && index(X)>=0){
			while(index(X)>=0){
				Entry k = (Entry)get(X);
				append(S->entries[i], newEntry(k->column, k->value));
				S->NNZ++;
				moveNext(X);
			}
		}
		
	}
	

	
	return S;
	
}

Matrix diff(Matrix A, Matrix B){
	if(A==NULL){
		printf("Matrix error: calling diff() on a NULL Matrix A\n");
		exit(EXIT_FAILURE);
	}
	if(B==NULL){
		printf("Matrix error: calling diff() on a NULL Matrix B\n");
		exit(EXIT_FAILURE);
	}
	
	if(size(A)!=size(B)){
		printf("Matrix error: calling diff() when size of Matrix A and Matrix B do not match\n");
		exit(EXIT_FAILURE);
	}
	
	double diff;
	int cA, cB;
	double valA, valB;
	Matrix S = newMatrix(size(A));
	
	if(equals(A, B)){
		S=copy(A);
		makeZero(S);
		return S;
	}
	
	for(int i=1; i<=size(A);i++){
		List X = A->entries[i];
		List Y = B->entries[i];
		
		moveFront(X);
		moveFront(Y);
		
		while(index(X)>=0 && index(Y)>=0){
			Entry k = (Entry)get(X);
			Entry f = (Entry)get(Y);
			cA = k->column;
			cB = f->column;
			valA = k->value;
			valB = f->value;
			if(cA==cB){
				diff = valA - valB;
				if(diff!=0){
					append(S->entries[i], newEntry(cA, diff));
					S->NNZ++;
				}
				moveNext(X);
				moveNext(Y);
				
			}else if(cA<cB){
				Entry E = newEntry(cA, valA);
				append(S->entries[i], E);
				S->NNZ++;
				moveNext(X);
			}else{
				Entry E = newEntry(cB, -1*valB);
				append(S->entries[i], E);
				S->NNZ++;
				moveNext(Y);
				
			}
			
		}
		
		if(index(X)<0 && index(Y)>=0){
			while(index(Y)>=0){
				Entry k = (Entry)get(Y);
				append(S->entries[i], newEntry(k->column, -1*k->value));
				S->NNZ++;
				moveNext(Y);
			}
		}else if(index(Y)<0 && index(X)>=0){
			while(index(X)>=0){
				Entry k = (Entry)get(X);
				append(S->entries[i], newEntry(k->column, k->value));
				S->NNZ++;
				moveNext(X);
			}
		}
		
	}
	
	
	
	return S;	
}

//used Mahyar Mike Vahabi pseudocode
double dotProduct(List A, List B){
	if(A==B){
		printf("List error: List A and List B cannot be equal\n");
		exit(EXIT_FAILURE);
	}
	double dp = 0.0;
	Entry a, b;
	
	
	moveFront(A);
	moveFront(B);
	while(index(A)>=0 && index(B)>=0){
		a = get(A);
		b = get(B);
		if(a->column==b->column){
			dp+=a->value*b->value;
			moveNext(A);
			moveNext(B);
		}else if(a->column<b->column){
			moveNext(A);
		}else{
			moveNext(B);
		}
	}
	
	
	
	
	return dp;
}

Matrix product(Matrix A, Matrix B){
	if(A==NULL){
		printf("Matrix error: calling product() on a NULL Matrix A\n");
		exit(EXIT_FAILURE);
	}
	if(B==NULL){
		printf("Matrix error: calling product() on a NULL Matrix B\n");
		exit(EXIT_FAILURE);
	}
	
	if(size(A)!=size(B)){
		printf("Matrix error: calling product() when size of Matrix A and Matrix B do not match\n");
		exit(EXIT_FAILURE);
	}
	
	Matrix p = newMatrix(size(A));

	Matrix t = transpose(B);

	
	for(int i =1; i<=size(A);i++){
		List X = A->entries[i];
		for(int j = 1; j<=size(A);j++){
			List Y = t->entries[j];
			double dp = dotProduct(X, Y);
			if(dp!=0){
				changeEntry(p, i, j, dp);
			}
		}
	}
	
	//free the tranposed matrix
	freeMatrix(&t);

	
	return p;

}



void printMatrix(FILE* out, Matrix M){
	if(M==NULL){
		printf("Matrix error: calling printMatrix() on a NULL Matrix A\n");
		exit(EXIT_FAILURE);
	}


	for(int i = 1; i<=size(M); i++){
		List L = M->entries[i];
		if(length(L)>0){
			fprintf(out,"%d: ", i);
			moveFront(L);
			while(index(L)>=0){
				Entry k = (Entry)get(L);
				fprintf(out,"(%d, %.1f) ", k->column, k->value);
				moveNext(L);
			}
			fprintf(out, "\n");
		}
		
	}
	
	


}




int equals(Matrix A, Matrix B){
	
	Entry x, y;
	List c, d;
	
	if(size(A)!=size(B)){
		return 0;
	}
	if(NNZ(A)!=NNZ(B)){
		return 0;
	}
	
	if(A==B){
		return 1;
	}
	
	
	for(int i =1; i<=size(A);i++){
		c = A->entries[i];
		d = B->entries[i];
		if(length(c)!=length(d)){
			return 0;
		}
		
		moveFront(c);
		moveFront(d);
		while(index(c)>=0 && index(d)>=0){
			//printf("index C: %d index D: d=%d\n", index(c), index(d));
			x = (Entry)get(c);
			y = (Entry)get(d);
			if(x->column!= y->column || x->value!=y->value){
				return 0;
			}else{
				moveNext(c);
				moveNext(d);
			}
		}
	}

//	
//	if(size(A)==size(B)){
//		for(int i=1; i<=size(A); i++){
//			c = A->entries[i];
//			d = B->entries[i];
//			moveFront(c);
//			moveFront(d);
//			while(index(c)>=0 && index(d)>=0){
//				x = get(c);
//				y= get(d);
//				if(x->value!=y->value){
//					return 0;
//				}
//				moveNext(c);
//				moveNext(d);
//			}
//		}
//	}
	
	return 1;
	
}


	