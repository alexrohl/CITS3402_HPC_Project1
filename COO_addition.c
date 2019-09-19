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
  if (Matrix1.n_rows != Matrix2.n_rows || Matrix1.m_columns != Matrix2.m_columns) {
    printf("Matrix Dimensions do not Match!\n");
    COO_Format null;
    return null;
  }

  int *values,*temp,*row_indices,*column_indices;
  COO_Format COO_Matrix1 = Matrix1.COO_Matrix;
  COO_Format COO_Matrix2 = Matrix2.COO_Matrix;
  COO_Format Result;
  /* values: The non-zero values stored in row-major order */
  values = malloc(sizeof(int));
  /*BUILD row_indices = [0, 1, 3, 3] the number of elements in each row */
  row_indices = malloc(sizeof(int));
  /*BUILD column_indices: Stores the column index of each non-zero element. */
  column_indices = malloc(sizeof(int));

  int non_zero_counter = 0;

  int * intvalues1 = (int*)COO_Matrix1.values;
  int * intvalues2 = (int*)COO_Matrix2.values;
  //Build resulting matrix
  int i;

  int last1 = COO_Matrix1.lenvalues;
  int last2 = COO_Matrix2.lenvalues;

  int COO_index1 = 0;
  int COO_index2 = 0;

  while (true) {
    int column_index1 = COO_Matrix1.column_indices[COO_index1];
    int column_index2 = COO_Matrix2.column_indices[COO_index2];
    int row_index1 = COO_Matrix1.row_indices[COO_index1];
    int row_index2 = COO_Matrix2.row_indices[COO_index2];
    int val1 = intvalues1[COO_index1];
    int val2 = intvalues2[COO_index2];
    //If matrix1 is spent, add matrix2 remaining elements to Result
    if (COO_index1 == last1) {
      for (COO_index2=COO_index2; COO_index2<last2;COO_index2++) {
        column_index2 = COO_Matrix2.column_indices[COO_index2];
        row_index2 = COO_Matrix2.row_indices[COO_index2];
        val2 = intvalues2[COO_index2];
        append_to_arrays(temp,values, column_indices, row_indices, val2, column_index2, row_index2, non_zero_counter);
        non_zero_counter++;
      }
      break;
    }

    //else matrix2 is spent, add matrix1 remaining elements to Results
    if (COO_index2 == last2) {
      for (COO_index1=COO_index1; COO_index1<last1;COO_index1++) {
        column_index1 = COO_Matrix1.column_indices[COO_index1];
        row_index1 = COO_Matrix1.row_indices[COO_index1];
        val1 = intvalues1[COO_index1];
        append_to_arrays(temp,values, column_indices, row_indices, val1, column_index1, row_index1, non_zero_counter);
        non_zero_counter++;
      }
      break;
    //row major order implies we check for column index first
    } else {

      //If index1 is smaller then add val1
      if (column_index1 < column_index2) {
        append_to_arrays(temp,values, column_indices, row_indices, val1, column_index1, row_index1, non_zero_counter);
        non_zero_counter++;
        COO_index1++;
      //If index2 is smaller then add val2
      } else if (column_index2 < column_index1) {
          append_to_arrays(temp,values, column_indices, row_indices, val2, column_index2, row_index2, non_zero_counter);
          non_zero_counter++;
          COO_index2++;
      //from now on column indices are the same...
      } else {
        //now check row index
        if (row_index1 < row_index2) {
          append_to_arrays(temp,values, column_indices, row_indices, val1, column_index1, row_index1, non_zero_counter);
          non_zero_counter++;
          COO_index1++;

        } else if (row_index2 < row_index1) {
            append_to_arrays(temp,values, column_indices, row_indices, val2, column_index2, row_index2, non_zero_counter);
            non_zero_counter++;
            COO_index2++;
        } else {
          //EXACT MATCH => ADD VALUES
          int NewVal = val1 + val2;
          append_to_arrays(temp,values, column_indices, row_indices, NewVal, column_index2, row_index1, non_zero_counter);
          non_zero_counter++;
          COO_index1++;
          COO_index2++;
        }
      }
    }
  }
  //format result
  Result.lenvalues = non_zero_counter;
  Result.values = values;
  Result.row_indices = row_indices;
  Result.column_indices = column_indices;
  /*
  print_array(Result.values, non_zero_counter, "values",);
  print_array(Result.column_indices , non_zero_counter, "column");
  print_array(Result.row_indices, non_zero_counter, "rows");
  */
  /* Free the pointers */
  /* free(values);
  free(column_indices);
  free(row_indices);
  */
  return Result;
}
