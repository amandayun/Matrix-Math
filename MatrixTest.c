//Amanda Yun, akyun, 1903241, pa4
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char **argv) {
	
	Matrix A = newMatrix(3);
	Matrix b = newMatrix(3);
	
	
	
	changeEntry(A, 1, 1, 1);
	changeEntry(A, 1, 2, 2);
	changeEntry(A, 1, 3, 3);
	changeEntry(A, 2, 1, 4);
	changeEntry(A, 2, 2, 5);
	changeEntry(A, 2, 3, 6);
	changeEntry(A, 3, 1, 7);
	changeEntry(A, 3, 2, 8);
	changeEntry(A, 3, 3, 9);
	
	changeEntry(b, 1, 1, 1);
	changeEntry(b, 1, 2, 2);
	changeEntry(b, 1, 3, 3);
	changeEntry(b, 2, 1, 4);
	changeEntry(b, 2, 2, 5);
	changeEntry(b, 2, 3, 6);
	changeEntry(b, 3, 1, 7);
	changeEntry(b, 3, 2, 8);
	changeEntry(b, 3, 3, 9);
	
	
	
	printf("Matrix A:\n");
	printMatrix(stdout, A);
	printf("\n");
	printf("Matrix B:\n");
	printMatrix(stdout, b);
	
	printf("\ntesting equals: %d\n", equals(A, b));
	
	printf("\ntesting size: %d\n", size(A));
	printf("\ntesting NNZ: %d\n", NNZ(A));
	
	Matrix co = copy(A);
	printf("\nMatrix copied:\n");
	printMatrix(stdout, co);
	
	Matrix tr = transpose(A);
	printf("\nMatrix A tranposed:\n");
	printMatrix(stdout, tr);
	
	
	Matrix sm = scalarMult(1.5, A);
	printf("\nMatrix A scalarMult by 1.5:\n");
	printMatrix(stdout, sm);
	
	Matrix added = sum(A, b);
	printf("\nMatrix A + Matrix B:\n");
	printMatrix(stdout, added);
	
	Matrix d = diff(A, sm);
	printf("\nMatrix A - A scalar Mult:\n");
	printMatrix(stdout, d);

	Matrix pro = product(A, b);
	printf("\nMatrix A * matrix b:\n");
	printMatrix(stdout, pro);
	
	printf("\n");
	
	printf("size: %d", size(A));
	
	makeZero(A);
	printMatrix(stdout, A);
	
	

	freeMatrix(&A);
	freeMatrix(&b);

	
	
	
		
	
	
	
//	Matrix s = product(A, A);
//	
//	printMatrix(stdout, A);
//	printf("\n");
//	printMatrix(stdout, B);
//	printf("\n");
//	
//	
//	
//	
//	printMatrix(stdout, s);
//
//	
//	printf("NNX: %d\n", NNZ(s));
//	
//	
//	
//	
	
	return 0;
}
