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
void append_to_arrays(int *temp,int *arr1, int *arr2, int*arr3, int val1, int val2, int val3, int index){
  printf("appending val %d, col %d, row %d, index %d\n",val1,val2,val3,index);
  /*append to values*/
  arr1[index]=val1;
  printf("here");
  temp=realloc(arr1,(index+2)*sizeof(int));
  printf("here");
  /*using temp*/
  if ( temp != NULL ) {
    arr1=temp;
  } else {
    free(arr1);
    printf("Error allocating memory!\n");
  }
  /*using temp*/

  /*append to arr2*/
  printf("here");
  arr2[index]=val2;
  printf("here");
  temp=realloc(arr2,(index+2)*sizeof(int));
  /*using temp*/
  if ( temp != NULL ) {
    arr2=temp;
  } else {
    free(arr2);
    printf("Error allocating memory!\n");
  }
  /*using temp*/

  /*append to arr3*/
  arr3[index]=val3;
  temp=realloc(arr3,(index+2)*sizeof(int));
  /*using temp*/
  if ( temp != NULL ) {
    arr3=temp;
  } else {
    free(arr3);
    printf("Error allocating memory!\n");
  }
  /*using temp*/
  printf("here");
  return;
}

/*Assumes we have an integer matrix*/
COO_Format get_COO_addition(COO_Format Matrix1, COO_Format Matrix2)
{
  if (Matrix1.num_rows != Matrix2.num_rows || Matrix1.num_columns != Matrix2.num_columns) {
    printf("Matrix Dimensions do not Match!\n");
    COO_Format null;
    return null;
  }

  int *values,*temp,*row_indices,*column_indices;
  COO_Format Result;
  /* values: The non-zero values stored in row-major order */
  values = malloc(sizeof(int));
  /*BUILD row_indices = [0, 1, 3, 3] the number of elements in each row */
  row_indices = malloc(sizeof(int));
  /*BUILD column_indices: Stores the column index of each non-zero element. */
  column_indices = malloc(sizeof(int));

  int non_zero_counter = 0;

  int * intvalues1 = (int*)Matrix1.values;
  int * intvalues2 = (int*)Matrix2.values;
  //Build resulting matrix
  int i;

  int last1 = Matrix1.lenvalues;
  int last2 = Matrix2.lenvalues;

  int COO_index1 = 0;
  int COO_index2 = 0;

  while (true) {
    int column_index1 = Matrix1.column_indices[COO_index1];
    int column_index2 = Matrix2.column_indices[COO_index2];
    int row_index1 = Matrix1.row_indices[COO_index1];
    int row_index2 = Matrix2.row_indices[COO_index2];
    int val1 = intvalues1[COO_index1];
    int val2 = intvalues2[COO_index2];
    //If matrix1 is spent, add matrix2 remaining elements to Result
    if (COO_index1 == last1) {
      for (COO_index2=COO_index2; COO_index2<last2;COO_index2++) {
        column_index2 = Matrix2.column_indices[COO_index2];
        row_index2 = Matrix2.row_indices[COO_index2];
        val2 = intvalues2[COO_index2];
        append_to_arrays(temp,values, column_indices, row_indices, val2, column_index2, row_index2, non_zero_counter);
        non_zero_counter++;
      }
      break;
    }

    //else matrix2 is spent, add matrix1 remaining elements to Results
    if (COO_index2 == last2) {
      for (COO_index1=COO_index1; COO_index1<last1;COO_index1++) {
        column_index1 = Matrix1.column_indices[COO_index1];
        row_index1 = Matrix1.row_indices[COO_index1];
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
  Result.num_rows = Matrix1.num_rows;
  Result.num_columns = Matrix1.num_columns;
  Result.lenvalues = non_zero_counter;
  Result.values = values;
  Result.row_indices = row_indices;
  Result.column_indices = column_indices;

  printf("ADDING\n");
  printf("non zero %d\n",non_zero_counter);
  printf("row_indices: [");
  for (i=0; i<non_zero_counter; i++) {
    printf("%d,", row_indices[i]);
  }
  printf("]\n");

  printf("column_indices: [");
  for (i=0; i<non_zero_counter; i++) {
    printf("%d,", column_indices[i]);
  }
  printf("]\n");

  printf("values: [");
  for (i=0; i<non_zero_counter; i++) {
    printf("%d,", values[i]);
  }
  printf("]\n");

  /* Free the pointers */
  /* free(values);
  free(column_indices);
  free(row_indices);
  */
  return Result;
}
