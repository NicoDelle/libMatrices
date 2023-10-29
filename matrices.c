#include <stdio.h>
#include <stdlib.h>
#include "matrices.h"
#define ZEROS 1
#define EMPTY 0
#define COMPLETE 1

// function that builds a matrix. The last argument is a flag that indicates if the matrix should be filled with zeros or not
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

// function that prints a matrix
void printMatrix(Matrix matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        printf("| ");
        for (int j = 0; j < matrix.cols; j++)
        {
            printf("%4.2f ", matrix.matrix[i][j]);
        }
        printf("|\n");
    }

    printf("\n");
}

void printSolutions(Solutions solutions)
{
    if (solutions.solutions.rows == 0)
    {
        printf("La matrice non ha soluzioni\n");
        return;
    }
    else if (solutions.solutions.cols == 1)
    {
        printf("La matrice ha una sola soluzione:\n");
    }
    else
    {
        printf("Free terms:\n");
        for (int i = 0; i < solutions.solutions.rows; i++)
        {
            printf("| %2.2f |\n", solutions.freeTerms[i]);
        }
        printf("\nMatrix:\n");
    }
    printMatrix(solutions.solutions);
    printf("\n");
}

// function that frees the memory allocated for a matrix
void dumpMatrix(Matrix matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        free(matrix.matrix[i]);
    }
    free(matrix.matrix);
}

void dumpSolution(Solutions solutions)
{
    dumpMatrix(solutions.solutions);
    free(solutions.freeTerms);
}

// function that trasposes a matrix. The last argument is a pointer to the (cols*rows) matrix where the trasposed matrix will be stored
Matrix traspose(Matrix matrix)
{
    Matrix trasposed;
    trasposed.rows = matrix.cols;
    trasposed.cols = matrix.rows;
    trasposed.matrix = buildMatrix(trasposed.rows, trasposed.cols, ZEROS);

    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            trasposed.matrix[j][i] = matrix.matrix[i][j];
        }
    }

    return trasposed;
}

// function that computes the product of two matrices. The function returns a pointer to the product matrix
Matrix dotProduct(Matrix matrix1, Matrix matrix2)
{
    Matrix product;
    product.rows = matrix1.rows;
    product.cols = matrix2.cols;
    if (matrix1.cols != matrix2.rows)
    {
        printf("Le due matrici non sono conformabili");

        return product;
    }

    product.matrix = buildMatrix(product.rows, product.cols, ZEROS);
    for (int i = 0; i < matrix1.rows; i++)
    {
        for (int j = 0; j < matrix2.cols; j++)
        {
            for (int k = 0; k < matrix1.cols; k++)
            {
                product.matrix[i][j] += (matrix1.matrix[i][k] * matrix2.matrix[k][j]);
            }
        }
    }

    return product;
}

// function that multiplies a row of a matrix by a factor
void multiplyRow(Matrix matrix, int row, float factor)
{
    for (int j = 0; j < matrix.cols; j++)
    {
        matrix.matrix[row][j] *= factor;
    }
}

// function that combines two rows of a matrix, multiplying one of them by a factor. The result is stored in row1, while factor multiplies row2.
void combineRows(Matrix matrix, int row1, int row2, float factor)
{
    for (int j = 0; j < matrix.cols; j++)
    {
        matrix.matrix[row1][j] += factor * matrix.matrix[row2][j];
    }
}

// function that swaps two rows of a matrix
void swapRows(Matrix matrix, int row1, int row2)
{
    float temp;
    for (int i = 0; i < matrix.cols; i++)
    {
        temp = matrix.matrix[row2][i];
        matrix.matrix[row2][i] = matrix.matrix[row1][i];
        matrix.matrix[row1][i] = temp;
    }
}

