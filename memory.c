/*Bimax Angélica Alejandra Serrano Rubio*/

/*Declaración de bibliotecas*/
#include "memory.h"

/*Almacena memoria en un solo bloque*/
int **createMatrixBloque(int nr, int nc)
{
    int i;
    int **Matrix=NULL;
    //Reservar memoria
    Matrix=(int **) malloc((nr)*sizeof(int *));
    /*Si no se pudo reservar memoria*/
    if(Matrix==NULL)
        return(NULL);
    /*Almacena memoria en un bloque*/
    Matrix[0]=(int *)malloc(nr*nc*sizeof(int));
    if(Matrix[0]==NULL)
        return(NULL);
    /*Genera un apuntador a cada inicio de fila*/
    for(i=1; i<=nr; i++)
        Matrix[i]=Matrix[i-1]+nc;
    return(Matrix);
}

/*Almacena memoria en varios blaques*/
int **createMatrixBloques(int nr, int nc)
{
    int i;
    int **Matrix=NULL;
    // Reservamos memoria
    Matrix = (int **) malloc( nr*sizeof(int *));
    if(Matrix==NULL)
        return(NULL);
    /*Genera distintos bloques de memoria*/
    for(i=0; i<nr; ++i)
        Matrix[i] = (int *) malloc( nc*sizeof(int));
    return(Matrix);
}

/*Almacena memoria para un vector*/
int *createVector(int n)
{
    int *Vector=NULL;
    /*Aloca memoria para un vector de n elementos de tipo int*/
    Vector=(int*)malloc(n*sizeof(int));
    if(Vector==NULL)
        return(NULL);
    return(Vector);
}

/* Libera memoria para una matriz de un solo bloque*/
void freeMatrix(int **mat)
{
    free(mat[0]);
    free(mat);
}

/* Libera memoria para una matriz de varios bloques*/
void freeMatrixBloques(int **mat, int nr)
{
    int i=0;
    for(i=0; i<nr; i++)
        free(mat[i]);
    free(mat);
}

/* Aloca memoria para estructura para filas*/
row *createRow(int nr, int nc)
{
    int i=0;
    row *str=NULL;
    str = malloc(sizeof(row) * nr);
    if (str == NULL)
        return(NULL);
    for (i=0;i<nr;i++)
    {
        str[i].originalRowNumber = i;
        str[i].columnSet = calloc(sizeof(int), nc);
        if (str[i].columnSet == NULL)
            return(NULL);
    }
    return(str);
}

/* Aloca memoria para estructura para columnas */
int **createCol(int nr, int nc)
{
    int i=0;
    int **str=NULL;
    str = calloc(sizeof(int *), nr);
    if (str == NULL)
        return(NULL);
    for (i=0;i<nr;i++)
    {
        str[i] = calloc(sizeof(int), nc);
        if (str[i] == NULL)
            return(NULL);
    }
    return(str);
}

/* Aloca memoria para estructura de intersección de columnas*/
int *createInt(int n)
{
    int *str=NULL;
    str = calloc(sizeof(int), n);
    if (str == NULL)
        return(NULL);
    return(str);
}

/* Libera memoria para estructura para filas*/
void freeRow(row *str, int nr)
{
    int i=0;
    for (i=0;i<nr;i++)
        free(str[i].columnSet);
    free(str);
}

/* Libera memoria para estructura para columnas */
void freeCol(int **str, int nr)
{
    int i=0;
    for (i=0;i<nr;i++)
        free(str[i]);
    free(str);
}

/* Libera memoria para estructura de intersección de columnas*/
void freeInt(int *str)
{
    free(str);
}
