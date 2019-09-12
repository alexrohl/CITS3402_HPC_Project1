#include<stdio.h>
#include<time.h>
#include<omp.h>
#include"parse_input.c"
/*Your code will be a simple command-line application that will:
• Read in up to two dense matrix files
• Convert this matrix (these matrices) to a suitable sparse format.
• Perform a single matrix algebra routine specified by command-line
• Time the whole process and log the results to a file
• Cleanup all memory usage and terminate*/

/*   ./mysolution.exe -sc -f matrix1.in   */

/*FUN WITH FLAGS*/
/*Several operators, determines what matrix operation will be performed
(have been discussed previously)
– --sm - Scalar multiplication
– --tr - Trace
– --ad - Addition
– --ts - Transpose
– --mm - Matrix multiplication
• -f %s (%s) depending on the operation requested, one or more matrix
files will need to be passed
– Example: ./mysolution.exe --sm -f matrix1.in
– Example: ./mysolution.exe --mm -f matrix1.in matrix2.in
• -t %d Threads. If present specifies the number of execution threads to
use.
• -l Log. If present, results will be logged to file*/

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
    printf("\n");

    struct parsedMatrix Matrix1 = get_array(argv[1]);
    return 0;
}
