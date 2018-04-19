/*Bimax Angélica Alejandra Serrano Rubio */
/*Código referencia Eckart Zitzler */

/*Declaración de bibliotecas*/
#include "bimax.h"
#include "memory.h"

/*Selecciona las columnas (suma)*/
void setColumn(int *columnSet, int  column, int Bits)
{
    /*Corrimiento a la izquierda*/
    int temp = 1 << (column % Bits);
    /*Almacena la union de conjuntos*/
    columnSet[column / Bits] |= temp;
}

/*Mezcla las columnas (complemento)*/
void unsetColumn(int *columnSet, int column, int Bits)
{
    /*Complemento a uno de la union de dos conjuntos*/
    int temp = ~(~(columnSet[column / Bits]) | (1 << (column % Bits)));
    /*Almacena la intersección de conjuntos*/
    columnSet[column / Bits] &= temp;
}

/*Revisa si es conjunto*/
int isSet(int *columnSet, int  column, int Bits)
{
    /*Corrimiento a la izquierda*/
    int  temp = 1 << (column % Bits);
    /*Verifica que la intersección de conjuntos sea distinta de vacio -> conjunto*/
    return ((columnSet[column / Bits] & temp) != 0);
}

/*Determina columnas en común mediante intersección de columnas*/
void determineColumnsInCommon(int firstRow, int lastRow, int *sharedColumnSet, int NoBs, int noCols, int noRows)
{
    int i=0;
    int j=0;
    for (i=0; i<NoBs; i++)
    {
        sharedColumnSet[i] = -1;
        /*Intersección de las columnas de acuerdo a la fila*/
        for (j=firstRow;j<=lastRow;j++)
            sharedColumnSet[i] &= rows[j].columnSet[i];
    }
}

/*Cuenta de columnas para ver si ya es mayor o igual que el mínimo*/
int columnCount(int *columnSet, int NoBs, int Bits)
{
    int i=0;
    int counter=0;
    int temp=0;
    int j=0;

    for (i=0;i<NoBs;i++)
    {
        temp = columnSet[i];
        /*Si el valor de la columna es diferente de 0*/
        if (temp!=0)
            /*Por cada bit realiza corrimiento a la derecha hasta que el número sea 0*/
            for(j=0;j<Bits;j++)
            {
                /*Cuenta la cantidad de 1's en la columna*/
                if (temp & 1)
                    counter++;
                temp>>=1;
            }
    }
    return counter;
}

/*Compara las columnas*/
int compareColumns(int *columnSetA, int *columnSetB, int NoBs)
{
    int i=0;
    int contained=1;
    int disjoint=1;
    int sharedColumns=0;

    for(i=0; i<NoBs; i++)
    {
        /*Por teoría de conjuntos*/
        /*Obtiene la intersección entre el conjunto A, conjunto B*/
        sharedColumns = columnSetA[i] & columnSetB[i];
        /*Obtiene la union de dos conjuntos y revisa si el conjunto A contiene al conjunto B*/
        if ((sharedColumns | columnSetB[i]) != sharedColumns )
            contained = 0;
        /*Revisa si existen elementos en la intersección*/
        if (sharedColumns != 0)
            disjoint = 0;
    }
    /*Conjunto vacio*/
    if(contained && disjoint)
        return -2;
    /*Conjunto B es subconjunto de A*/
    if (contained)
        return -1;
    /*Conjuntos disjuntos*/
    if (disjoint)
        return 1;
    /*Conjunto B es mas grande que conjunto A y la intersección es no vacía */
    return 0;
}

/*Copia un conjunto de columnas*/
void  copyColumnSet(int *columnSet, int *columnSetDest, int Mode, int NoBs)
{
    int i=0;
    for(i=0; i<NoBs; i++)
        /*Complemento*/
        if (Mode)
            columnSetDest[i] = ~columnSet[i];
    /*Identidad*/
        else
            columnSetDest[i] = columnSet[i];
}

