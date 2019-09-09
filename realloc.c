#include <stdio.h>
#include <stdlib.h>

/* This program takes input and outputs everything backwards */

int main() {
  int *data,*temp;
  data=malloc(sizeof(int));
  int c; /* c is the current character */
  int i; /* i is the counter */
  for (i=0;;i++) {
    c=getchar(); /* put input character into c */
    if (c==EOF) /* break from the loop on end of file */
      break;
    data[i]=c; /* put the character into the data array */
    temp=realloc(data,(i+2)*sizeof(int)); /* give the pointer some memory */
    if ( temp != NULL ) {
      data=temp;
    } else {
      free(data);
      printf("Error allocating memory!\n");
      return 1;
    }
  }
/* Output data backwards one character at a time */
for (i--;i>=0;i--)
putchar(data[i]);
/* Free the pointer */
free(data);
/* Return success */
return 0;
}
