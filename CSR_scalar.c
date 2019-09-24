// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Note we will always be returning a float result*/
CSR_Format get_CSR_scalar(MatrixContainer Matrix, float scalar, int num_threads)
{
  double t;
  t = omp_get_wtime();
  printf("Multiplying by %f\n",scalar);

  CSR_Format CSR_Matrix = Matrix.CSR_Matrix;
  CSR_Format Result;

  int i;
  int j;

  int *IA,*JA;
  float *float_NNZ;

  /* NNZ: The non-zero values stored in row-major order */
  float_NNZ = malloc(CSR_Matrix.lenNNZ*sizeof(float));
  /*BUILD IA = [0, 1, 3, 3] the number of elements in each row */
  IA = malloc((Matrix.n_rows+1)*sizeof(int));
  /*BUILD JA: Stores the column index of each non-zero element. */
  JA = malloc(CSR_Matrix.lenNNZ*sizeof(int));
  //rebuild IA_index
  omp_set_num_threads(num_threads); //I have set the number of threads =4, you can change this.
  #pragma omp parallel
  {
    for (i=0;i<Matrix.n_rows+1;i++) {
      IA[i] = CSR_Matrix.IA[i];
    }
  }
  if (Matrix.isInt) {
    int * old_values = (int*)CSR_Matrix.NNZ;
    #pragma omp parallel
    {
      #pragma omp for
      for (i=0;i<CSR_Matrix.lenNNZ;i++) {
        JA[i] = CSR_Matrix.JA[i];
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
        JA[i] = CSR_Matrix.JA[i];
        float new_val = old_values[i]*scalar;
        float_NNZ[i] = new_val;
      }
    }
  }
  Result.lenNNZ = CSR_Matrix.lenNNZ;
  Result.IA = IA;
  Result.JA = JA;
  Result.NNZ = float_NNZ;
  print_int_array(Result.IA, Matrix.n_rows+1, "IA");
  print_int_array(Result.JA, Result.lenNNZ, "JA");
  print_float_array(Result.NNZ, Result.lenNNZ, "NNZ");


  double time_taken = omp_get_wtime() - t;
  Result.time = time_taken;
  printf("Time: %f\n",Result.time);

  return Result;
}
