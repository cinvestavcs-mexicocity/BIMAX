/*Bimax Angélica Alejandra Serrano Rubio*/

#ifndef FILES_H
#define FILES_H

/*Declaracion de librerias*/
#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lectura del vector en el archivo cfile */
int *readVectorTxt(char *, int *);
int *readVector(char *, int *);

/* Imprime el vector en un archivo*/
int writeVector(int *, int, char *);

/* Imprime en la consola las entradas del vector */
void printVector(int *, int);

/* Lee el valor de los parametros y los asigna a las variables */
void readParams(int, char **, char *);

/* Lectura del vector en el archivo cfile */
int **readMatrixTxt(const char *, int *, int *);
int **readMatrix(char *, int *, int *);

/* Imprime la matriz en un archivo */
int writeMatrix(int **, int, int, char *);

/*Imprime la matriz en consola*/
void printMatrix(int **, int, int);

#endif // FILES_H
