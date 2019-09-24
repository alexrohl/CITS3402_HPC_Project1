#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*RECALL • NNZ: The non-zero values stored in row-major order (left to right, top to
bottom)
• IA: The number of elements in each row. An extra element IA[0] = 0 is
used by convention. This array can be used to index into the NNZ array
for each i-th row
• JA: Stores the column index of each non-zero element.

NNZ = [ 10 20 30 40 50 60 70 80 ]
   IA = [  0  2  4  7  8 ]
   JA = [  0  1  1  3  2  3  4  5 ]
The whole is stored as 21 entries.



IA splits the array NNZ into rows: (10, 20) (30, 40) (50, 60, 70) (80);
JA aligns values in columns: (10, 20, ...) (0, 30, 0, 40, ...)(0, 0, 50, 60, 70, 0) (0, 0, 0, 0, 0, 80).*/

FILE* CSR_Print(FILE* fp, CSR_Format CSR_Matrix, int n, int m, int isInt) {
  print_int_array(CSR_Matrix.IA, n+1, "IA");
  print_int_array(CSR_Matrix.JA, CSR_Matrix.lenNNZ, "JA");
  print_float_array(CSR_Matrix.NNZ, CSR_Matrix.lenNNZ, "NNZ");
  int i,j;
  printf("HERE");
  for (i=0;i<n;i++) {
    int first1 = CSR_Matrix.IA[i];
    int last1 = CSR_Matrix.IA[i+1];
    int j1 = first1;
    for (j=0;j<m;j++) {
      int column_index1 = CSR_Matrix.JA[j1];
      int final_index1 = CSR_Matrix.JA[last1];

      if ((j==column_index1) && (j1!=last1)) {
        if (isInt==1) {
          fprintf(fp,"%d ",((int*)CSR_Matrix.NNZ)[j1]);
          j1++;
        } else {
          fprintf(fp,"%f ",((float*)CSR_Matrix.NNZ)[j1]);
          j1++;
        }

      } else {
        if (isInt==1) {
          fprintf(fp,"0 ");
        } else {
          fprintf(fp,"0. ");
        }
      }
      printf("J1:%d\n",j1);
    }
  }
  fprintf(fp,"\n");
  return fp;
}

FILE* COO_Print(FILE* fp, COO_Format COO_Matrix, int n, int m, int isInt) {
  //print_int_array(CSR_Matrix.IA, n+1, "IA");
  //print_int_array(CSR_Matrix.JA, CSR_Matrix.lenNNZ, "JA");
  //print_float_array(CSR_Matrix.NNZ, CSR_Matrix.lenNNZ, "NNZ");
  int i,j,i1,j1;
  printf("HERE");
  int index=0;
  for (i=0;i<n;i++) {
    for (j=0;j<m;j++) {
      i1 = COO_Matrix.row_indices[index];
      j1 = COO_Matrix.column_indices[index];
      if ((j==j1) && (i==i1)) {
        if (isInt==1) {
          fprintf(fp,"%d ",((int*)COO_Matrix.values)[index]);
          index++;
        } else {
          fprintf(fp,"%f ",((float*)COO_Matrix.values)[index]);
          index++;
        }

      } else {
        if (isInt==1) {
          fprintf(fp,"0 ");
        } else {
          fprintf(fp,"0. ");
        }
      }
      printf("J1:%d\n",j1);
    }
  }
  fprintf(fp,"\n");
  return fp;
}
