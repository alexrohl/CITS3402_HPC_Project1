#include<stdio.h>
#include<time.h>
#include<omp.h>

FILE *ifp, *ofp;
char *mode = "r";
char outputFilename[] = "name.out";

FILE ifp = fopen("int1.in", mode);

if (ifp == NULL) {
  fprintf(stderr, "Can't open input file in.list!\n");
  exit(1);
}

ofp = fopen(outputFilename, "w");

if (ofp == NULL) {
  fprintf(stderr, "Can't open output file %s!\n",
          outputFilename);
  exit(1);
}

/*   ./mysolution.exe -sc -f matrix1.in   */

int main(int argc,char* argv[])
{
    int counter;
    printf("Program Name Is: %s",argv[0]);
    if(argc==1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if(argc>=2)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\n----Following Are The Command Line Arguments Passed----");
        for(counter=0; counter<argc ; counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
    }
    return 0;
}
