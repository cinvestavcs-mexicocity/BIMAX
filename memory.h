/*Bimax Angélica Alejandra Serrano Rubio*/

#ifndef MEMORY_H
#define MEMORY_H

/*Declaracion de bibliotecas*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

/* Aloca memoria para una matriz por medio de un solo bloque*/
int **createMatrixBloque(int,int);

/* Aloca memoria para una matriz por medio de bloques */
int **createMatrixBloques(int,int);

/* Aloca memoria para un vector */
int *createVector(int);

/* Libera memoria para una matriz*/
void freeMatrix(int **);

/* Libera memoria para una matriz de varios bloques*/
void freeMatrixBloques(int **, int);

/* Aloca memoria para estructura para filas*/
row *createRow(int, int);

/* Aloca memoria para estructura para columnas */
int **createCol(int, int);

/* Aloca memoria para estructura de intersección de columnas*/
int *createInt(int);

/* Libera memoria para estructura para filas*/
void freeRow(row *, int);

/* Libera memoria para estructura para columnas */
void freeCol(int **, int);

/* Libera memoria para estructura de intersección de columnas*/
void freeInt(int *);


#endif // MEMORY_H
