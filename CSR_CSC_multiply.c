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
CSR_Format get_CSR_CSC_multiply(MatrixContainer Matrix1, MatrixContainer Matrix2)
{
  if (Matrix1.n_rows != Matrix2.m_columns || Matrix1.m_columns != Matrix2.n_rows) {
    printf("Matrix Dimensions do not Match!\n");
    CSR_Format null;
    return null;
  }
  double t = omp_get_wtime();
  CSR_Format CSR_Matrix = Matrix1.CSR_Matrix;
  CSC_Format CSC_Matrix = Matrix2.CSC_Matrix;
  CSR_Format Result;

  int num_rows = Matrix1.n_rows;
  int num_cols = Matrix2.m_columns;

  int *NNZ,*IA,*JA,*temp;

  /* NNZ: The non-zero values stored in row-major order */
  NNZ = malloc(sizeof(int));
  /*BUILD IA = [0, 1, 3, 3] the number of elements in each row */
  IA = malloc(sizeof(int));
  /*BUILD JA: Stores the column index of each non-zero element. */
  JA = malloc(sizeof(int));

  float *float_NNZ;
  float *float_temp;
  /* values: The non-zero values stored in row-major order */
  float_NNZ = malloc(sizeof(float));

  int non_zero_counter = 0;
  int elements_in_row_counter = 0;

  /*initialise IA*/
  IA[0] = elements_in_row_counter;
  //Get integer values
  int * intNNZ_CSR = (int*)CSR_Matrix.NNZ;
  int * intNNZ_CSC = (int*)CSC_Matrix.NNZ;

  int i,j;
  //LOOP THROUGH EACH ROW
  for(i=0; i<Matrix1.n_rows; i++) {
    printf("row: %d\n",i);
    int row_first = CSR_Matrix.IA[i];
    int row_last = CSR_Matrix.IA[i+1];

    for(j=0; j<num_cols; j++) {
      printf("rcol: %d\n",j);
      int col_first = CSC_Matrix.IA[j];
      int col_last = CSC_Matrix.IA[j+1];

      int i1 = row_first;
      int j1 = col_first;
      int cell_result = 0;
      while (true) { //multiplying row on column...
        //If CSRmatrix is spent, we are done as the rest is zeros
        if (i1 == row_last) {
          break;
        }

        //else CSC_matrix is spent, we are done as the rest is zeros
        else if (j1 == col_last) {
          break;

        } else {
          int row_index = CSR_Matrix.JA[i1];
          int column_index = CSC_Matrix.JA[j1];

          //If row index is smaller add zero...
          if (row_index < column_index) {
            i1++;

          //If index2 is smaller
        } else if (column_index < row_index) {
            j1++;

          //if indexs are the same
          } else {
            cell_result += intNNZ_CSR[i1] * intNNZ_CSC[j1];
            printf("row ind: %d, row val: %d, col ind: %d, col val: %d\n",i1,intNNZ_CSR[i1],j1,intNNZ_CSC[j1]);
            j1++;
            i1++;
          }
        }
      }
      //cell result is calculated...
      if (cell_result == 0) {
        continue;
        //computed a zero so we skip
      }
      else {
        NNZ = append_int_to_array(temp, NNZ, cell_result, non_zero_counter);
        JA = append_int_to_array(temp, JA, j, non_zero_counter);
        non_zero_counter++;

      }
    }
    //After each row is computed...
    IA = append_int_to_array(temp, IA, non_zero_counter, i+1);
  }
  Result.lenNNZ = non_zero_counter;
  Result.IA = IA;
  Result.JA = JA;
  Result.NNZ = NNZ;
  print_int_array(Result.IA, num_rows+1, "IA");
  print_int_array(Result.JA, non_zero_counter, "JA");
  print_int_array(Result.NNZ, non_zero_counter, "NNZ");


  double time_taken = omp_get_wtime() - t;
  Result.time = time_taken;
  printf("Time: %f\n",Result.time);
  return Result;
}
