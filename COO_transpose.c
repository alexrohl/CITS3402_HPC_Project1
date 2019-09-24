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
COO_Format get_COO_transpose(MatrixContainer Matrix1,int num_threads)
{
  double t;
  t = omp_get_wtime();

  COO_Format Result;
  COO_Format COO_Matrix = Matrix1.COO_Matrix;
  int size = COO_Matrix.lenvalues;

  int *values,*row_indices,*column_indices;
  float *float_values;

  values = malloc( size * sizeof(int) );
  float_values = malloc( size * sizeof(int) );
  column_indices = malloc( size * sizeof(int) );
  row_indices = malloc( size * sizeof(int) );

  int non_zero_counter = 0;

  int i;
  int j;
  int changes;
  omp_set_num_threads(num_threads); //I have set the number of threads =4, you can change this.


  if (Matrix1.isInt) {
    int * old_values = (int*)COO_Matrix.values;

    for (i=0 ; i<size; i++){
      row_indices[i] = COO_Matrix.column_indices[i];
      column_indices[i] = COO_Matrix.row_indices[i];
      values[i] = old_values[i];
    }
    //print_int_array(row_indices,size, "new rown");
    //print_int_array(column_indices,size, "new column");
    //BUBBLE SORT TO ROW MAJOR ORDER

    for(i=0;i<size;i++)
    {
      #pragma omp parallel
      {
        #pragma omp for
        for(j = 0; j < size - 1; j = j + 2)
        {
          if(row_indices[j] > row_indices[j+1] )
          {
            int_swap(&column_indices[j], &column_indices[j+1]);
            int_swap(&row_indices[j], &row_indices[j+1]);
            int_swap(&values[j], &values[j+1]);
          } else if (row_indices[j] == row_indices[j+1] && (column_indices[j] > column_indices[j+1])) {
            int_swap(&column_indices[j], &column_indices[j+1]);
            int_swap(&row_indices[j], &row_indices[j+1]);
            int_swap(&values[j], &values[j+1]);
          }
        }
        #pragma omp for
        for(j = 1; j < size - 1; j = j + 2)
        {
          if( row_indices[j] > row_indices[j+1] )
          {
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
    }
    Result.values = values;
    //print_int_array(values,size, "new2 values");

  } else {
    //FLOATS

    float * old_values = (float*)COO_Matrix.values;

    for (i=0 ; i<size; i++){
      row_indices[i] = COO_Matrix.column_indices[i];
      column_indices[i] = COO_Matrix.row_indices[i];
      float_values[i] = old_values[i];
    }
    //print_int_array(row_indices,size, "new rown");
    //print_int_array(column_indices,size, "new column");
    //BUBBLE SORT TO ROW MAJOR ORDER
    for(i=0;i<size;i++)
    {
      #pragma omp parallel
      {
        #pragma omp for
        for(j = 0; j < size - 1; j = j + 2)
        {
          if(row_indices[j] > row_indices[j+1] )
          {
            int_swap(&column_indices[j], &column_indices[j+1]);
            int_swap(&row_indices[j], &row_indices[j+1]);
            float_swap(&float_values[j], &float_values[j+1]);
          } else if (row_indices[j] == row_indices[j+1] && (column_indices[j] > column_indices[j+1])) {
            int_swap(&column_indices[j], &column_indices[j+1]);
            int_swap(&row_indices[j], &row_indices[j+1]);
            float_swap(&float_values[j], &float_values[j+1]);
          }
        }
        #pragma omp for
        for(j = 1; j < size - 1; j = j + 2)
        {
          if( row_indices[j] > row_indices[j+1] )
          {
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
    }
    Result.values = float_values;
    //print_float_array(float_values,size, "new2 values");
  }

  Result.lenvalues = size;
  Result.row_indices = row_indices;
  Result.column_indices = column_indices;

  //print_int_array(Result.column_indices , size, "column");
  //print_int_array(Result.row_indices, size, "rows");
  printf("num:%d\n",num_threads);

  double time_taken = omp_get_wtime() - t;
  Result.time = time_taken;
  //printf("Time: %f\n",Result.time);
  return Result;
}
