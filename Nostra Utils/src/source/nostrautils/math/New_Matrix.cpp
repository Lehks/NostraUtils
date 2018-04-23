#ifndef NOU_MATH_UTILS_HPP
#define NOU_MATH_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include <iostream>

namespace NOU::NOU_MATH {

	template<typename T>
	constexpr T **generateMatrix(const T &rows, const T &cols) {

		T** temp = new T*[rows];

		for (int i = 0; i < rows; ++i) {
			temp[i] = new T[cols];
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

	void populateMatrix(int** matrix, int rows, int cols, int * src, int src_size) {

		if (rows * cols != src_size) {
			std::cout << "Size of matrix is not equal to the size of source array" << std::endl;
			exit(-1);
		}

		int pos = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				matrix[i][j] = src[pos++];
			}
		}
	}

	template<typename T>
	constexpr T** addMatrix(T** matA, T** matB, T &rows, T &cols) {
		T** resultMat = generateMatrix(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				resultMat[i][j] = matA[i][j] + matB[i][j];
			}
		}

		return resultMat;
	}

	template<typename T>
	constexpr T** subMatrix(T** matA, T** matB, T &rows, T &cols) {
		T** resultMat = generateMatrix(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				resultMat[i][j] = matA[i][j] - matB[i][j];
			}
		}

		return resultMat;
	}
	/*
	int** mulMatrix(int** matA, int** matB, int rows, int cols) {
	if(cols != )

	int** resultMat = generateMatrix(rows, cols);

	for (int i = 0; i < rows; ++i) {
	for (int j = 0; j < cols; ++j) {
	resultMat[i][j] = matA[i][j] - matB[i][j];
	}
	}

	return resultMat;
	}
	*/
	void transpose(int** matTrans, int rows, int cols) {
		int **temp = generateMatrix(cols, rows);

		for (int i = 0; i < cols; ++i) {
			for (int j = 0; j < rows; ++j) {
				temp[i][j] = matTrans[i][j];
			}
		}

		for (int i = 0; i < rows; ++i) {
			delete[] matTrans[i];
		}
		delete[] matTrans;

		matTrans = temp;
		int tmp = cols;
		rows = cols;
		cols = tmp;
	}



	int main() {

		int m1_src[] = { 1,1,1,2,2,2,3,3,3 };
		int m1_rows = 3, m1_cols = 3;
		int** m1 = generateMatrix(m1_rows, m1_cols);
		populateMatrix(m1, m1_rows, m1_cols, m1_src, 9);
		printMatrix(m1, m1_rows, m1_cols);
		std::cout << std::endl;

		int m2_src[] = { 1,1,1,2,2,2,3,3,3 };
		int m2_rows = 3, m2_cols = 3;
		int** m2 = generateMatrix(m2_rows, m2_cols);
		populateMatrix(m2, m2_rows, m2_cols, m2_src, 9);
		printMatrix(m2, m2_rows, m2_cols);
		std::cout << std::endl;

		// result
		printMatrix(addMatrix(m1, m2, m1_rows, m1_cols), m1_rows, m1_cols);

		printMatrix(subMatrix(m1, m2, m1_rows, m1_cols), m1_rows, m1_cols);

		system("pause");
		return 0;
	}
}
#endif