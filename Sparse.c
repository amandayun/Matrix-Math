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
	
	
	if(argc!=3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	if(in ==NULL){
		printf("unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	
	out = fopen(argv[2], "w");
	if(out==NULL){
		printf("unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	
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
	
	
	
	fprintf(out, "A has %d non-zero entries:\n", a);
	printMatrix(out, A);
	fprintf(out, "\n");
	
	fprintf(out, "B has %d non-zero entries:\n", b);
	printMatrix(out, B);
	fprintf(out, "\n");
	
	fprintf(out, "(1.5)*A = \n");
	Matrix scalar = scalarMult(1.5, A);
	printMatrix(out, scalar);
	fprintf(out, "\n");
	
	fprintf(out, "A+B = \n");
	Matrix s = sum(A, B);
	printMatrix(out, s);
	fprintf(out, "\n");
	
	fprintf(out, "A+A = \n");
	Matrix s2 = sum(A, A);
	printMatrix(out, s2);
	fprintf(out, "\n");
	
	fprintf(out, "B-A = \n");
	Matrix sub = diff(B, A);
	printMatrix(out, sub);
	fprintf(out, "\n");
	
	fprintf(out, "A-A = \n");
	Matrix subA = diff(A, A);
	printMatrix(out, subA);
	fprintf(out, "\n");
	
	fprintf(out, "Transpose(A) = \n");
	Matrix trans = transpose(A);
	printMatrix(out, trans);
	fprintf(out, "\n");
	
	fprintf(out, "A*B = \n");
	Matrix mult = product(A, B);
	printMatrix(out, mult);
	fprintf(out, "\n");
	
	
	fprintf(out, "B*B = \n");
	Matrix multB = product(B, B);
	printMatrix(out, multB);
	fprintf(out, "\n");
	
	
	freeMatrix(&A);
	freeMatrix(&B);

	
	
	return 0;
}