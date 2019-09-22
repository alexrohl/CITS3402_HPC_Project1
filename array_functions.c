#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_int_array(int * arr, int len, char name[64]) {
    printf("Array %s: [",name);

    int i;
    for (i=0; i<len; i++) {
      printf("%d,", arr[i]);
    }
    printf("] has length %d\n",len);
    return;
}

void print_float_array(float * arr, int len, char name[64]) {
    printf("Array %s: [",name);

    int i;
    for (i=0; i<len; i++) {
      printf("%f,", arr[i]);
    }
    printf("] has length %d\n",len);
    return;
}

//we define the following function to modularise the array building processes...
int * append_int_to_array(int *temp, int *arr1, int val1, int index){
  /*append to values*/
  arr1[index]=val1;
  temp=realloc(arr1,(index+2)*sizeof(int));
  /*using temp*/
  if ( temp != NULL ) {
    arr1=temp;
  } else {
    free(arr1);
    printf("Error allocating memory!\n");
  }
  return arr1;
}

//we define the following function to modularise the array building processes...
float * append_float_to_array(float *temp, float *arr1, float val1, int index){
  /*append to values*/
  arr1[index]=val1;
  temp=realloc(arr1,(index+2)*sizeof(float));
  /*using temp*/
  if ( temp != NULL ) {
    arr1=temp;
  } else {
    free(arr1);
    printf("Error allocating memory!\n");
  }
  //printf("adding %f\n",val1);
  //print_float_array(arr1, index+1, "sub");
  //print_float_array(temp, index+1, "sub");
  return arr1;
}

void int_swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void float_swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void append_to_arrays(int *temp, int *arr1, int *arr2, int*arr3, int val1, int val2, int val3, int index){
  append_int_to_array(temp,arr1, val1, index);
  append_int_to_array(temp,arr1, val1, index);
  append_int_to_array(temp,arr1, val1, index);
}
