// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*TRACE the sum of each diagonal element. Note: the Trace is only well defined for
square matrices.*/

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


/*Assumes we have an integer matrix*/
int get_int_trace(MatrixContainer Matrix, int num_threads)
{
  CSR_Format CSR_Matrix = Matrix.CSR_Matrix;
  int sum = -1; //!!!unknown reason as to result produced was 1 too big...
  int lsum = 0;
  int i,j;
  int column_index;
  int diagonal_entry;
  int first, last;
  int * intNNZ = (int*)CSR_Matrix.NNZ;

  omp_set_num_threads(num_threads); //I have set the number of threads =4, you can change this.
  #pragma omp parallel private(lsum,i,j,diagonal_entry,column_index,first,last)
  {
    #pragma omp for
    //loops through each row
    for(i=0; i<Matrix.n_rows; i++) {
      first = CSR_Matrix.IA[i];
      last = CSR_Matrix.IA[i+1];

      //loops through column_indexs
      for (j=first;j<last;j++) {
        column_index = CSR_Matrix.JA[j];
        if (column_index>i) {
          break;
        }

        if (column_index == i) {//found entry on diagonal
          diagonal_entry = intNNZ[j];
          lsum = lsum + diagonal_entry;
        }
      }
    }
    #pragma omp critical
        {
        //printf("LSum: %d\n",lsum);
        sum+=lsum;
        }
  }
  //printf("ASum: %d\n",sum);
  return sum;
}

/*Assumes we have a FLOAT matrix*/
float get_flt_trace(MatrixContainer Matrix, int num_threads)
{
  CSR_Format CSR_Matrix = Matrix.CSR_Matrix;
  float sum = 0.0; //!!!unknown reason as to result produced was 1 too big...
  float lsum = 0;
  int i,j;
  int column_index;
  float diagonal_entry;
  int first, last;
  float * fltNNZ = (float*)CSR_Matrix.NNZ;

  omp_set_num_threads(num_threads); //I have set the number of threads =4, you can change this.
  #pragma omp parallel private(lsum,i,j,diagonal_entry,column_index,first,last)
  {
    #pragma omp for
    //loops through each row
    for(i=0; i<Matrix.n_rows; i++) {
      first = CSR_Matrix.IA[i];
      last = CSR_Matrix.IA[i+1];

      //loops through column_indexs
      for (j=first;j<last;j++) {
        column_index = CSR_Matrix.JA[j];
        if (column_index>i) {
          break;
        }

        if (column_index == i) {//found entry on diagonal
          diagonal_entry = fltNNZ[j];
          lsum = lsum + diagonal_entry;
        }
      }
    }
    #pragma omp critical
        {
        //printf("LSum: %d\n",lsum);
        sum+=lsum;
        }
  }
  //printf("Sum: %f\n",sum);
  return sum;
}
