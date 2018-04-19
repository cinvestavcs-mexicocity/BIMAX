/*Bimax Angélica Alejandra Serrano Rubio*/

/*Declaración de bibliotecas*/
#include "files.h"
#include "memory.h"

/* Lectura del vector en el archivo cfile */
int *readVectorTxt(char *fileName, int *nr)
{
    /* Abre el archivo para su lectura*/
    FILE *fp = fopen(fileName, "rt");
    int val;
    int i;

    /* Error no se puede abrir el archivo*/
    if (!fp)
        return(NULL);

    /* Obtiene la dimensión del vector*/
    fscanf(fp, "%d", nr);
    /* Aloca memoria dinámica */
    int *vec = createVector(*nr);
    /* Error no se pudo asignar la memoria al vector */
    if(vec==NULL)
        return(NULL);
    /* Lee los valores del vector */
    for(i=0; i<*nr; i++)
    {
        fscanf(fp, "%d", &val);
        vec[i] = val;
    }
    /* Cierra el archivo */
    fclose(fp);
    return vec;
}

int *readVector(char *fileName, int *nr)
{
    int *vec;
    /* Abre el archivo */
    FILE *fp = fopen(fileName, "rb");

    /* Error el archivo no se puede abrir */
    if(!fp)
        return(NULL);
    /* Lectura de la dimensión del vector*/
    fread(nr, sizeof(int), 1, fp);
    /* Aloca memoria dinámica para el vector*/
    vec = (int *) malloc( (*nr)*sizeof(int));
    /* Error no se pudo asignar la memoria al vector */
    if(vec==NULL)
        return(NULL);
    /* Lee los elementos del vector */
    fread(vec, sizeof(int), *nr, fp);
    /*Cierra el archivo*/
    fclose(fp);
    return(vec);
}

/* Imprime el vector en un archivo*/
int writeVector(int *vec, int dim, char *fileName)
{
    /* Crea el archivo donde va a escribie el vector */
    FILE *fp = fopen(fileName, "w");
    int i=0;

    /*Error no se puede crear el archivo*/
    if(!fp)
        return(1);
    /* Imprime la dimensión y los elementos del vector */
    fprintf(fp,"%d\n", dim);
    for(i=0; i<dim; i++)
        fprintf(fp,"%d\n",vec[i]);
    /*Cierra el archivo*/
    fclose(fp);
    return(0);
}

/* Imprime en la consola las entradas del vector */
void printVector(int *vec, int dim)
{
    int i;
    /*Imprime los valores del vector en consola*/
    for(i=0; i<dim; ++i)
        printf("%d   ", vec[i]);
    printf("\n");
}

/* Lee el valor de los parametros y los asigna a las variables */
void readParams(int argc, char **argv, char *FileName)
{
    /*Asigna el nombre al archivo*/
    if(argc>1)
        strcpy(FileName, argv[1]);
}

/* Lectura del vector en el archivo cfile */
int **readMatrixTxt(const char *fileName, int *nr, int *nc)
{
    /*Abre el archivo para su lectura*/
    FILE *fp = fopen(fileName, "rt");
    int val;
    int i, j;
    /* Error el archivo no se puede abrir */
    if (!fp)
        return(NULL);

    /* Obtiene las dimensiones de la matriz */
    fscanf(fp, "%d %d", nr, nc);
    /* Aloca memoria dinamica para la matriz */
    int **mat = createMatrixBloques(*nr, *nc);
    /* Lectura de los valores de la matriz */
    for(i=0; i<*nr; i++)
        for(j=0; j<*nc; j++)
        {
            fscanf(fp, "%d", &val);
            mat[i][j] = val;
        }
    /* Cierra el archivo */
    fclose(fp);
    return mat;
}

int **readMatrix(char *fileName, int *nr, int *nc)
{
    int **mat;
    /* Abre el archivo para su lectura*/
    FILE *fp = fopen(fileName, "rb");

    /* Error el archivo no se puede abrir*/
    if(!fp)
        return(NULL);
    /* Lectura del tamaño de la matriz */
    fread(nr, sizeof(int), 1, fp);
    fread(nc, sizeof(int), 1, fp);
    /* Se reserva memoria dinámicamente */
    mat = createMatrixBloques(*nr, *nc);
    /* Lectura de los datos */
    fread(mat[0], sizeof(int), (*nr)*(*nc), fp);
    /* Cierra el archivo */
    fclose(fp);
    return(mat);
}

/* Imprime la matriz en un archivo */
int writeMatrix(int **mat, int nr, int nc, char *fileName)
{
    /* Crea el archivo donde se va a escribir la matriz */
    FILE *fp = fopen(fileName, "w");
    int i=0, j=0;

    /* El archivo no se pudo crear */
    if(!fp)
        return(1);
    /* Imprime las dimenciones de la matriz y los valores de la matriz */
    fprintf(fp,"%d %d\n", nr, nc);
    for(i=0; i<nr; i++)
    {
        for(j=0; j<nc; j++)
            fprintf(fp,"%d ",mat[i][j]);
        fprintf(fp, "\n");
    }
    /* Cierra el archivo */
    fclose(fp);
    return(0);
}

/*Imprime la matriz en consola*/
void printMatrix(int **mat, int nr, int nc)
{
    int i, j;
    /* Imprime la matriz en consola */
    for(i=0; i<nr; ++i)
    {
        for(j=0; j<nc; ++j)
            printf("%d   ", mat[i][j]);
        printf("\n");
    }
}