/*Intersección de conjuntos de columnas*/
void  intersectColumnSets(int *columnSetA, int *columnSetB, int *columnSetDest, int NoBs)
{
    int  i=0;
    /*Obtiene la intersección entre conjunto A y conjunto B*/
    for(i=0; i<NoBs; i++)
        columnSetDest[i] = columnSetA[i] & columnSetB[i];
}

/*Contiene las columnas*/
int containsColumns(int *columnSet, int  noSets, int NoBs)
{
    int contains=1;
    int j=0;
    int i=0;

    for(i=0;i<noSets;i++)
        /*Si no existe intersección*/
        if((Columns[i][NoBs - 1] & columnSet[NoBs - 1])  == 0)
        {
            j=NoBs-2;
            while (j >= 0 && (Columns[i][j] & columnSet[j]) == 0)
                j--;
            if(j<0)
            {
                contains=0;
                i=noSets;
            }
        }
    return contains;
}

/*Intercambia las filas*/
void  swapRows(int a, int b, int noRows)
{
    /*Utilizando el operador xor exclusivo*/
    if (a != b && a >= 0 && a < noRows && b >= 0 && b < noRows)
    {
        rows[a].originalRowNumber ^= rows[b].originalRowNumber;
        rows[b].originalRowNumber ^= rows[a].originalRowNumber;
        rows[a].originalRowNumber ^= rows[b].originalRowNumber;

        int *tempColumnSet = rows[a].columnSet;
        rows[a].columnSet = rows[b].columnSet;
        rows[b].columnSet = tempColumnSet;
    }
}

/*Elige la división de las filas similares*/
int DivideRow(int firstRow, int lastRow, int level, int NoBs)
{
    int i=0;
    /*Compara una columna con el resto de las columnas*/
    for(i=firstRow; compareColumns(rows[i].columnSet, Conditions[level], NoBs)<0; i++);
    /*Si se encontro una columna similar regresa el indice*/
    if(i<=lastRow)
        return i;
    /*En caso contrario regresa la fila con la que se comparo*/
    return firstRow;
}

/*Cuenta el número de filas seleccionadas para revisar si es mayor o igual al mínimo*/
int selectRows(int  firstRow, int  lastRow, int  level, int  *overlapping, int noRows, int noCols, int NoBs)
{
    int  selected = 0;
    *overlapping = 0;
    while( firstRow <= lastRow)
    {
        int Compare=compareColumns(Conditions[level], rows[firstRow].columnSet, NoBs);
        switch (Compare)
        {
        /*Intercambia columnas entre conjuntos disjuntos y vacios*/
        case -2:
        case 1:
            swapRows(lastRow, firstRow, noRows);
            lastRow--;
            break;
            /*Existe sobreslapes entre los conjuntos*/
        case 0:
            *overlapping = 1;
            /*Un conjunto es subconjunto de otro*/
        default:
            selected++;
            firstRow++;
            break;
        }
    }
    return selected;
}

