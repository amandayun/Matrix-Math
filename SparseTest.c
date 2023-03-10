//Amanda Yun, akyun, 1903241, pa4
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char **argv) {
	
	Matrix A, B, T;
	int n, a, b;
	int row, col;
	double val;
	
	FILE *in, *out;
	
	in = fopen("in1.txt", "r");
		
	out = fopen("out1.txt", "w");

	
	fscanf(in, "%d %d %d", &n, &a, &b);
	
	
	A=newMatrix(n);
	B=newMatrix(n);
	
	
	for(int i =0; i<a; i++){
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(A, row, col, val);
	}
	
	for(int i =0; i<b; i++){
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(B, row, col, val);
	}
	
	
	
	printf("A has %d non-zero entries:\n", a);
	printMatrix(stdout, A);
	printf("\n");
	
	printf("B has %d non-zero entries:\n", b);
	printMatrix(stdout, B);
	printf("\n");
	
	printf("(1.5)*A = \n");
	Matrix scalar = scalarMult(1.5, A);
	printMatrix(stdout, scalar);
	printf("\n");
	
	printf("A+B = \n");
	Matrix s = sum(A, B);
	printMatrix(stdout,s);
	printf("\n");
	
	printf("B-A = \n");
	Matrix di = diff(B, A);
	printMatrix(stdout,di);
	printf("\n");
	
	printf("tranpose = \n");
	Matrix trans = transpose(A);
	printMatrix(stdout,trans);
	printf("\n");
	
	
	printf("NNZ: %d\n", NNZ(s));
	

	
	
	return 0;
}