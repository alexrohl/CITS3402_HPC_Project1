// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*return an array of the correct size and type*/
/*The compressed sparse column format is very similar to CSR format except
the non-zero values are stored in a column-wise ordering, the IA array corresponds to the extent of each column and the JA array provides row indices. For
example, the matrix,
X =
0 0 1
3 0 2
0 0 0
becomes
NNZ = [3, 1, 2]
IA = [0, 1, 1, 3]
JA = [1, 0, 1]
*/
#define MAX_LINE_LEN 256
/*note the void definition of NNZ since we don't know if it contains ints or floats*/


//Accepts transposed COO matrix
CSC_Format get_CSC_Matrix(COO_Format COOT, int isInt, int n, int m) {
  double t = omp_get_wtime()-COOT.time;
  CSC_Format parsed_matrix;

  int size = COOT.lenvalues;
  int index;

  int i;
  int j;
  int *NNZ,*temp,*IA,*JA;
  float *floatNNZ;
  /* NNZ: The non-zero values stored in row-major order */
  NNZ = malloc(size*sizeof(int));
  /* NNZ: The non-zero values stored in row-major order */
  floatNNZ = malloc(size*sizeof(float));
  /*BUILD IA = [0, 1, 3, 3] the number of elements in each row */
  IA = malloc((n+1)*sizeof(int));
  /*BUILD JA: Stores the column index of each non-zero element. */
  JA = malloc(size*sizeof(int));

  int IA_index = 0;
  IA[IA_index] = 0;
  IA_index++;
  int row_prev,row_new,jump;
  row_prev = 0;

  for (index=0;index<size;index++) {

    if (isInt == 1){
      NNZ[index] = ((int*)COOT.values)[index];
    } else{
      floatNNZ[index] = ((float*)COOT.values)[index];
    }

    JA[index] = COOT.column_indices[index];

    //BUILD IA ARRAY
    row_new = COOT.row_indices[index];
    if (row_new == row_prev) {
      continue;
    } else {
      jump = row_new-row_prev;
      IA[IA_index]=index;
      IA_index++;
      for (i=0;i<jump-1;i++) {
        IA[IA_index] = index;
        IA_index++;
      }
      row_prev = row_new;
    }
  }
  IA[n] = size;

  parsed_matrix.lenNNZ = size;
  parsed_matrix.IA = IA;
  parsed_matrix.JA = JA;
  if (isInt==1){
    parsed_matrix.NNZ = NNZ;
  } else {
    parsed_matrix.NNZ = floatNNZ;
  }

  //print_int_array(parsed_matrix.IA, n+1, "IA");
  //print_int_array(parsed_matrix.JA, size, "JA");
  //print_int_array(parsed_matrix.NNZ, size, "NNZ");

  double time_taken = omp_get_wtime() - t;
  parsed_matrix.time = time_taken;
  printf("Time: %f\n",parsed_matrix.time);
  return parsed_matrix;
}
