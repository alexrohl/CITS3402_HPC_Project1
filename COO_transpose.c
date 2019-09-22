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
COO_Format get_COO_transpose(MatrixContainer Matrix1)
{
  clock_t t;
  t = clock();

  COO_Format Result;
  COO_Format COO_Matrix = Matrix1.COO_Matrix;
  int size = COO_Matrix.lenvalues;
  /*BUILD row_indices = [0, 1, 3, 3] the number of elements in each row */
  int row_indices[size];
  /*BUILD column_indices: Stores the column index of each non-zero element. */
  int column_indices[size];

  /* values: The non-zero values stored in row-major order */
  int values[size];

  /* values: The non-zero values stored in row-major order */
  float float_values[size];

  int non_zero_counter = 0;

  int i;
  int j;


  if (Matrix1.isInt) {
    int * old_values = (int*)COO_Matrix.values;

    for (i=0 ; i<size; i++){
      row_indices[i] = COO_Matrix.column_indices[i];
      column_indices[i] = COO_Matrix.row_indices[i];
      values = old_values[i];
    }
    //print_int_array(row_indices,size, "new rown");
    //print_int_array(column_indices,size, "new column");
    //BUBBLE SORT TO ROW MAJOR ORDER
    for (i = 0; i < size-1; i++) {
      // Last i elements are already in place
      for (j = 0; j < size-i-1; j++) {

        if (row_indices[j] > row_indices[j+1]) {
          int_swap(&column_indices[j], &column_indices[j+1]);
          int_swap(&row_indices[j], &row_indices[j+1]);
          int_swap(&values[j], &values[j+1]);

        } else if (row_indices[j] == row_indices[j+1] && (column_indices[j] > column_indices[j+1])) {
          int_swap(&column_indices[j], &column_indices[j+1]);
          int_swap(&row_indices[j], &row_indices[j+1]);
          int_swap(&values[j], &values[j+1]);
        }
      }
    }
    Result.values = values;
    //print_int_array(values,size, "new2 values");
  } else {
    //FLOATS
    float * old_values = (float*)COO_Matrix.values;

    for (i=0 ; i<size; i++){
      row_indices[i] = COO_Matrix.column_indices[i];
      column_indices[i] = COO_Matrix.row_indices[i];
      float_values = old_values[i];
    }
    //print_int_array(row_indices,size, "new rown");
    //print_int_array(column_indices,size, "new column");
    //BUBBLE SORT TO ROW MAJOR ORDER
    for (i = 0; i < size-1; i++) {
      // Last i elements are already in place
      for (j = 0; j < size-i-1; j++) {

        if (row_indices[j] > row_indices[j+1]) {
          int_swap(&column_indices[j], &column_indices[j+1]);
          int_swap(&row_indices[j], &row_indices[j+1]);
          float_swap(&float_values[j], &float_values[j+1]);

        } else if (row_indices[j] == row_indices[j+1] && (column_indices[j] > column_indices[j+1])) {
          int_swap(&column_indices[j], &column_indices[j+1]);
          int_swap(&row_indices[j], &row_indices[j+1]);
          float_swap(&float_values[j], &float_values[j+1]);
        }
      }
    }
    Result.values = float_values;
    //print_float_array(float_values,size, "new2 values");
  }

  Result.lenvalues = size;
  Result.row_indices = row_indices;
  Result.column_indices = column_indices;

  //print_int_array(Result.column_indices , size, "column");
  //print_int_array(Result.row_indices, size, "rows");


  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  Result.time = time_taken;
  printf("Time: %f\n",Result.time);
  return Result;
}