// functions that returns the first non-zero element of a matrix, starting from a given row
void firstNonZero(Matrix matrix, int startingRow, int coords[2])
{
    for (int j = 0; j < matrix.cols; j++) // ciclo sulle colonne
    {
        for (int i = startingRow; i < matrix.rows; i++)
        {
            if (matrix.matrix[i][j] != 0)
            {
                coords[0] = i;
                coords[1] = j;

                return;
            }
        }
    }

    // se non trova elementi non-zero, ritorna una riga fuori dallo scope (triggerando la condizione sentinella)
    coords[0] = matrix.rows + 1;
    coords[1] = matrix.cols + 1;
    return;
}

// function that takes a matrix (reduced to echelon form) and returns its rank
int rank(Matrix matrix)
{
    int row, col;
    row = col = 0;

    while (row < matrix.rows && col < matrix.cols)
    {
        if (matrix.matrix[row][col] != 0)
        {
            row++;
        }
        col++;
    }

    return row; // il numero di righe contenenti un valore non nullo (se la matrice è ridotta a scala) coindice col rango della matrice
}

// function that swaps two columns of a matrix
void swapColumns(Matrix matrix, int col1, int col2)
{
    float temp;
    for (int i = 0; i < matrix.rows; i++)
    {
        temp = matrix.matrix[i][col2];
        matrix.matrix[i][col2] = matrix.matrix[i][col1];
        matrix.matrix[i][col1] = temp;
    }
}

// function that moves al the columns containing pivots to the left of the matrix and returns the new order of the columns with respect to the original matrix
int *sortPivots(Matrix matrix)
{
    int *order = (int *)malloc(sizeof(int) * matrix.cols);//take note of the swapping of columns 
    float *temp = (float *)malloc(sizeof(float) * matrix.cols);
    for (int n = 0; n < matrix.cols; n++) // inizializzazione di un array di posizioni
    {
        order[n] = n;
    }
    for (int i = 0; i < rank(matrix); i++)
    {
        if(!matrix.matrix[i][i])
        {
            int currentCol = order[i]; 
            for(int row=0; row<matrix.rows; row ++)
            {
                temp[i] = matrix.matrix[row][i]; //put the value of last column to 0
            }
            for(int col=i; col<matrix.cols-1; col++)
            {
                for(int row=0; row<matrix.rows; row ++)
                {
                    matrix.matrix[row][col] = matrix.matrix[row][col+1]; //swap every value of a column with the value of the next one
                }
                order[col] = order[col+1]; //take note of the swap
            }
            for(int row=0; row<matrix.rows; row ++)
            {
                matrix.matrix[row][matrix.cols-1] = temp[i]; //put the value of last column to 0
            }
            order[matrix.cols-1] = currentCol; //take note of last swap
        }
    }

    return order;
}

void sortSolutions(Solutions solutions, int *order)
{
    int i = 0;
    int temp;
    while (i < solutions.solutions.rows)
    {
        if (order[i] != i)
        {
            swapRows(solutions.solutions, i, order[i]);
            temp = solutions.freeTerms[i];
            solutions.freeTerms[i] = solutions.freeTerms[order[i]];
            solutions.freeTerms[order[i]] = temp;

            temp = order[i];
            order[i] = order[temp];
            order[temp] = temp;
        }
        i++;
    }
}

// function that reduces a matrix to its echelon form, using the Gauss algorithm
void echelonForm(Matrix matrix)
{
    int i;             // iteratore del  while sulle righe
    int pivotCol;      // memorizza la colonna del pivot su cui si sta correntemente lavorando
    int nonZeroRow;    // contiene l'indice della riga con primo elemento non nullo, in ordine di colonna
    int row = 0;       // indica la riga alla quale si sta lavorando
    int coords[2];     // array delle coordinate del pivot sul quale si sta lavorando
    float coefficient; // coefficiente moltiplicativo

    while (row < matrix.rows - 1) // è inutile lavorare sull'ultima riga
    {
        firstNonZero(matrix, row, coords);
        nonZeroRow = coords[0];
        pivotCol = coords[1];

        if (nonZeroRow > matrix.rows) // se non trova elementi non-zero, termina
        {
            return;
        }

        if (nonZeroRow != row) // porto in cima (alla parte di matrice non ridotta) la riga col pivot, e sistemo le coordinate
        {
            swapRows(matrix, row, nonZeroRow);
            nonZeroRow = row;
        }

        i = nonZeroRow + 1;
        while (i < matrix.rows)
        {
            if (matrix.matrix[i][pivotCol] != 0)
            {
                coefficient = -(matrix.matrix[i][pivotCol] / matrix.matrix[nonZeroRow][pivotCol]);
                combineRows(matrix, i, nonZeroRow, coefficient);
            }

            i++;
        }

        row++;
    }
}

