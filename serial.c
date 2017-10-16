/******************************************************************************
 * * FILE: serial.c 
 * * DESCRIPTION: this code will do following things 
 * 1. in command-line pass into size n of the matrices
 * 2. read matrices A and B which are stored in A.csv, B.csv, C.csv into 2D array
 * 3. use naive 3 loops to compute the C = A*B
 * 5. write the result matrix C into C_serial.csv
 * ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "timing.h"

void generateMatrices(int n);
void matrixMulti(int n);


int main(int argc, char *argv[]){
    timing_start();
    int n;
    if( argc == 2 ) {
        n = atoi(argv[1]);
    }
    else {
      printf("Wrong # of argument.\n");
      return -1;
    }
    
    matrixMulti(n);
    timing_stop();
    printf("Serial Execution Time:\n");
    print_timing();
    return 0;
}



// Read matrices A,B,C stored in csv files into 2D arrays
// and do the calculation C = C+A*B
// and then print out C on console
void matrixMulti(int n){
    FILE *fstream;
    char *record,*line;
    char buffer[1024000];
    int i,j,k;
    double matA[n][n],matB[n][n],matC[n][n];
    
    /*--------------------------------------read 2 matrices-----------------------------*/ 
    i=0;j=0;
    fstream = fopen("A.csv","r");
    if(fstream==NULL){
        exit(-1);
    }
    fgets(buffer,sizeof(buffer), fstream);  //skip the first line
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
         record = strtok(line,",");
         j = 0;
         while(record != NULL)
         {
             matA[i][j] = atof(record);
             record = strtok(NULL,",");
             j++;
         }
         i++;
    }
    fclose(fstream);


    i= 0;j=0;
    printf("\n");
    fstream = fopen("B.csv","r");
    if(fstream==NULL){
        exit(-1);
    }
    fgets(buffer,sizeof(buffer), fstream);  //skip the first line
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
         record = strtok(line,",");
         j = 0;
         while(record != NULL)
         {
             matB[i][j] = atof(record);
             record = strtok(NULL,",");
             j++;
         }
         i++;
    }
    fclose(fstream);
    fflush(stdin);


    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            matC[i][j] = 0;   
    /*---------------------------------3 loops for calculation-----------------------------------*/
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                matC[i][j] += matA[i][k]*matB[k][j];
            }
        }
    }
    
    /*-------------------------print out the result matrix C-------------------------------------*/ 

    FILE *fp;
    int matrixSize = n;
    char comma[2];
    fp = fopen("C_serial.csv", "w");
    fprintf(fp, "%d\n", matrixSize);
    for(i=0;i<matrixSize;i++)
    {
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;j++)
    {
      fprintf(fp, "%s%f",comma,matC[i][j]);
      sprintf(comma, "%s", ",");;
    }
      fprintf(fp, "\n");
    }
    fclose(fp);
    fflush(stdout);
}


