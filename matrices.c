#include <stdio.h>
#include <stdlib.h>
#define ZEROS 1
#define EMPTY 0

//function that builds a matrix. The last argument is a flag that indicates if the matrix should be filled with zeros or not
float **buildMatrix(int rows, int cols, int zeros)
{
    float **matrix;
    matrix = malloc(rows * sizeof(*matrix));

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(*matrix[i]));
        for (int j = 0; j < cols; j++)
        {
            if (!zeros)
            {
                printf("Inserisci il valore M[%d][%d]: ", i, j);
                scanf("%f", &matrix[i][j]);
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}

//function that prints a matrix
void printMatrix(float **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        printf("| ");
        for (int j = 0; j < cols; j++)
        {
            printf("%4.2f ", matrix[i][j]);
        }
        printf("|\n");
    }

    printf("\n");
}

//function that frees the memory allocated for a matrix
void dumpMatrix(float **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

//function that trasposes a matrix. The last argument is a pointer to the (cols*rows) matrix where the trasposed matrix will be stored
float **traspose(float **matrix, int rows, int cols, float **trasposed)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            trasposed[j][i] = matrix[i][j];
        }
    }

    return trasposed;
}

//function that computes the product of two matrices. The function returns a pointer to the product matrix, the last argument ist also a pointer to the (rows1*cols2) matrix where the product will be stored
float **dotProduct(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2, float **product)
{
    if (cols1 != rows2)
    {
        printf("Le due matrici non sono conformabili");

        // per il flag di ritorno
        float a;
        float *b = &a;
        float **ptr = &b;

        return ptr;
    }

    product = buildMatrix(rows1, cols2, ZEROS);
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            for (int k = 0; k < cols1; k++)
            {
                product[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }

    return product;
}

//function that multiplies a row of a matrix by a factor
void multiplyRow(float **matrix, int row, int cols, float factor)
{
    for (int j = 0; j < cols; j++)
    {
        matrix[row][j] *= factor;
    }
}

//function that combines two rows of a matrix, multiplying one of them by a factor. The result is stored in row1, while factor multiplies row2.
void combineRows(float **matrix, int row1, int row2, float factor, int cols)
{
    for (int j = 0; j < cols; j++)
    {
        matrix[row1][j] += factor * matrix[row2][j];
    }
}

//function that swaps two rows of a matrix
void swapRows(float **matrix, int row1, int row2, int cols)
{
    float temp;
    for (int i = 0; i < cols; i++)
    {
        temp = matrix[row2][i];
        matrix[row2][i] = matrix[row1][i];
        matrix[row1][i] = temp;
    }
}

//function that reduces a matrix to its echelon form, using the Gauss algorithm
void echelonForm(float **matrix, int rows, int cols)
{
    // prototipo di funzione con scope minimo
    void firstNonZero(float **matrix, int rows, int cols, int startingRow, int coords[2]);

    int i;             // iteratore del  while sulle righe
    int pivotCol;      // memorizza la colonna del pivot su cui si sta correntemente lavorando
    int nonZeroRow;    // contiene l'indice della riga con primo elemento non nullo, in ordine di colonna
    int row = 0;       // indica la riga alla quale si sta lavorando
    int coords[2];     // array delle coordinate del pivot sul quale si sta lavorando
    float coefficient; // coefficiente moltiplicativo

    while (row < rows - 1) // è inutile lavorare sull'ultima riga
    {
        firstNonZero(matrix, rows, cols, row, coords);
        nonZeroRow = coords[0];
        pivotCol = coords[1];

        if (nonZeroRow != row) // porto in cima (alla parte di matrice non ridotta) la riga col pivot, e sistemo le coordinate
        {
            swapRows(matrix, row, nonZeroRow, cols);
            nonZeroRow = row;
        }

        i = nonZeroRow + 1;
        while (i < rows)
        {
            if (matrix[i][pivotCol] != 0)
            {
                coefficient = -(matrix[i][pivotCol] / matrix[nonZeroRow][pivotCol]);
                combineRows(matrix, i, nonZeroRow, coefficient, cols);
            }

            i++;
        }

        row++;
    }
}

//functions that returns the first non-zero element of a matrix, starting from a given row
void firstNonZero(float **matrix, int rows, int cols, int startingRow, int coords[2])
{
    for (int j = 0; j < cols; j++) // ciclo sulle colonne
    {
        for (int i = startingRow; i < rows; i++)
        {
            if (matrix[i][j] != 0)
            {
                coords[0] = i;
                coords[1] = j;

                return;
            }
        }
    }

    // se non trova elementi non-zero, ritorna una riga fuori dallo scope (triggerando la condizione sentinella)
    coords[0] = rows + 1;
    coords[1] = cols + 1;
    return;
}

//function that totally reduces a matrix to its reduced row echelon form, using the Gauss-Jordan algorithm
void GaussJordanForm(float **matrix, int rows, int cols)
{
    void swapColumns(float **matrix, int col1, int col2, int cols,  int rows);

    int pivotCol;      // memorizza la colonna del pivot su cui si sta correntemente lavorando
    int row = 0;       // indica la riga alla quale si sta lavorando
    int coords[2];     // array delle coordinate del pivot sul quale si sta lavorando
    float coefficient; // coefficiente moltiplicativo

    echelonForm(matrix, rows, cols);
    for(int i=rows-1; i>=0; i--)
    {
        for(int j=0; j<cols; j++)
        {
            if(matrix[i][j])
            {
                coefficient = 1/matrix[i][j];
                multiplyRow(matrix, i, cols, coefficient);
                int k = i-1;
                
                while(k>=0)
                {
                    if(matrix[k][j])
                    {
                        coefficient = -matrix[k][j];
                        combineRows(matrix, k, i, coefficient, cols);
                    }
                    k--;
                }
                
                break;
            }
        }
    }
}

//function that swaps two columns of a matrix
void swapColumns(float **matrix, int col1, int col2, int rows, int cols)
{
    float temp;
    for(int i=0; i<rows; i++)
    {
        temp = matrix[i][col2];
        matrix[i][col2] = matrix[i][col1];
        matrix[i][col1] = temp;
    }
}