/*Funcion conquer RECURSIVA*/
void  conquer(int **matrix, int firstRow, int  lastRow, int  level, int noSets, int noCols, int noRows, int minCols, int minRows, int NoBs, int Bits, FILE *Output, int type)
{
    int overlapping=0;
    int splitRow=0;
    int noSelectedRows=0;

    /*Determina si hay columnas en comun*/
    if (firstRow >= 0 && lastRow >= firstRow && lastRow < noRows)
        determineColumnsInCommon(firstRow, lastRow, columnIntersection, NoBs, noCols, noRows);

    /*Imprime los biclusters obtenidos -> resultado final (Conjunto B es subconjunto de A)*/
    if (compareColumns(columnIntersection, Conditions[level], NoBs) == -1)
    {
        if(type==1)
            printBicluster(matrix, firstRow, lastRow, columnIntersection, noCols, noRows, Bits);
        else if(type==2)
            writeBicluster(matrix, firstRow, lastRow, columnIntersection, noCols, noRows, Bits, Output);
        else if(type==3)
        {
            printBicluster(matrix, firstRow, lastRow, columnIntersection, noCols, noRows, Bits);
            writeBicluster(matrix, firstRow, lastRow, columnIntersection, noCols, noRows, Bits, Output);
        }
    }
    /*Funcion recursiva*/
    else
    {
        /*Divide las filas*/
        splitRow = DivideRow(firstRow, lastRow, level, NoBs);
        /*Intersección de columnas*/
        intersectColumnSets(Conditions[level],   rows[splitRow].columnSet, Conditions[level + 1], NoBs);
        /*Si el número de columas es mayor al mínimo*/
        if (columnCount(Conditions[level + 1], NoBs, Bits) >= minCols && containsColumns(Conditions[level + 1], noSets, NoBs))
        {
            /*Verifica que el número de filas seleccionadas sea mayor que el mínimo*/
            noSelectedRows = selectRows(firstRow, lastRow, level + 1, &overlapping, noRows, noCols, NoBs);
            /*Vuelve a dividir el conjunto de columnas si el número de filas seleccionadas es mayor al mínimo*/
            if (noSelectedRows >= minRows)
                conquer(matrix, firstRow, firstRow + noSelectedRows - 1, level + 1, noSets, noCols, noRows, minCols, minRows, NoBs, Bits, Output, type);
        }
        /*Copia el conjunto de columnas*/
        copyColumnSet(Conditions[level + 1], Conditions[level + 1], 1, NoBs);
        /*Intersección entre conjuntos de columnas*/
        intersectColumnSets(Conditions[level], Conditions[level + 1], Conditions[level + 1], NoBs);
        /*Si existe overlapping entre conjuntos*/
        if (overlapping)
        {
            /*Copia el conjunto de columnas y aumenta el contador de conjuntos*/
            copyColumnSet(Conditions[level + 1], Columns[noSets],0, NoBs);
            noSets++;
        }
        /*Seleccion de filas*/
        noSelectedRows = selectRows(firstRow, lastRow, level + 1, &overlapping, noRows, noCols, NoBs);
        /*Copia el conjunto de columas*/
        copyColumnSet(Conditions[level], Conditions[level + 1], 0, NoBs);
        /*Si el número de filas seleccionadas es mayor al minimo elegido por el usuario, se vuelve a hacer la partición*/
        if (noSelectedRows >= minRows)
            conquer(matrix, firstRow, firstRow + noSelectedRows - 1, level + 1, noSets, noCols, noRows, minCols, minRows, NoBs, Bits, Output, type);
    }
}

/*Inicializa las estructuras necesarias*/
void Initialize(int noRows, int noCols, int *Bits, int *NoBs)
{
    int i=0;
    /*Obtiene el tamaño de bits*/
    for(i=1;i!=0;i<<=1)
        (*Bits)++;
    /*Calcula el tamaño de memoria que se va a almacenar*/
    if(noCols < *Bits || noCols == *Bits)
        *NoBs=1;
    else
    {
        *NoBs = (noCols / *Bits);
        if(noCols % *Bits != 0)
            *NoBs += 1;
    }

    /*Aloca memoria dinámica*/
    rows = createRow(noRows, *NoBs);
    Conditions = createCol(noRows+1, *NoBs);
    Columns = createCol(noRows+1, *NoBs);
    columnIntersection = createInt(*NoBs);

    /*Inicializa la union entre las columnas*/
    for (i = 0; i < noCols; i++)
        setColumn(Conditions[0], i, *Bits);
}

/*Lee los valores de la matriz y discrimina los valores 0´s o 1´s*/
void readExpressionMatrix(int noRows, int noCols, int **matrix, int Bits)
{
    int i=0;
    int j=0;
    for(i=0;i<noRows;i++)
        for(j=0;j<noCols;j++)
            /*Si el valor es 1, union de columnas*/
            if (matrix[i][j])
                setColumn(rows[i].columnSet, j, Bits);
    /*Si el valor es 0, intersección de columnas*/
            else
                unsetColumn(rows[i].columnSet, j, Bits);
}

