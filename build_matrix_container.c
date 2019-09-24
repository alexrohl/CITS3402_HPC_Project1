// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*return an array of the correct size and type*/
/*• Datatype: ”int” or ”float”
• Number of rows: An integer n > 0
• Number of columns: An integer m > 0
• n × m space-separated integers/floats representing each value*/

/*READ DIRECTLY INTO SPARSE MATRIX FORMAT*/
/*The most intuitive sparse matrix format specifies each non-zero element as a triple
        Ai,j = (i, j, val)
*/


#define MAX_LINE_LEN 256
/*
struct MatrixContainer {
    int isInt;
    int n_rows;
    int m_columns;
    COO_Format COO_Matrix;
    CSR_Format CSR_Matrix;
    CSC_Format CSC_Matrix;
};

typedef struct MatrixContainer MatrixContainer;
*/

MatrixContainer get_type(char *filename)
{
    printf("Building matrix container for %s\n",filename);
    MatrixContainer Result;
    strcpy(Result.name,filename);

    int n; /*Number of rows: An integer n > 0*/
    int m; /*Number of columns: An integer m > 0*/
    int is_int;

    FILE *fp = fopen(filename, "r"); /* should check the result */
    char type[MAX_LINE_LEN];

    float f_elem;
    int i_elem;

    /*read in type of matrix*/
    fscanf(fp, "%s", type);

    if (strncmp(type, "int", 3) == 0) {
      is_int = true;
    } else {
      is_int = false;
    }
    Result.isInt = is_int;

    /*read in n and m*/
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);
    Result.n_rows = n;
    Result.m_columns = m;

    //Build other matrix types COO,CSR CSC
    printf("Building COO_matrix for %s\n",filename);
    Result.COO_Matrix = get_COO_Matrix(filename,is_int,n,m);

    printf("Building CSR_matrix for %s\n",filename);
    Result.CSR_Matrix = get_CSR_Matrix(filename,is_int,n,m);

    printf("Building CSC_matrix for %s\n",filename);
    Result.CSC_Matrix = get_CSC_Matrix(get_COO_transpose(Result,1),is_int,n,m);



    return Result;
}
