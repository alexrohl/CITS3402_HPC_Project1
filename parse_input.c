// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*return an array of the correct size and type*/
/*• Datatype: ”int” or ”float”
• Number of rows: An integer n > 0
• Number of columns: An integer m > 0
• n × m space-separated integers/floats representing each value*/

/*READ DIRECTLY INTO SPARSE MATRIX FORMAT*/
/*The compressed sparse row format stores a matrix with three arrays:
• NNZ: The non-zero values stored in row-major order (left to right, top to
bottom)
• IA: The number of elements in each row. An extra element IA[0] = 0 is
used by convention. This array can be used to index into the NNZ array
for each i-th row
2
• JA: Stores the column index of each non-zero element.
For example, the matrix,
0 0 1
3 0 2
0 0 0
becomes
NNZ = [1, 3, 2]
IA = [0, 1, 3, 3]
JA = [2, 0, 2]
*/


#define MAX_LINE_LEN 256
#define FALSE 0
#define TRUE !(FALSE)
void get_array(char *filename)
{
    int n; /*Number of rows: An integer n > 0*/
    int m; /*Number of columns: An integer m > 0*/
    int is_int;

    FILE *fp = fopen(filename, "r"); /* should check the result */
    char type[MAX_LINE_LEN];

    float f_elem;
    int i_elem;

    /*read in type of matrix*/
    fscanf(fp, "%s", type);

    if (strncmp(type, "int", 3) == 0) {
      is_int = TRUE;
    } else {
      is_int = FALSE;
    }

    /*read in n and m*/
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);

    int i;
    int j;

    /*
    if ( temp != NULL ) {
      NNZ=temp;
    } else {
      free(NNZ);
      printf("Error allocating memory!\n");
    }
    */

    if (is_int) {
      int *NNZ,*temp,*IA,*JA;

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

      for (i=0; i<n; i++) {
        IA_index++;
        for (j=0; j<m; j++) {
          /* i is our row index*/
          /* j is our column index*/

          /*read element*/
          fscanf(fp,"%d", &i_elem);
          printf("%d \n", i_elem);

          if (i_elem != 0) {
            elements_in_row_counter++;

            /*append to NNZ*/
            NNZ[non_zero_counter]=i_elem;
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
            JA[non_zero_counter]=j;
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
          }
        }
        /*append to IA*/
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
      printf("non zero %d\n",non_zero_counter);
      printf("IA: [");
      for (i=0; i<=n; i++) {
        printf("%d,", IA[i]);
        j = IA[i];
      }
      printf("]\n");

      printf("JA: [");
      for (i=0; i<j; i++) {
        printf("%d,", JA[i]);
      }
      printf("]\n");

      printf("NNZ: [");
      for (i=0; i<j; i++) {
        printf("%d,", NNZ[i]);
      }
      printf("]\n");
        /* Free the pointers */
      free(NNZ);
        /* Return success */

    }

}

int main() {
  char file_name[MAX_LINE_LEN] = "int3.in";
  get_array(file_name);
}
