const int true = 1;
const int false = 0;
#include <time.h>
#include<stdio.h>
#include<time.h>
#include<omp.h>
#include <stdlib.h>
#include"array_functions.c"

#include"parse_COO.c"
#include"parse_CSR.c"
#include"parse_CSC2.c"

#include"build_matrix_container.c"

#include"CSR_scalar.c"
#include"CSR_trace.c"
#include"COO_transpose.c"
#include"CSR_addition.c"
#include"COO_addition.c"
#include"CSR_CSC_multiply.c"

#include"FILE_PRINTER.c"
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
float scalar;
int main(int argc,char* argv[])
{
    int num_threads = 1;
    int counter;
    int logging = 0;
    int num_files = 1;
    char operation[2];
    MatrixContainer matrix_container1;
    MatrixContainer matrix_container2;
    printf("Program Name Is: %s", argv[0]);
    if(argc==1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if(argc>=2)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\n----Following Are The Command Line Arguments Passed----\n");
        for(counter=0; counter<argc ; counter++) {
            printf("argv[%d]: %s\n",counter,argv[counter]);
            if (strcmp(argv[counter],"-t")==0) {
              num_threads = atoi(argv[counter + 1]);
            }
            else if (strcmp(argv[counter],"-l")==0) {
              logging = 1;
            }
            else if (strcmp(argv[counter],"--sm")==0) {
              strncpy(operation,"sm",2);
              scalar = atof(argv[counter+1]);
              printf("Read scalar0: %f\n", scalar);
            }
            else if (strcmp(argv[counter],"--tr")==0) {
              strncpy(operation,"tr",2);
              printf("Reading trace!!\n");
            }
            else if (strcmp(argv[counter],"--ts")==0) {
              strncpy(operation,"ts",2);
            }
            else if (strcmp(argv[counter],"--ad")==0) {
              strncpy(operation,"ad",2);
              num_files = 2;

            }
            else if (strcmp(argv[counter],"--mm")==0) {
              strncpy(operation,"mm",2);
              num_files = 2;

            }
            else if (strcmp(argv[counter],"-f")==0) {
              if (num_files==1) {
                matrix_container1 = get_type(argv[counter + 1]);
              } else {
                matrix_container1 = get_type(argv[counter + 1]);
                matrix_container2 = get_type(argv[counter + 2]);
              }
            }
        }
      //Create File Name
      int studentNum = 22233158;
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      char output[50];
      sprintf(output,"%d_%d%d%d_%d%d_%s.out",studentNum,tm.tm_mday,tm.tm_mon + 1, tm.tm_year + 1900,tm.tm_hour,tm.tm_min,operation);
      printf("\n%s\n",output);
      FILE* fp = fopen(output, "w");


      printf("Performing operation: %s\n",operation);

      //Now run the computations!!

      //SCALAR MULTIPLICATION
      if (strncmp(operation,"sm",2)==0) {
        printf("Computing Scalar Multiplication\n");
        printf("Read scalar: %f\n", scalar);
        CSR_Format CSRres = get_CSR_scalar(matrix_container1, scalar, num_threads);
        fprintf(fp, "sm\n");
        fprintf(fp,"%s\n",matrix_container1.name);
        fprintf(fp, "%d\n",num_threads);
        //need to unpack csr format...
        fp = CSR_Print(fp, CSRres, matrix_container1.n_rows, matrix_container1.m_columns, 0); //always float..
        fprintf(fp,"%f\n",matrix_container1.CSR_Matrix.time);
        fprintf(fp,"%f\n",CSRres.time);

      }

      //TRACE
      else if (strncmp(operation,"tr",2)==0) {
        double t = omp_get_wtime();
        fprintf(fp, "tr\n");
        fprintf(fp,"%s\n",matrix_container1.name);
        fprintf(fp, "%d\n",num_threads);
        if (matrix_container1.isInt==1) {
          int INTres = get_int_trace(matrix_container1, num_threads);
          fprintf(fp,"%d\n",INTres);
        } else {
          float FLTres = get_flt_trace(matrix_container1, num_threads);
          fprintf(fp,"%f\n",FLTres);
        }
        fprintf(fp,"%f\n",matrix_container1.CSR_Matrix.time);
        fprintf(fp,"%f\n",omp_get_wtime()-t);
      }

      //TRANSPOSE
      else if (strncmp(operation,"ts",2)==0) {
        COO_Format COOres = get_COO_transpose(matrix_container1, num_threads);
        fprintf(fp, "tp\n");
        fprintf(fp,"%s\n",matrix_container1.name);
        fprintf(fp, "%d\n",num_threads);
        fp = COO_Print(fp, COOres, matrix_container1.n_rows, matrix_container1.m_columns, matrix_container1.isInt); //always float..
        fprintf(fp,"%f\n",matrix_container1.COO_Matrix.time);
        fprintf(fp,"%f\n",COOres.time);

      }

      //ADDITION
      else if (strncmp(operation,"ad",2)==0) {
        CSR_Format CSRres = get_CSR_Addition(matrix_container1, matrix_container2);
        fprintf(fp, "ad\n");
        fprintf(fp,"%s\n",matrix_container1.name);
        fprintf(fp,"%s\n",matrix_container2.name);
        fprintf(fp, "%d\n",num_threads);
        fp = CSR_Print(fp, CSRres, matrix_container1.n_rows, matrix_container1.m_columns, matrix_container1.isInt);
        fprintf(fp,"%f\n",matrix_container1.CSR_Matrix.time+matrix_container2.CSR_Matrix.time);
        fprintf(fp,"%f\n",CSRres.time);
      }

      //MULTIPLICATION
      else if (strncmp(operation,"mm",2)==0) {
        printf("Computing Matrix Multiplication\n");
        CSR_Format CSRres = get_CSR_CSC_multiply(matrix_container1, matrix_container2);
        print_int_array(CSRres.IA, matrix_container1.n_rows+1, "inMAIN_IA");
        print_int_array(CSRres.JA, CSRres.lenNNZ, "inMAIN_JA");
        if (matrix_container1.isInt==1) {
          print_int_array((int*)CSRres.NNZ, CSRres.lenNNZ, "intMAINNNZ");
        } else {
          print_float_array((float*)CSRres.NNZ, CSRres.lenNNZ, "inMAINNNZ");
        }
        fprintf(fp,"mm\n");
        fprintf(fp,"%s\n",matrix_container1.name);
        fprintf(fp,"%s\n",matrix_container2.name);
        fprintf(fp, "%d\n",num_threads);
        fp = CSR_Print(fp, CSRres, matrix_container1.n_rows, matrix_container1.m_columns, matrix_container1.isInt);
        fprintf(fp,"%f\n",matrix_container1.CSR_Matrix.time+matrix_container2.CSR_Matrix.time);
        fprintf(fp,"%f\n",CSRres.time);
      }

      fclose(fp);
    }
    printf("DONE\n");
    return 0;
}
