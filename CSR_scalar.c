// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Note we will always be returning a float result*/
CSR_Format get_CSR_scalar(MatrixContainer Matrix, float scalar, int num_threads)
{
  clock_t t;
  t = clock();

  CSR_Format CSR_Matrix = Matrix.CSR_Matrix;
  CSR_Format Result;

  int i;
  int j;

  /* values: The non-zero values stored in row-major order */
  float float_NNZ[CSR_Matrix.lenNNZ];
  /*BUILD IA = [0, 1, 3, 3] the number of elements in each row */
  int IA[Matrix.n_rows];
  /*BUILD JA: Stores the column index of each non-zero element. */
  int JA[CSR_Matrix.lenNNZ];

  //rebuild IA_index
  omp_set_num_threads(num_threads); //I have set the number of threads =4, you can change this.
  #pragma omp parallel
  {
    for (i=0;i<Matrix.n_rows;i++) {
      IA[i] = CSR_Matrix.IA[i];
    }
  }
  if (Matrix.isInt) {
    int * old_values = (int*)CSR_Matrix.NNZ;
    #pragma omp parallel
    {
      #pragma omp for
      for (i=0;i<CSR_Matrix.lenNNZ;i++) {
        JA[i] = CSR_Matrix.IA[i];
        float new_val = old_values[i]*scalar;
        float_NNZ[i] = new_val;
      }
    }

  } else {
    //Float array...
    float * old_values = (float*)CSR_Matrix.NNZ;
    #pragma omp parallel
    {
      #pragma omp for
      for (i=0;i<CSR_Matrix.lenNNZ;i++) {
        JA[i] = CSR_Matrix.IA[i];
        float new_val = old_values[i]*scalar;
        float_NNZ[i] = new_val;
      }
    }
  }
  Result.lenNNZ = CSR_Matrix.lenNNZ;
  Result.IA = IA;
  Result.JA = JA;
  Result.NNZ = float_NNZ;
  //print_int_array(Result.IA, Matrix.n_rows, "IA");
  //print_int_array(Result.JA, Result.lenNNZ, "JA");
  //print_float_array(Result.NNZ, Result.lenNNZ, "NNZ");


  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  Result.time = time_taken;
  printf("Time: %f\n",Result.time);

  return Result;

}
