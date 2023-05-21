#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
// Definição da estrutura do nó
typedef struct Node {
    data_type value;
    int row, column;
    struct Node* next;
} Node;

// Função para criar um novo nó com um valor específico
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Função para criar uma matriz utilizando nós de lista encadeada

/*
    Cria a matriz
        Complexidade O(1)
*/
Matrix createMatrix(int rows, int columns) {
    Node** matrix = (Node**)malloc(rows * sizeof(Node*));
    return matrix;
}

/*
    Preenche a matriz com valores de entrada do usuário
        Complexidade O(N²), sempre irá percorrer todas as N linhas e N colunas
*/
void FillMatrix(Matrix matrix, int rows, int columns){
     int i, j;
    for (i = 0; i < rows; i++) {
        matrix[i] = NULL;
        Node* current = NULL;
        for (j = 0; j < columns; j++) {
            int value;
            printf("Digite o valor para a posição [%d][%d]: ", i, j);
            scanf("%d", &value);
                if (matrix[i] == NULL) {
                    matrix[i] = createNode(value);
                    matrix[i]->column = j;
                    matrix[i]->row = i;
                    current = matrix[i];
                } else {
                    current->next = createNode(value);
                    matrix[i]->column = j;
                    matrix[i]->row = i;
                    current = current->next;
                }
        }
    }
}

/*
    Exibir matriz
        Complexidade O(N²), No pior dos casos (modo esparso) sempre irá percorrer as N linhas * N colunas
*/
void displayMatrix(Matrix matrix, int rows, int columns, int mode) {
    int i, j;
    Node* current;
    if(!mode){
            for (i = 0; i < rows; i++) {
                for (j = 0; j < columns; j++) {
                    printf("%d ", matrix[i][j].value);
                }
                printf("\n");
            }
    }else{
            for (i = 0; i < rows; i++) {
                current = matrix[i];
                for (j = 0; j < columns; j++) {
                    if(current->value == 0) continue;
                    else{
                        printf("%d ", current->value);
                        current = current->next;
                    }
                }
                printf("\n");
            }
    }
}
/*
     Função para liberar a memória ocupada pela matriz
        Complexiade O(N²), no pior caso irá passar por todas as linhas e colunas de uma matrix N * N
 */
