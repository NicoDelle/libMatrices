float **buildMatrix(int rows, int cols, int zeros);
void printMatrix(float **matrix, int rows, int cols);
void dumpMatrix(float **matrix, int rows);
float **traspose(float **matrix, int rows, int cols, float **emptyTrasposed);
float **dotProduct(float **product, float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2);
void multiplyRow(float **matrix, int row, int cols, float factor);
void combineRows(float **matrix, int row1, int row2, float factor, int cols);
void swapRows(float **matrix, int row1, int row2, int cols);
void echelonForm(float **matrix, int rows, int cols);
