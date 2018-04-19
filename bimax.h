/*Bimax Angélica Alejandra Serrano Rubio*/
/*Código referencia Eckart Zitzler */

#ifndef BIMAX_H
#define BIMAX_H

/*Declaración de bibliotecas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int **Conditions;
int **Columns;
int *columnIntersection;
row *rows;

/*Valida que el número mínimo de filas y columnas sea mayor igual a 0*/
int ValidEntries(int *, int *);

/*Inicializa las estructuras necesarias*/
void Initialize(int, int, int*, int *);

/*Libera la memoria dinámica de las estructuras necesarias*/
void Finalize(int);

/*Selecciona una columna*/
void setColumn(int *, int, int);

/*Mezcla las columnas*/
void unsetColumn(int *, int, int);

/*Lee los valores de la matriz*/
void readExpressionMatrix(int, int, int **, int);

/*Función conquer*/
void conquer(int **, int, int, int, int, int, int, int, int, int, int, FILE *, int);

/*Escribe un bicluster en pantalla*/
void printBicluster(int **, int ,int, int *, int, int, int);

/*Escribe un bicluster en archivo*/
void writeBicluster(int **, int ,int, int *, int, int, int, FILE *);

/*Cuenta el número de filas seleccionadas para revisar si es mayor o igual al mínimo*/
int selectRows(int, int, int, int *, int, int, int);

/*Elige la división de las filas*/
int DivideRow(int, int, int, int);

/*Intercambia las filas de la estructura*/
void swapRows(int, int, int);

/*Contiene las columnas obligatorias*/
int containsColumns(int *, int, int);

/*Cuenta de columnas para ver si ya es mayor  o igual que el mínimo*/
int columnCount(int *, int, int);

/*Compara las columnas*/
int compareColumns(int *, int *, int);

/*Copia un conjunto de columnas*/
void copyColumnSet(int *, int *,int , int);

/*Intercepta un conjunto de columnas*/
void intersectColumnSets(int *, int *, int *, int);

/*Revisa si es conjunto*/
int isSet(int * , int, int);

/*Determina columnas en común*/
void determineColumnsInCommon(int, int, int *, int, int, int);

/*Algoritmo Bimax*/
int Bimax(int **,int, int, int, int, char*, int);
#endif  //BIMAX_H
