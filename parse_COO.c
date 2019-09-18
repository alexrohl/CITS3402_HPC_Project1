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
/*The most intuitive sparse matrix format specifies each non-zero element as a triple
        Ai,j = (i, j, val)
*/


#define MAX_LINE_LEN 256

/*Returns ptr values, its length, ptr row_indices, its length, ptr column_indices, its length*/
/*note the void definition of values since we don't know if it contains ints or floats*/
struct COO_Matrix {
    int num_rows;
    int num_columns;
    int lenvalues;
    void *values;
    int *column_indices;
    int *row_indices;
};

typedef struct COO_Matrix COO_Format;



COO_Format get_COO_Matrix(char *filename)
{
    COO_Format parsed_matrix;

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
      is_int = true;
    } else {
      is_int = false;
    }

    /*read in n and m*/
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);
    parsed_matrix.num_rows = n;
    parsed_matrix.num_columns = m;

    int i;
    int j;

    if (is_int) {
      int *values,*temp,*row_indices,*column_indices;

      /* values: The non-zero values stored in row-major order */
      values = malloc(sizeof(int));
      /*BUILD row_indices = [0, 1, 3, 3] the number of elements in each row */
      row_indices = malloc(sizeof(int));
      /*BUILD column_indices: Stores the column index of each non-zero element. */
      column_indices = malloc(sizeof(int));

      int non_zero_counter = 0;

      for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
          /* i is our row index*/
          /* j is our column index*/

          /*read element*/
          fscanf(fp,"%d", &i_elem);
          printf("%d \n", i_elem);

          if (i_elem != 0) {
            /*append to values*/
            values[non_zero_counter]=i_elem;
            temp=realloc(values,(non_zero_counter+2)*sizeof(int));
            /*using temp*/
            if ( temp != NULL ) {
              values=temp;
            } else {
              free(values);
              printf("Error allocating memory!\n");
            }
            /*using temp*/

            /*append to column_indices*/
            column_indices[non_zero_counter]=j;
            temp=realloc(column_indices,(non_zero_counter+2)*sizeof(int));
            /*using temp*/
            if ( temp != NULL ) {
              column_indices=temp;
            } else {
              free(column_indices);
              printf("Error allocating memory!\n");
            }
            /*using temp*/

            /*append to row_indices*/
            row_indices[non_zero_counter]=i;
            temp=realloc(row_indices,(non_zero_counter+2)*sizeof(int));
            /*using temp*/
            if ( temp != NULL ) {
              row_indices=temp;
            } else {
              free(row_indices);
              printf("Error allocating memory!\n");
            }
            /*using temp*/

            non_zero_counter++;
          }
        }


      }
      parsed_matrix.lenvalues = non_zero_counter;
      parsed_matrix.values = values;
      parsed_matrix.row_indices = row_indices;
      parsed_matrix.column_indices = column_indices;


      printf("non zero %d\n",non_zero_counter);
      printf("row_indices: [");
      for (i=0; i<non_zero_counter; i++) {
        printf("%d,", row_indices[i]);
      }
      printf("]\n");

      printf("column_indices: [");
      for (i=0; i<non_zero_counter; i++) {
        printf("%d,", column_indices[i]);
      }
      printf("]\n");

      printf("values: [");
      for (i=0; i<non_zero_counter; i++) {
        printf("%d,", values[i]);
      }
      printf("]\n");

      /* Free the pointers */
      /* free(values);
      free(column_indices);
      free(row_indices);
      */
      return parsed_matrix;

    }
}
