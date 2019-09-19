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
struct CSC_Matrix {
    int lenNNZ;
    void *NNZ;
    int *IA;
    int *JA;
};

typedef struct CSC_Matrix CSC_Format;
