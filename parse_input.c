// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    char const* const fileName = argv[1]; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[256];

    int line_counter = 0
    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */

        /* Parse type */
        if (line_counter == 0) {
          str type = line;
        }
        /* Parse num rows and columns */
        elif (line_counter == 1) {
          int num_rows = line;
        }
        elif (line_counter == 2) {
          int num_cols = line;
        }
        /*Make Matrix...*/
        else {
          if (type=="int") {
            int matrix[num_rows][num_cols] = line;
          } else {
            float matrix[num_rows][num_cols] = line;
          }
        }
        /*Parse num_rows and num_columns*/

        printf("%s", line);
    }

    fclose(file);

    return 0;
}
