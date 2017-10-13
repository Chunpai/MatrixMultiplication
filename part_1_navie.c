/******************************************************************************
 * * FILE: part_1_navie.c 
 * * DESCRIPTION: this code will do following things 
 * 1. in command-line pass into size n of the matrices
 * 2. generate 3 matrices, and save them into A.csv, B.csv, C.csv
 * 3. read those 3 matrices from those *.csv files into 2D arrays 
 *      matA, matB, matC
 * 4. use 3 loops to compute the C = C + A*B
 * 5. print out the result matrix C on console
 * ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timing.h"
#include "generateSquareMatrix.h"

void generateMatrices(int n);
void matrixMulti(int n);


int main(int argc, char *argv[]){
    int n;
    if( argc == 2 ) {
        n = atoi(argv[1]);
    }
    else if( argc > 2 ) {
      printf("Too many arguments.\n");
      return -1;
    }
    else {
      printf("One argument expected.\n");
      return -1;
    }
    
    printf("%d\n",n); 
    generateMatrices(n);    
    matrixMulti(n);
    return 0;
}

//generate 3 matrices A,B,C with size n*n , 
//and store them into .csv files
//each row is a column of the matrix
void generateMatrices(int n){
    char mat1_name[128] = "A"; 
    generateSquareDoubleMatrix(n,mat1_name);

    char mat2_name[128] = "B"; 
    generateSquareDoubleMatrix(n,mat2_name);

    char mat3_name[128] = "C"; 
    generateSquareDoubleMatrix(n,mat3_name);
}



// Read matrices A,B,C stored in csv files into 2D arrays
// and do the calculation C = C+A*B
// and then print out C on console
void matrixMulti(int n){
    FILE *fstream;
    char *record,*line;
    char buffer[1024];
    int i,j,k;
    double matA[n][n],matB[n][n],matC[n][n];
    
    /*--------------------------------------read 3 matrices-----------------------------*/ 
    i=0;j=0;
    fstream = fopen("A.csv","r");
    if(fstream==NULL){
        exit(-1);
    }
    fgets(buffer,sizeof(buffer), fstream);  //skip the first line
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
         record = strtok(line,",");
         i = 0;
         while(record != NULL)
         {
             matA[i][j] = atof(record);
             record = strtok(NULL,",");
             i++;
         }
         j++;
    }
    int row = sizeof(matA) / sizeof(matA[0]);
    int col = sizeof(matA[0]) /sizeof(double);

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
         i = 0;
         while(record != NULL)
         {
             matB[i][j] = atof(record);
             record = strtok(NULL,",");
             i++;
         }
         j++;
    }
    fclose(fstream);

    i=0;j=0;
    printf("\n");
    fstream = fopen("C.csv","r");
    if(fstream==NULL){
        exit(-1);
    }
    fgets(buffer,sizeof(buffer), fstream);  //skip the first line
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
         record = strtok(line,",");
         i = 0;
         while(record != NULL)
         {
             matC[i][j] = atof(record);
             record = strtok(NULL,",");
             i++;
         }
         j++;
    }

    fclose(fstream);
    /*--------------------------------------finish reading matrices-----------------------------*/
    /*----------------------------------print out 3 matrices------------------------------------*/
    printf("Matrix A:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%f ",matA[i][j]);
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%f ",matB[i][j]);
        }
        printf("\n");
    }

    printf("Matrix C:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%f ",matC[i][j]);
        }
        printf("\n");
    }

    /*---------------------------------3 loops for calculation-----------------------------------*/
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                matC[i][j] = matC[i][j] + matA[i][k]*matB[k][j];
            }
        }
    }
    
    /*-------------------------print out the result matrix C-------------------------------------*/ 
    printf("Result Matrix C:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%f ",matC[i][j]);
        }
        printf("\n");
    }
}





