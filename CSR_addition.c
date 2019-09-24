// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*RECALL • NNZ: The non-zero values stored in row-major order (left to right, top to
bottom)
• IA: The number of elements in each row. An extra element IA[0] = 0 is
used by convention. This array can be used to index into the NNZ array
for each i-th row
• JA: Stores the column index of each non-zero element.*/

/* NNZ = [ 10 20 30 40 50 60 70 80 ]
   IA = [  0  2  4  7  8 ]
   JA = [  0  1  1  3  2  3  4  5 ]
The whole is stored as 21 entries.

IA splits the array NNZ into rows: (10, 20) (30, 40) (50, 60, 70) (80);
JA aligns values in columns: (10, 20, ...) (0, 30, 0, 40, ...)(0, 0, 50, 60, 70, 0) (0, 0, 0, 0, 0, 80).*/

#define MAX_LINE_LEN 256


/*Assumes we have an integer matrix*/
CSR_Format get_CSR_Addition(MatrixContainer Matrix1, MatrixContainer Matrix2)
{
  if (Matrix1.n_rows != Matrix2.n_rows || Matrix1.m_columns != Matrix2.m_columns) {
    printf("Matrix Dimensions do not Match!\n");
    CSR_Format null;
    return null;
  }
  double t;
  t = omp_get_wtime();

  CSR_Format CSR_Matrix1 = Matrix1.CSR_Matrix;
  CSR_Format CSR_Matrix2 = Matrix2.CSR_Matrix;
  CSR_Format Result;

  int size1 = CSR_Matrix1.lenNNZ;
  int size2 = CSR_Matrix2.lenNNZ;
  int num_rows = Matrix1.n_rows;

  int *NNZ,*IA,*JA;

  /* NNZ: The non-zero values stored in row-major order */
  NNZ = malloc((size1+size2)*sizeof(int));
  /*BUILD IA = [0, 1, 3, 3] the number of elements in each row */
  IA = malloc(num_rows*sizeof(int));
  /*BUILD JA: Stores the column index of each non-zero element. */
  JA = malloc((size1+size2)*sizeof(int));

  float *float_NNZ;
  float *float_temp;
  /* values: The non-zero values stored in row-major order */
  float_NNZ = malloc((size1+size2)*sizeof(float));

  int non_zero_counter = 0;
  int elements_in_row_counter = 0;
  int IA_index = 0;

  /*initialise IA*/
  IA[IA_index] = elements_in_row_counter;

  //Get integer values
  int * intNNZ1 = (int*)CSR_Matrix1.NNZ;
  int * intNNZ2 = (int*)CSR_Matrix2.NNZ;

  //Get float values
  float * fltNNZ1 = (float*)CSR_Matrix1.NNZ;
  float * fltNNZ2 = (float*)CSR_Matrix2.NNZ;

  //Build resulting matrix
  int element_to_add,index_to_add;

  //loops through each row in M1 and M2
  int i;
  for(i=0; i<Matrix1.n_rows; i++) {
    IA_index++;
    printf("row: %d\n",i);

    int first1 = CSR_Matrix1.IA[i];
    int last1 = CSR_Matrix1.IA[i+1];
    int first2 = CSR_Matrix2.IA[i];
    int last2 = CSR_Matrix2.IA[i+1];

    int j1 = first1;
    int j2 = first2;

    while (true) {
      int column_index1 = CSR_Matrix1.JA[j1];
      int column_index2 = CSR_Matrix2.JA[j2];
      //If matrix1 is spent, add matrix2 remaining elements to Result
      if (j1 == last1) {
        for(j2=j2;j2<last2;j2++) {
          printf("here j2:%d last: %d\n",j2,last2);
          element_to_add = intNNZ2[j2];
          index_to_add = CSR_Matrix2.JA[j2];

          NNZ[non_zero_counter]=element_to_add;
          JA[non_zero_counter]=index_to_add;

          non_zero_counter++;
          elements_in_row_counter++;
        }
        break;
      }

      //else matrix2 is spent, add matrix1 remaining elements to Results
      if (j2 == last2) {
        for(j1=j1;j1<last1;j1++) {
          printf("here j1:%d last: %d\n",j1,last1);
          element_to_add = intNNZ1[j1];
          index_to_add = CSR_Matrix1.JA[j1];

          NNZ[non_zero_counter]=element_to_add;
          JA[non_zero_counter]=index_to_add;

          non_zero_counter++;
          elements_in_row_counter++;
        }
        break;
      } else {

        //If index1 is smaller
        if (column_index1 < column_index2) {
          printf("here j2:%d last: %d\n",j2,last2);
          element_to_add = intNNZ1[j1];
          index_to_add = column_index1;
          j1++;

        //If index2 is smaller
        } else if (column_index2 < column_index1) {
          printf("here j2:%d last: %d\n",j2,last2);
          element_to_add = intNNZ2[j2];
          index_to_add = column_index2;
          j2++;

        //if indexs are the same
        } else {
          printf("here j2:%d last: %d\n",j2,last2);
          element_to_add = intNNZ1[j1] + intNNZ2[j2];
          index_to_add = column_index1;
          j1++;
          j2++;
        }

        NNZ[non_zero_counter]=element_to_add;
        JA[non_zero_counter]=index_to_add;

        non_zero_counter++;
        elements_in_row_counter++;

      }
    }
    //append number_of_elements in row to result
    IA[IA_index]=elements_in_row_counter;

  }
  Result.lenNNZ = non_zero_counter;
  Result.NNZ = NNZ;
  Result.IA = IA;
  Result.JA = JA;

  print_int_array(Result.NNZ, non_zero_counter, "Result");
  print_int_array(Result.IA, num_rows+1, "IA");
  print_int_array(Result.JA, non_zero_counter, "JA");

  double time_taken = omp_get_wtime()-t;
  Result.time = time_taken;
  return Result;
}
