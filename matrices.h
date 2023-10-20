//types
typedef struct {
    int rows;
    int cols;
    float **matrix;
} Matrix; //matrix type: has rows, cols, matrix attributes

float **buildMatrix(int rows, int cols, int zeros);
void printMatrix(Matrix matrix);
void dumpMatrix(Matrix matrix);
Matrix traspose(Matrix matrix);
Matrix dotProduct(Matrix matrix1, Matrix matrix2);
void multiplyRow(Matrix matrix, int row, float factor);
void combineRows(Matrix matrix, int row1, int row2, float factor);
void swapRows(Matrix matrix, int row1, int row2);
void echelonForm(Matrix matrix);
void GaussJordanForm(Matrix matrix);
