// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*RECALL The most intuitive sparse matrix format specifies each non-zero element as a triple
        Ai,j = (i, j, val)
*/

#define MAX_LINE_LEN 256
//Function that accepts relevant pointers and dynamically appends values to the arrays

/*Assumes we have an integer matrix*/
COO_Format get_COO_addition(MatrixContainer Matrix1, MatrixContainer Matrix2)
{
  if (Matrix1.n_rows != Matrix2.m_columns || Matrix1.m_columns != Matrix2.n_rows) {
    printf("Matrix Dimensions do not Match!\n");
    COO_Format null;
    return null;
  }
