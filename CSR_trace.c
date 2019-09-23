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
  clock_t t;
  t = clock();
  CSR_Format CSR_Matrix = Matrix.CSR_Matrix;
  int sum = 0;
  int lsum = 0;
  int i,j;
  int * intNNZ = (int*)CSR_Matrix.NNZ;

  omp_set_num_threads(num_threads); //I have set the number of threads =4, you can change this.
  #pragma omp parallel private(lsum)
  {
    #pragma omp for
    //loops through each row
    for(i=0; i<Matrix.n_rows; i++) {
      //printf("row: %d\n",i);
      int first = CSR_Matrix.IA[i];
      int last = CSR_Matrix.IA[i+1];
      int column_index;
      //loops through column_indexs
      for (j=first;j<last;j++) {
        /*Look through column indexes*/
        column_index = CSR_Matrix.JA[j];
        //printf("columnIndex: %d\n",column_index);
        if (column_index>i) {
          break;
        }

        if (column_index == i) {//found entry on diagonal
          int diagonal_entry = intNNZ[j];
          //printf("Diagonal: %d\n",diagonal_entry);
          lsum += diagonal_entry;
        }
      }
    }
    #pragma omp critical
        {
        sum+=lsum;
        }
  }
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("Time: %f\n",time_taken);
  printf("Sum: %d\n",sum);
  return sum;
}
/*
    //BUILD ROW
    ith_row = malloc(sizeof(int)); //Where i is the place you want to start your subset.
    column_indexs = malloc(sizeof(int));

    ith_row[counter] = Matrix.NNZ[j];
    temp=realloc(ith_row,(counter+2)*sizeof(int));
    //using temp
    if ( temp != NULL ) {
      ith_row=temp;
    } else {
      free(ith_row);
      printf("Error allocating memory!\n");
    }

    //BUILD Column Indexes
    column_indexs[counter] = Matrix.JA[j];
    temp=realloc(column_indexs,(counter+2)*sizeof(int));
    //using temp
    if ( temp != NULL ) {
      column_indexs=temp;
    } else {
      free(column_indexs);
      printf("Error allocating memory!\n");
    }

    counter++
    //initialise IA
    IA[IA_index] = elements_in_row_counter;
    temp=realloc(IA,(IA_index+2)*sizeof(int));

    //using temp
    if ( temp != NULL ) {
      IA=temp;
    } else {
      free(IA);
      printf("Error allocating memory!\n");
    }
  }
}
*/