// function that totally reduces a matrix to its reduced row echelon form, using the Gauss-Jordan algorithm
void GaussJordanForm(Matrix matrix, int complete)
{
    int pivotCol, pivotRow; // memorizza la colonna del pivot su cui si sta correntemente lavorando
    int row = 0;            // indica la riga alla quale si sta lavorando
    int coords[2];          // array delle coordinate del pivot sul quale si sta lavorando
    float coefficient;      // coefficiente moltiplicativo
    int maxCols = matrix.cols;

    if (complete)
    {
        maxCols--;
    }

    echelonForm(matrix);
    for (int i = matrix.rows - 1; i >= 0; i--)
    {
        for (int j = 0; j < maxCols; j++)
        {
            if (matrix.matrix[i][j])
            {
                coefficient = 1 / matrix.matrix[i][j];
                multiplyRow(matrix, i, coefficient);

                int k = i - 1;
                while (k >= 0)
                {
                    if (matrix.matrix[k][j])
                    {
                        coefficient = -matrix.matrix[k][j];
                        combineRows(matrix, k, i, coefficient);
                    }
                    k--;
                }

                break;
            }
        }
    }
}

//function that solves the linear system associated to the given matrix. The last column of the matrix is taken as the vector of the free terms
Solutions findSolutions(Matrix matrix)
{
    Solutions solutions;
    Matrix coeffMatrix;
    solutions.freeTerms = malloc(sizeof(float) * matrix.cols);

    int rank1;
    int pivotCoords[2];
    int *order = malloc(sizeof(int) * matrix.cols);

    printf("Matrix:\n");
    printMatrix(matrix);
    
    echelonForm(matrix);
    printf("Echelon form:\n");
    printMatrix(matrix);

    rank1 = rank(matrix);
    firstNonZero(matrix, rank1, pivotCoords);
    if (pivotCoords[1] == matrix.cols - 1)
    {
        solutions.solutions.rows = solutions.solutions.cols = 0;
        return solutions;
    }

    GaussJordanForm(matrix, COMPLETE);
    printf("Gauss-Jordan form:\n");
    printMatrix(matrix);

    //ricavo i termini noti dopo la riduzione totale
    for (int i = 0; i < matrix.rows; i++)
    {
        solutions.freeTerms[i] = matrix.matrix[i][matrix.cols - 1];
    }

    //ricava le soluzioni
    solutions.solutions.rows = matrix.rows;
    solutions.solutions.cols = matrix.cols - rank1;
    solutions.solutions.matrix = buildMatrix(solutions.solutions.rows, solutions.solutions.cols, ZEROS);
    solutions.dimension = solutions.solutions.cols;

    order = sortPivots(matrix);
    for (int i = 0; i < rank1; i++)
    {
        for (int j = 0; j < matrix.cols - rank1; j++)
        {
            solutions.solutions.matrix[i][j] = - matrix.matrix[i][j + rank1];
        }
    }
    for(int k = rank1; k < solutions.solutions.rows; k++)
    {
        solutions.solutions.matrix[k][k - rank1] = 1;
    }

    for(int i = 0; i < matrix.cols; i++)
    {
        if (order[i] != i)
        {
            sortSolutions(solutions, order);
            break;
        }
    }

    return solutions;
}
