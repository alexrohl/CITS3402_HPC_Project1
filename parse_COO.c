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
    int lenvalues;
    void * values;
    int * column_indices;
    int * row_indices;
};

typedef struct COO_Matrix COO_Format;



COO_Format get_COO_Matrix(char *filename, int isInt, int n, int m)
{
    COO_Format parsed_matrix;

    FILE *fp = fopen(filename, "r"); /* should check the result */
    char type[MAX_LINE_LEN];

    /*read in type of matrix*/
    fscanf(fp, "%s", type);
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);
    /*read in n and m*/
    int *temp,*row_indices,*column_indices;

    /*BUILD row_indices = [0, 1, 3, 3] the number of elements in each row */
    row_indices = malloc(sizeof(int));
    /*BUILD column_indices: Stores the column index of each non-zero element. */
    column_indices = malloc(sizeof(int));

    int *values;
    /* values: The non-zero values stored in row-major order */
    values = malloc(sizeof(int));

    float *float_values;
    float *float_temp;
    /* values: The non-zero values stored in row-major order */
    float_values = malloc(sizeof(float));

    int non_zero_counter = 0;

    int i;
    int j;

    //FOR INTEGERS

    if (isInt) {
      printf("Building integer COO matrix\n");
      int i_elem;

      for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
          /*read element*/
          fscanf(fp,"%d", &i_elem);
          printf("%d \n", i_elem);

          if (i_elem != 0) {
            /*append to values*/
            values = append_int_to_array(temp, values, i_elem, non_zero_counter);
            row_indices = append_int_to_array(temp, row_indices, i, non_zero_counter);
            column_indices = append_int_to_array(temp, column_indices, j, non_zero_counter);
            non_zero_counter++;
          }
        }
      }
      parsed_matrix.values = values;
      print_int_array(parsed_matrix.values, non_zero_counter, "values");
    } else {
      //FOR FLOATS
      printf("Building float COO matrix\n");
      float f_elem;

      for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
          /* i is our row index*/
          /* j is our column index*/

          /*read element*/
          fscanf(fp,"%f", &f_elem);
          printf("%f \n", f_elem);

          if (f_elem != 0) {
            /*append to values*/
            float_values = append_float_to_array(float_temp, float_values, f_elem, non_zero_counter);
            row_indices = append_int_to_array(temp, row_indices, i, non_zero_counter);
            column_indices = append_int_to_array(temp, column_indices, j, non_zero_counter);
            non_zero_counter++;

          }
        }
      }
      parsed_matrix.values = float_values;
      print_float_array(parsed_matrix.values, non_zero_counter, "values");
    }

    parsed_matrix.lenvalues = non_zero_counter;
    parsed_matrix.row_indices = row_indices;
    parsed_matrix.column_indices = column_indices;
    
    print_int_array(parsed_matrix.column_indices , non_zero_counter, "column");
    print_int_array(parsed_matrix.row_indices, non_zero_counter, "rows");

    /* Free the pointers */
    /* free(values);
    free(column_indices);
    free(row_indices);
    */
    return parsed_matrix;

}
