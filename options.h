/*Bimax Angélica Alejandra Serrano Rubio*/

#ifndef OPTIONS_H
#define OPTIONS_H

/* Declaracion de bibliotecas */
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Parametros*/
#define PACKAGE    "BIMAX"
#define VERSION    "1.0.0"

/*Funcion que lee los parámetros de entrada*/
int ReadParameters(int, char **, char *, char *, int *, int *, int *);

/* Función que imprime la ayuda del programa*/
void PrintHelp(int);

#endif // OPTIONS_H
