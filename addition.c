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
CSRformat get_addition(CSRformat Matrix1, CSRformat Matrix2)
{
  if (Matrix1.num_rows != Matrix2.num_rows || Matrix1.num_columns != Matrix2.num_columns) {
    printf("Matrix Dimensions do not Match!\n");
    CSRformat null;
    return null;
  }
  int *NNZ,*temp,*IA,*JA;
  CSRformat Result;
  /* NNZ: The non-zero values stored in row-major order */
  NNZ = malloc(sizeof(int));
  /*BUILD IA = [0, 1, 3, 3] the number of elements in each row */
  IA = malloc(sizeof(int));
  /*BUILD JA: Stores the column index of each non-zero element. */
  JA = malloc(sizeof(int));

  int non_zero_counter = 0;
  int elements_in_row_counter = 0;
  int IA_index = 0;

  /*initialise IA*/
  IA[IA_index] = elements_in_row_counter;
  temp=realloc(IA,(IA_index+2)*sizeof(int));

  /*using temp*/
  if ( temp != NULL ) {
    IA=temp;
  } else {
    free(IA);
    printf("Error allocating memory!\n");
  }
  /*using temp*/

  int * intNNZ1 = (int*)Matrix1.NNZ;
  int * intNNZ2 = (int*)Matrix2.NNZ;
  //Build resulting matrix
  int element_to_add,index_to_add;
  //loops through each row in M1 and M2
  int i;
  for(i=0; i<Matrix1.num_rows; i++) {
    IA_index++;
    printf("row: %d\n",i);

    int first1 = Matrix1.IA[i];
    int last1 = Matrix1.IA[i+1];
    int first2 = Matrix2.IA[i];
    int last2 = Matrix2.IA[i+1];

    int j1 = first1;
    int j2 = first2;

    while (true) {
      int column_index1 = Matrix1.JA[j1];
      int column_index2 = Matrix2.JA[j2];
      //If matrix1 is spent, add matrix2 remaining elements to Result
      if (j1 == last1) {
        for(j2=j2;j2<last2;j2++) {
          printf("here j2:%d last: %d\n",j2,last2);
          element_to_add = intNNZ2[j2];
          index_to_add = Matrix2.JA[j2];
          //append  element and its index to result
          /*append to NNZ*/
          NNZ[non_zero_counter]=element_to_add;
          temp=realloc(NNZ,(non_zero_counter+2)*sizeof(int));
          /*using temp*/
          if ( temp != NULL ) {
            NNZ=temp;
          } else {
            free(NNZ);
            printf("Error allocating memory!\n");
          }
          /*using temp*/

          /*append to JA*/
          JA[non_zero_counter]=index_to_add;
          temp=realloc(JA,(non_zero_counter+2)*sizeof(int));
          /*using temp*/
          if ( temp != NULL ) {
            JA=temp;
          } else {
            free(JA);
            printf("Error allocating memory!\n");
          }
          /*using temp*/

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
          index_to_add = Matrix1.JA[j1];
          //append  element and its index to result
          /*append to NNZ*/
          NNZ[non_zero_counter]=element_to_add;
          temp=realloc(NNZ,(non_zero_counter+2)*sizeof(int));
          /*using temp*/
          if ( temp != NULL ) {
            NNZ=temp;
          } else {
            free(NNZ);
            printf("Error allocating memory!\n");
          }
          /*using temp*/

          /*append to JA*/
          JA[non_zero_counter]=index_to_add;
          temp=realloc(JA,(non_zero_counter+2)*sizeof(int));
          /*using temp*/
          if ( temp != NULL ) {
            JA=temp;
          } else {
            free(JA);
            printf("Error allocating memory!\n");
          }
          /*using temp*/

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

        //append  element and its index to result
        /*append to NNZ*/
        NNZ[non_zero_counter]=element_to_add;
        temp=realloc(NNZ,(non_zero_counter+2)*sizeof(int));
        /*using temp*/
        if ( temp != NULL ) {
          NNZ=temp;
        } else {
          free(NNZ);
          printf("Error allocating memory!\n");
        }
        /*using temp*/

        /*append to JA*/
        JA[non_zero_counter]=index_to_add;
        temp=realloc(JA,(non_zero_counter+2)*sizeof(int));
        /*using temp*/
        if ( temp != NULL ) {
          JA=temp;
        } else {
          free(JA);
          printf("Error allocating memory!\n");
        }
        /*using temp*/

        non_zero_counter++;
        elements_in_row_counter++;

      }
    }
    //append number_of_elements in row to result
    IA[IA_index]=elements_in_row_counter;
    temp=realloc(IA,(IA_index+2)*sizeof(int));
    /*using temp*/
    if ( temp != NULL ) {
      IA=temp;
    } else {
      free(IA);
      printf("Error allocating memory!\n");
    }
    /*using temp*/
  }
  //format result
  Result.num_rows = Matrix1.num_rows;
  Result.num_columns = Matrix1.num_columns;
  Result.lenNNZ = non_zero_counter;
  Result.NNZ = NNZ;
  Result.IA = IA;
  Result.JA = JA;

  printf("ADDING\n");
  printf("non zero %d\n",non_zero_counter);
  printf("IA: [");
  for (i=0; i<=Matrix1.num_rows; i++) {
    printf("%d,", IA[i]);
  }
  printf("]\n");

  printf("JA: [");
  for (i=0; i<non_zero_counter; i++) {
    printf("%d,", JA[i]);
  }
  printf("]\n");

  printf("NNZ: [");
  for (i=0; i<non_zero_counter; i++) {
    printf("%d,", NNZ[i]);
  }
  printf("]\n");

  /* Free the pointers */
  /* free(NNZ);
  free(JA);
  free(IA);
  */
  return Result;
}
