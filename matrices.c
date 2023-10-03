#include <stdio.h>
#include <stdlib.h>
#define ZEROS 1
#define EMPTY 0

float **buildMatrix(int rows, int cols, int zeros)
{ // riceve in input righe e colonne, restituisce un array di array (o un pointer a una sequenza di pointers che puntano a sequenze di interi)

    float **matrix;
    matrix = malloc(rows * sizeof(*matrix));

    for (int i = 0; i < rows; i++)
    {

        matrix[i] = malloc(cols * sizeof(*matrix[i]));

        for (int j = 0; j < cols; j++)
        {

            if (!zeros)
            {
                int k;
                printf("Inserisci il valore M[%d][%d]: ", i, j);
                scanf("%d", &k);

                matrix[i][j] = k;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}

void printMatrix(float **matrix, int rows, int cols)
{ // stampa una matrice formattata leggibilmente

    for (int i = 0; i < rows; i++)
    {
        printf("| ");

        for (int j = 0; j < cols; j++)
        {
            printf("%02.2f ", matrix[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

void dumpMatrix(float **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

float **traspose(float **matrix, int rows, int cols, float **trasposed)
{ // l'ultimo argomento è il template della trasposta vuoto (dimensioni cols*rows)

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            trasposed[j][i] = matrix[i][j];
        }
    }
    return trasposed;
}

float **dotProduct(float **product, float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2)
{ // il primo argomento è il template per il prodotto, ha dimensioni rows1*cols2

    if (cols1 != rows2)
    {
        printf("Le due matrici non sono conformabili");

        // per il flag di ritorno
        float a;
        float *b = &a;
        float **ptr = &b;

        return ptr;
    }

    ;
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

void multiplyRow(float **matrix, int row, int cols, float factor)
{
    for (int j = 0; j < cols; j++)
    {
        matrix[row][j] *= factor;
    }
}

void combineRows(float **matrix, int row1, int row2, float factor, int cols) //<-- bug here?
{                                                                            // somma row2*factor a row1 (i cambiamenti avvengono in row1)
    for (int j = 0; j < cols; j++)
    {
        matrix[row1][j] += factor * matrix[row2][j];
    }
    printf("\n");
}

void swapRows(float **matrix, int row1, int row2, int cols)
{ // scambia di posti riga 1 e riga 2
    float temp;

    for (int i = 0; i < cols; i++)
    {
        temp = matrix[row2][i];
        matrix[row2][i] = matrix[row1][i];
        matrix[row1][i] = temp;
    }
}

void echelonForm(float **matrix, int rows, int cols)
{ // funzione per la riduzione a scala di una matrice

    // prototipo di funzione con scope minimo
    void firstNonZero(float **matrix, int rows, int cols, int startingRow, int coords[2]);

    int i;
    int pivotCol;
    int nonZeroRow = 0; // contiene l'indice della riga con primo elemento non nullo, in ordine di colonna
    int row = 0;        // indica la riga alla quale si sta lavorando
    int coords[2];      // array delle coordinate del pivot sul quale si sta lavorando
    float coefficient;

    while (row < rows)
    {
        firstNonZero(matrix, rows, cols, row, coords);
        nonZeroRow = coords[0];
        pivotCol = coords[1];

        if (nonZeroRow != row)
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

void firstNonZero(float **matrix, int rows, int cols, int startingRow, int coords[2])
{ // ritorna la riga alla quale si trova il primo elemento diverso da zero muovendosi colonna per colonna, a partire dalla riga passata come ultimo argomento

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

    coords[0] = rows + 1;
    coords[1] = cols + 1;
    return; // se non trova elementi non-zero, ritorna una riga fuori dallo scope (triggerando la condizione sentinella)
}