void freeMatrix(Matrix matrix, int rows) {
    int i;
    Node* current;
    Node* temp;

    for (i = 0; i < rows; i++) {
        current = matrix[i];

        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(matrix);
}

void insertElement(Matrix matrix, int rows, int columns, int rowIdx, int colIdx, data_type value) {
    if (rowIdx < 0 || rowIdx >= rows || colIdx < 0 || colIdx >= columns) {
        printf("Posição inválida!\n");
        return;
    }

    Node* newNode = createNode(value);
    Node* current = matrix[rowIdx];

    // Caso a matriz esteja vazia na linha especificada
    if (current == NULL) {
        matrix[rowIdx] = newNode;
        return;
    }

    // Inserir no início da lista
    if (colIdx == 0) {
        newNode->next = current;
        matrix[rowIdx] = newNode;
        return;
    }

    // Inserir no meio ou final da lista
    int i;
    for (i = 0; i < colIdx - 1 && current->next != NULL; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

Matrix addMatrices(Matrix matrix1, Matrix matrix2, int rows, int columns) {


    Node** resultMatrix = (Node**)malloc(rows * sizeof(Node*));
    int i, j;

    for (i = 0; i < rows; i++) {
        resultMatrix[i] = NULL;
        Node* current1 = matrix1[i];
        Node* current2 = matrix2[i];
        Node* resultCurrent = NULL;

        for (j = 0; j < columns; j++) {
            int sum = current1->value + current2->value;

            if (resultMatrix[i] == NULL) {
                resultMatrix[i] = createNode(sum);
                resultCurrent = resultMatrix[i];
            } else {
                resultCurrent->next = createNode(sum);
                resultCurrent = resultCurrent->next;
            }

            current1 = current1->next;
            current2 = current2->next;
        }
    }

    return resultMatrix;
}

int getMatrixValue(Matrix matrix, int rows, int columns, int rowIdx, int colIdx) {
    if (rowIdx < 0 || rowIdx >= rows || colIdx < 0 || colIdx >= columns) {
        printf("Posição inválida!\n");
            return 0; // Valor padrão em caso de posição inválida
    }
        Node* current = matrix[rowIdx];

// Percorrer a lista encadeada até a coluna desejada
        int i;
        for (i = 0; i < colIdx && current != NULL; i++) {
            current = current->next;
        }
        if (current != NULL) {
            return current->value;
        } else {
            printf("Posição não encontrada!\n");
            return 0; // Valor padrão em caso de posição não encontrada
        }   
}

void multiplyMatrixByScalar(Matrix matrix, int rows, int columns, int scalar) {
    int i, j;
    Node* current;

    for (i = 0; i < rows; i++) {
        current = matrix[i];

        for (j = 0; j < columns; j++) {
            current->value *= scalar;
            current = current->next;
        }
    }
}

Matrix transposeMatrix(Matrix matrix, int rows, int columns) {
    Node** transposedMatrix = createMatrix(columns, rows);  // Cria uma nova matriz transposta
    int i, j;
    Node* current;

    for (i = 0; i < rows; i++) {
        current = matrix[i];

        for (j = 0; j < columns; j++) {
            transposedMatrix[j][i].value = current->value;  // Atribui o valor transposto à nova matriz
            current = current->next;
        }
    }

    return transposedMatrix;
}

void swapMatrixRows(Matrix matrix, int rows, int columns, int row1, int row2) {
    if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
        printf("Posição inválida!\n");
        return;
    }

    Node* temp;
    Node* current1 = matrix[row1];
    Node* current2 = matrix[row2];

    // Troca os ponteiros dos nós de cada coluna
    int j;
    for (j = 0; j < columns; j++) {
        temp = current1;
        current1 = current1->next;
        current2->next = temp;
        current2 = current2->next;
    }

    matrix[row1] = matrix[row2];
    matrix[row2] = current2;
    current2->next = NULL;
}

void swapMatrixColumns(Matrix matrix, int rows, int columns, int col1, int col2) {

    if (col1 < 0 || col1 >= columns || col2 < 0 || col2 >= columns) {
        printf("Posição inválida!\n");
        return;
    }

    int i;
    Node* current;
    Node* temp;

    for (i = 0; i < rows; i++) {
        current = matrix[i];

        // Percorre até a coluna col1
        int j;
        for (j = 0; j < col1; j++) {
            current = current->next;
        }

        // Guarda o valor do nó da coluna col1
        temp = current;

        // Percorre até a coluna col2
        for (j = 0; j < col2; j++) {
            current = current->next;
        }

        // Troca os valores dos nós das colunas col1 e col2
        int value = temp->value;
        temp->value = current->value;
        current->value = value;
    }
}

Matrix multiplyTwoMatrices(Matrix matrix1, int rows1, int columns1,Matrix matrix2, int rows2, int columns2) {
    if (columns1 != rows2) {
        printf("Número de colunas da primeira matriz deve ser igual ao número de linhas da segunda matriz!\n");
        return NULL;
    }

    Node** result = createMatrix(rows1, columns2);
    int i, j, k;
    Node* current1;
    Node* current2;

    for (i = 0; i < rows1; i++) {
        current1 = matrix1[i];

        for (j = 0; j < columns2; j++) {
            current2 = matrix2[j];

            int sum = 0;

            for (k = 0; k < columns1; k++) {
                sum += current1->value * current2->value;
                current1 = current1->next;
                current2 = current2->next;
            }

            result[i][j].value = sum;
        }
    }

    return result;
}

void modifyPointer(Node** ptr, Node *New) {
    ///função auxiliar de modificação de ponteiros
    Node* newPtr = New;
    *ptr = newPtr;
}

Matrix getSubmatrix(Matrix matrix, int startRow, int startColumn, int endRow, int endColumn) {
    int subRows = endRow - startRow + 1;
    int subColumns = endColumn - startColumn + 1;
    Node** submatrix = createMatrix(subRows, subColumns);
    int i, j;

    for (i = startRow; i <= endRow; i++) {
        Node* current = matrix[i];

        for (j = startColumn; j <= endColumn; j++) {
           
            ///modifyPointer(submatrix[i - startRow][j - startColumn],createNode(current->value));
            submatrix[i - startRow][j - startColumn] = *(createNode(current->value)); /// pode dar merda
            current = current->next;
        }
    }

    return submatrix;
}

void MatrixToFile(Matrix matrix, int rows, int columns,char* filename) {
    FILE* file = fopen(filename, "wb");
    int i, j;
    Node* current;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    // Grava o número de linhas e colunas da matriz no arquivo
    fwrite(&rows, sizeof(int), 1, file);
    fwrite(&columns, sizeof(int), 1, file);

    // Grava os valores dos nós da matriz no arquivo
    for (i = 0; i < rows; i++) {
        current = matrix[i];

        for (j = 0; j < columns; j++) {
            fwrite(&(current->value), sizeof(int), 1, file);
            current = current->next;
        }
    }

    fclose(file);
}

Matrix MatrixFromFile(char* filename, int* rows, int* columns) {
    FILE* file = fopen(filename, "rb");
    Node** matrix = NULL;
    int i, j;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return matrix;
    }

    // Lê o número de linhas e colunas da matriz do arquivo
    fread(rows, sizeof(int), 1, file);
    fread(columns, sizeof(int), 1, file);

    // Aloca memória para a matriz
    matrix = (Node**)malloc(*rows * sizeof(Node*));

    // Lê os valores dos nós da matriz do arquivo
    for (i = 0; i < *rows; i++) {
        matrix[i] = NULL;
        Node* current = NULL;

        for (j = 0; j < *columns; j++) {
            int value;
            fread(&value, sizeof(int), 1, file);

            if (matrix[i] == NULL) {
                matrix[i] = createNode(value);
                current = matrix[i];
            } else {
                current->next = createNode(value);
                current = current->next;
            }
        }
    }

    fclose(file);

    return matrix;
}

Matrix MatrixConvolution(Matrix matrix, int rows, int columns, Matrix kernel, int kernelRows, int kernelColumns) {
    int convRows = rows - kernelRows + 1;
    int convColumns = columns - kernelColumns + 1;
    Node** result = createMatrix(convRows, convColumns);
    int i, j, k, l;

    for (i = 0; i < convRows; i++) {
        for (j = 0; j < convColumns; j++) {
            int sum = 0;

            for (k = 0; k < kernelRows; k++) {
                Node* matrixRow = matrix[i + k];
                Node* kernelRow = kernel[k];

                for (l = 0; l < kernelColumns; l++) {
                    sum += matrixRow->value * kernelRow->value;
                    matrixRow = matrixRow->next;
                    kernelRow = kernelRow->next;
                }
            }

            result[i][j].value = sum;
        }
    }

    return result;
}