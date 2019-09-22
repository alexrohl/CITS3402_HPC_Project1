// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*return an array of the correct size and type*/
/*The compressed sparse column format is very similar to CSR format except
the non-zero values are stored in a column-wise ordering, the IA array corresponds to the extent of each column and the JA array provides row indices. For
example, the matrix,
X =
0 0 1
3 0 2
0 0 0
becomes
NNZ = [3, 1, 2]
IA = [0, 1, 1, 3]
JA = [1, 0, 1]
*/
#define MAX_LINE_LEN 256
/*note the void definition of NNZ since we don't know if it contains ints or floats*/
struct CSC_Matrix {
    int lenNNZ;
    void *NNZ;
    int *IA;
    int *JA;
    double time;
};

typedef struct CSC_Matrix CSC_Format;
