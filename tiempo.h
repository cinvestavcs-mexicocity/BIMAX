/*Tarea 4 Angélica Alejandra Serrano Rubio*/

#ifndef TIEMPO_H
#define TIEMPO_H
#include <sys/time.h>

// Funcion que calcula diferencia en milisegundos usando struct timeval
double diferencia_milisegundos(struct timeval *ini, struct timeval *fin);

#endif // TIEMPO_H
