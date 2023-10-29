//types

//matrix type: has rows, cols, matrix attributes
typedef struct {
    int rows;
    int cols;
    float **matrix;
} Matrix;

typedef struct {
    float *freeTerms;
    Matrix solutions;
    int dimension;
} Solutions;

typedef struct {
    
} tests;



//code utils

float **buildMatrix(int rows, int cols, int zeros);
void printMatrix(Matrix matrix);
void printSolutions(Solutions solutions);
void dumpMatrix(Matrix matrix);
void dumpSolution(Solutions solutions);

//math instruments

Matrix traspose(Matrix matrix);
Matrix dotProduct(Matrix matrix1, Matrix matrix2);
void multiplyRow(Matrix matrix, int row, float factor);
void combineRows(Matrix matrix, int row1, int row2, float factor);
void swapRows(Matrix matrix, int row1, int row2);
int rank(Matrix matrix);
void firstNonZero(Matrix matrix, int startingRow, int coords[2]);
void swapColumns(Matrix matrix, int col1, int col2);
int *sortPivots(Matrix matrix);
void sortSolutions(Solutions solutions, int *order);

//big algorithms

void echelonForm(Matrix matrix);
void GaussJordanForm(Matrix matrix, int complete);
Solutions findSolutions(Matrix matrix);