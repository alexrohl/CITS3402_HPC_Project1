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

/*READ DIRECTLY INTO SPARE MATRIX FORMAT*/

#define MAX_LINE_LEN 256
#define FALSE 0
#define TRUE !(FALSE)
void get_array(char *filename)
{
    printf("here");
    int n;
    int m;
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
    printf("bool %d",is_int);
    if (is_int) {
        printf(" here");
      for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
          fscanf(fp,"%d", &i_elem);
          printf("%d \n", i_elem);
        }
      }
    }
}

int main() {
  char file_name[MAX_LINE_LEN] = "int2.in";
  get_array(file_name);
}
