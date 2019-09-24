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

/*Returns ptr NNZ, its length, ptr IA, its length, ptr JA, its length*/
/*note the void definition of NNZ since we don't know if it contains ints or floats*/
struct CSR_Matrix {
    int lenNNZ;
    void *NNZ;
    int *IA;
    int *JA;
    double time;
};

typedef struct CSR_Matrix CSR_Format;

struct CSC_Matrix {
    int lenNNZ;
    void *NNZ;
    int *IA;
    int *JA;
    double time;
};

typedef struct CSC_Matrix CSC_Format;

struct MatrixContainer {
    char name[50];
    int isInt;
    int n_rows;
    int m_columns;
    COO_Format COO_Matrix;
    CSR_Format CSR_Matrix;
    CSC_Format CSC_Matrix;
};

typedef struct MatrixContainer MatrixContainer;


CSR_Format get_CSR_Matrix(char *filename, int isInt, int n, int m)
{
    CSR_Format parsed_matrix;
    double t;
    t = omp_get_wtime();

    FILE *fp = fopen(filename, "r"); /* should check the result */
    char type[MAX_LINE_LEN];

    float f_elem;
    int i_elem;

    /*skip first 3 reads...*/
    fscanf(fp, "%s", type);
    fscanf(fp, "%d", &i_elem);
    fscanf(fp, "%d", &i_elem);
    /*read in n and m*/

    int i;
    int j;
    int *NNZ,*temp,*IA,*JA;

    /* NNZ: The non-zero values stored in row-major order */
    NNZ = malloc(sizeof(int));
    /*BUILD IA = [0, 1, 3, 3] the number of elements in each row */
    IA = malloc(sizeof(int));
    /*BUILD JA: Stores the column index of each non-zero element. */
    JA = malloc(sizeof(int));

    float *float_NNZ;
    float *float_temp;
    /* values: The non-zero values stored in row-major order */
    float_NNZ = malloc(sizeof(float));

    int non_zero_counter = 0;
    int elements_in_row_counter = 0;
    int IA_index = 0;

    /*initialise IA*/
    IA = append_int_to_array(temp, IA, elements_in_row_counter, IA_index);
    IA_index++;

    if (isInt) {
      for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
          /* i is our row index*/
          /* j is our column index*/

          /*read element*/
          fscanf(fp,"%d", &i_elem);

          if (i_elem != 0) {
            elements_in_row_counter++;

            NNZ = append_int_to_array(temp, NNZ, i_elem, non_zero_counter);
            JA = append_int_to_array(temp, JA, j, non_zero_counter);
            non_zero_counter++;
          }
        }
        /*append to IA*/
        IA = append_int_to_array(temp, IA, elements_in_row_counter, IA_index);
        IA_index++;

      }
      parsed_matrix.NNZ = NNZ;
      //print_int_array(parsed_matrix.NNZ , non_zero_counter, "NNZ");
    } else {
      //READING FLOATS
      for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
          /* i is our row index*/
          /* j is our column index*/

          /*read element*/
          fscanf(fp,"%f", &f_elem);

          if (f_elem != 0.0) {
            elements_in_row_counter++;

            float_NNZ = append_float_to_array(float_temp, float_NNZ, f_elem, non_zero_counter);
            JA = append_int_to_array(temp, JA, j, non_zero_counter);
            non_zero_counter++;
          }
        }
        /*append to IA*/
        IA = append_int_to_array(temp, IA, elements_in_row_counter, IA_index);
        IA_index++;

      }
      parsed_matrix.NNZ = float_NNZ;
      //print_float_array(parsed_matrix.NNZ , non_zero_counter, "NNZ");

    }
    parsed_matrix.lenNNZ = non_zero_counter;
    parsed_matrix.IA = IA;
    parsed_matrix.JA = JA;
    //print_int_array(parsed_matrix.IA, n+1, "IA");
    //print_int_array(parsed_matrix.JA, non_zero_counter, "JA");

    double time_taken = omp_get_wtime() - t;
    parsed_matrix.time = time_taken;
    printf("Time: %f\n",parsed_matrix.time);
    return parsed_matrix;
}
