#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef int data_type;
#define SPARSE 0
#define DENSE 1

typedef struct Node** Matrix;
typedef enum Modes Mode;

Matrix createMatrix(int rows, int columns);
void freeMatrix(Matrix matrix, int rows);
void FillMatrix(Matrix matrix, int rows, int columns);
void displayMatrix(Matrix matrix, int rows, int columns, int mode);
void insertElement(Matrix matrix, int rows, int columns, int rowIdx, int colIdx, data_type value);
Matrix addMatrices(Matrix matrix1, Matrix matrix2, int rows, int columns);
int getMatrixValue(Matrix matrix, int rows, int columns, int rowIdx, int colIdx);
void multiplyMatrixByScalar(Matrix matrix, int rows, int columns, int scalar);
Matrix transposeMatrix(Matrix matrix, int rows, int columns);
void swapMatrixRows(Matrix matrix, int rows, int columns, int row1, int row2);
void swapMatrixColumns(Matrix matrix, int rows, int columns, int col1, int col2);
Matrix multiplyTwoMatrices(Matrix matrix1, int rows1, int columns1,Matrix matrix2, int rows2, int columns2);
Matrix getSubmatrix(Matrix matrix, int startRow, int startColumn, int endRow, int endColumn);
void MatrixToFile(Matrix matrix, int rows, int columns,char* filename);
Matrix MatrixFromFile(char* filename, int* rows, int* columns);
Matrix MatrixConvolution(Matrix matrix, int rows, int columns, Matrix kernel, int kernelRows, int kernelColumns);
#endif