/*Funcion que escribe un bicluster*/
void printBicluster(int **matrix, int  firstRow, int  lastRow, int *columnSet, int noCols, int noRows, int Bits)
{
    static int  biclusterCounter = 0;
    int i=0;
    int j=0;
    int k=0;

    biclusterCounter++;
    printf("\nBicluster: %d\n", biclusterCounter);
    printf("Genes: ");
    for(i=firstRow;i<=lastRow;i++)
        printf("%d\t", rows[i].originalRowNumber + 1);
    printf("\nConditions: ");
    for(i=0;i<noCols;i++)
        if (isSet(columnSet, i, Bits))
            printf("%d\t", i + 1);
    printf("\n");
    /*Imprime la matriz*/
    for(i=0;i<noRows;i++)
        for(k=firstRow;k<=lastRow;k++)
            if(rows[k].originalRowNumber == i)
            {
                for (j=0;j<noCols;j++)
                    if (isSet(columnSet, j, Bits))
                        printf("%d ", matrix[i][j]);
                printf("\n");
            }
}

/*Funcion que escribe un bicluster*/
void  writeBicluster(int **matrix, int  firstRow, int  lastRow, int *columnSet, int noCols, int noRows, int Bits, FILE *output)
{
    static int biclusterCounter = 0;
    int i=0;
    int j=0;
    int k=0;
    biclusterCounter++;
    fprintf(output,"\nBicluster: %d\n", biclusterCounter);
    fprintf(output,"Genes: ");
    for(i=firstRow;i<=lastRow;i++)
        fprintf(output,"%d\t", rows[i].originalRowNumber + 1);
    fprintf(output,"\nConditions: ");
    for(i=0;i<noCols;i++)
        if (isSet(columnSet, i, Bits))
            fprintf(output,"%d\t", i + 1);
    fprintf(output,"\n");

    /*Imprime la matriz*/
    for(i=0;i<noRows;i++)
        for(k=firstRow;k<=lastRow;k++)
            if(rows[k].originalRowNumber == i)
            {
                for (j=0;j<noCols;j++)
                    if (isSet(columnSet, j, Bits))
                        fprintf(output,"%d ", matrix[i][j]);
                fprintf(output,"\n");
            }
}

/*Valida que el número mínimo de filas y columnas sea mayor igual a 0*/
int ValidEntries(int *minRows, int *minCols)
{
    /*Verifica que el tamaño dado por el usuario para cada bicluster sea mayor igual a 1*/
    if(*minRows<1)
        *minRows=1;
    if(*minCols<1)
        *minCols=1;
    return 0;
}

/*Libera la memoria dinámica de las estructuras necesarias*/
void Finalize(int noRows)
{
    /*Libera memoria dinámica*/
    freeRow(rows, noRows);
    freeCol(Conditions, noRows+1);
    freeCol(Columns, noRows+1);
    freeInt(columnIntersection);
}

/*Algoritmo Bimax*/
int Bimax(int **matrix, int noCols, int noRows, int minCols, int minRows, char *FileName, int type)
{
    int Bits=0;
    int NoBs=0;

    /*Inicializa las estructuras*/
    Initialize(noRows, noCols, &Bits, &NoBs);
    /*Archivo que escribe la salida*/
    FILE *output=NULL;
    output=fopen(FileName, "w");
    /*Divide la matriz*/
    readExpressionMatrix(noRows, noCols, matrix, Bits);
    /*Encuentra coincidencias de manera recursiva*/
    conquer(matrix, 0, noRows-1, 0, 0, noCols, noRows, minCols, minRows, NoBs, Bits, output, type);
    /*Cierra el archivo*/
    fclose(output);
    /*Libera memoria dinámica*/
    Finalize(noRows);
    return 0;
}
