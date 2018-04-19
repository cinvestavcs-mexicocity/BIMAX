/*Tarea 4 Angélica Alejandra Serrano Rubio*/

#include "tiempo.h"

// Funcion que calcula diferencia en milisegundos usando struct timeval
double diferencia_milisegundos(struct timeval *ini, struct timeval *fin)
{
    return
    (double)(fin->tv_sec*1000 + (double)fin->tv_usec/1000) -
    (double)(ini->tv_sec*1000 + (double)ini->tv_usec/1000);

}
