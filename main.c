#include "Matrix.h"

int main(int argc, char const *argv[])
{
    int rows = 3, columns = 3;
    Matrix novaMatriz = createMatrix(rows,columns);
    FillMatrix(novaMatriz,rows,columns);
    displayMatrix(novaMatriz,rows,columns,SPARSE);
    freeMatrix(novaMatriz,rows);

    return 0;
}
