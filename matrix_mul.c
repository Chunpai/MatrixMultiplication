#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timing.h"
#include "generateSquareMatrix.h"

#define ARRAYSIZE(x)  (sizeof(x)/sizeof(*(x)))

//generate 3 matrices A,B,C with size n*n , 
//and store them into .csv files
//each row is a column of the matrix
void generateMatrices(int n){
    char mat1_name[128] = "A"; 
    generateSquareMatrix(n,mat1_name);

    char mat2_name[128] = "B"; 
    generateSquareMatrix(n,mat2_name);

    char mat3_name[128] = "C"; 
    generateSquareMatrix(n,mat3_name);
}




// Read matrices A,B,C stored in csv files into 2D arrays
void readMatrices(int n){
    FILE *fstream;
    char *record,*line;
    char buffer[1024];
    int i=0,j=0;
    double mat[n][n];
    fstream = fopen("A.csv","r");
    if(fstream==NULL){
        exit(-1);
    }

    printf("%d\n",n); 
    fscanf(fstream,"%[^\n]\n", NULL);

    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
         record = strtok(line,",");
         while(record != NULL)
         {
             printf("%f ",atof(record)) ;    //here you can put the record into the array as per your requirement.
             mat[i][j++] = atof(record);
             record = strtok(NULL,",");
         }
         ++i;
    }
    fclose(fstream);
    //fflush(stdin);
   
    /* 
    printf("%d\n",n); 

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%f ",mat[i][j]);
        }
        printf("\n");
    }
    */
    /*
    FILE *fp;
    fp = fopen("B.csv","r");
    if(fp==NULL){
        exit(-1);
    }
    fclose(fp);

    FILE *fp;
    fp = fopen("C.csv","r");
    if(fp==NULL){
        exit(-1);
    }
    fclose(fp);
    */
}


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
    //generateMatrices(n);    
    readMatrices(n);
    return 0;
}

