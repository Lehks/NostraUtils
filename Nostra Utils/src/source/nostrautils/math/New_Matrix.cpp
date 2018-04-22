//#include "stdafx.h"
#include <iostream>


int ** generateMatrix(int rows, int cols) {
	int **temp = new int*[rows];

	for (int i = 0; i < rows; ++i) {
		temp[i] = new int[cols];
	}
	return temp;
}

void printMatrix(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void populateMatrix(int** matrix, int rows, int cols, int *src, int src_size) {

	if (rows * cols != src_size) {
		std::cout << "Size of the matrix is not equal to the size of source Array" << std::endl;
		exit(-1);
	}

	int pos = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			matrix[i][j] = src[pos++];
		}
	}
}

int ** addMatrix(int** matA, int** matB, int rows, int cols) {
	int** resultMat = generateMatrix(rows, cols);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			resultMat[i][j] = matA[i][j] + matB[i][j];
		}
	}

	return resultMat;
}


/*
int main() {

	//first matrix
	int m1_src[] = { 0, 0, 1, 0, 1, 0, 1, 0, 0 };
	int m1_rows = 3, m1_cols = 3;
	int** m1 = generateMatrix(m1_rows, m1_cols);
	populateMatrix(m1, m1_rows, m1_cols, m1_src, 9);

	//second mmatrix
	int m2_src[] = { 1, 1, 1, 2, 2, 2, 3, 3, 3 };
	int m2_rows = 3, m2_cols = 3;
	int** m2 = generateMatrix(m2_rows, m2_cols);
	populateMatrix(m2, m2_rows, m2_cols, m2_src, 9);

	//printMatrix(m1, m1_rows, m1_cols);
	std::cout << std::endl;
	//printMatrix(m2, m2_rows, m2_cols);

	//result matrix
	printMatrix(addMatrix(m1, m2, m1_rows, m1_cols), m1_rows, m1_cols);

	system("pause");
	return 0;
}
*/