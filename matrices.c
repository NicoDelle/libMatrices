#include <stdio.h>
#include <stdlib.h>
# define ZEROS 1
#define EMPTY 0

float **buildMatrix(int rows, int cols, int zeros) {//riceve in input righe e colonne, restituisce un array di array (o un pointer a una sequenza di pointers che puntano a sequenze di interi)

    float **matrix;
    matrix = malloc(rows * sizeof(*matrix));
    
    for(int i = 0; i < rows; i++){
        
        matrix[i] = malloc(cols * sizeof(*matrix[i]));

        for(int j = 0; j < cols; j++) {
            
            if(!zeros) {
                int k;
                printf("Inserisci il valore M[%d][%d]: ", i, j);
                scanf("%d", &k);

                matrix[i][j] = k;
            }
            else {
                matrix[i][j] = 0;
            }
        }
        
    }

    return matrix;
}

void printMatrix(float **matrix, int rows, int cols) {//stampa una matrice formattata leggibilmente
    
    for(int i = 0; i < rows; i++) {
        printf("| ");

        for(int j = 0; j < cols; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("|\n");
    }
}

void dumpMatrix(float **matrix, int rows) {
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

float **traspose(float **matrix, int rows, int cols, float **trasposed) {//l'ultimo argomento è il template della trasposta vuoto (dimensioni cols*rows)

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            trasposed[j][i] = matrix[i][j];
        }
    }
    return trasposed;
}

float **dotProduct(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2) {

    if(cols1 != rows2) {
        printf("Le due matrici non sono conformabili");

        //per il flag di ritorno
        float a;
        float *b = &a;
        float **ptr = &b;

        return ptr;
    }

    float **product;
    product = buildMatrix(rows1, cols2, ZEROS);

    for(int i = 0; i < rows1; i++) {
        for(int j = 0; j < cols2; j++) {
            for(int k = 0; k < cols1; k++) {
                product[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }

    return product;
}

void multiplyRow(float **matrix, int row, int cols, float factor) {
    for (int j = 0; j < cols; j++)
    {
        matrix[row][j] *= factor;
    }
}

void combineRows(float **matrix, int row1, int row2, int factor, int cols) {//somma row2*factor a row1 (i cambiamenti avvengono in row1)
    for (int j = 0; j < cols; j++)
    {
        matrix[row1][j] += factor * matrix[row2][j];
    }
}

void swapRows(float **matrix, int row1, int row2, int cols) {//scambia di posti riga 1 e riga 2

    float *tempPtr;
    tempPtr = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = tempPtr;
    
}