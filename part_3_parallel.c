/******************************************************************************
 * * FILE: part_1_navie.c 
 * * DESCRIPTION: this code will do following things 
 * 1. in command-line pass into 2 variables:  size n of the matrices, and number of threads
 * 2. generate 1 N*N matrix, and save it into N.csv
 * 3. read this matrix from N.csv file into a 2D arrays called matN
 * 4. save information, such matrix size, thread_id, chunk_size for each thread to count,
 *          and the address of the matrix, as a struct, and pass it as thread argument 
 * 4. each thread will count their own chunk of matrix, and store the counts in a size 10 array
 * 5. each thread return the address of their own count array back to main thread
 * 6. join all threads, and do the summation
 * 7. print out the distributions
 * ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timing.h"
#include <pthread.h>
#include "generateSquareMatrix.h"

//define a struct type, which is used to pass into each thread function
typedef struct thread_data{
    int thread_id;   
    int N;           //size of matrix
    int chunk_size;  // almost equal chunk size of matrix for each thread
    int *matrix;     // the address of the matrix
}thread_data;

void generateMatrix(int n);
void *Count(void *arg);


//first passed-in parameter is number, the second is the loop
int main(int argc, char *argv[]){
    timing_start();  // start the timing
    
    int N,num_threads;  
    //argument checking
    if( argc == 2 ){
        N = atoi(argv[1]);
        num_threads = 1;
    }
    else if( argc == 3 ) {
        N = atoi(argv[1]);
        num_threads = atoi(argv[2]);
    }
    else if( argc > 3 ) {
      printf("Too many arguments.\n");
      return -1;
    }
    else {
      printf("One argument expected.\n");
      return -1;
    }
    //end of argument checking

    FILE *fstream;
    char *record,*line;
    char buffer[1024];
    int i,j,k;
    int matN[N][N];

    generateMatrix(N);
    
    //start reading the matrix
    i=0;j=0;
    fstream = fopen("N.csv","r");
    if(fstream==NULL){
        exit(-1);
    }
    fgets(buffer,sizeof(buffer), fstream);  //skip the first line
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
         record = strtok(line,",");
         i = 0;
         while(record != NULL)
         {
             matN[i][j] = atof(record);
             record = strtok(NULL,",");
             i++;
         }
         j++;
    }
    fclose(fstream);
    //end of reading matrix and print out matrix
    printf("Matrix N:\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d ",matN[i][j]);
        }
        printf("\n");
    }

    pthread_t threads[num_threads];   //declare number of threads
    int rc;
    long t;
    thread_data *tdata;
    for(t=0; t<num_threads;t++){
        //thread_data tdata;
        tdata = (thread_data *) malloc(sizeof(thread_data));
        (* tdata).thread_id = t;
        (* tdata).N = N;
        (* tdata).chunk_size = N*N/num_threads;
        //tdata->matrix = (int*) malloc(sizeof(int)*N*N);
        (* tdata).matrix =(int *) &matN;  
        //printf("matN address %p\n",matN);
        //(* tdata).matrix = matN;
        rc = pthread_create(&threads[t], NULL, Count, (void *) tdata); //create threads, (void *)&number convert number's address to (void *) type
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    void *status;  //used to store the return value of each thread
    int dist[10] = {0};
    for(t=0; t<num_threads;t++){
        rc = pthread_join(threads[t],&status);  // need pthread_join to join threads first
        for(k=0;k<N;k++){    
            dist[k] += *((int *)status+k);
            //printf("t:%d %d\n",t,*((int *)status+k));  //used to check if every thread return the value with same address
        }
        free(status);   //free the return array from each thread.
        //printf("value of rc: %d",rc); //used to check the return values from each threads
        if (rc){
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }
    
    printf("Distributions: (value:count)");
    for(i=0;i<N;i++){
        printf("\n(%d:%d) ",i+1,dist[i]);
    }
    printf("\n");
    timing_stop(); //stop the timing
    print_timing();
    pthread_exit(NULL); //exit threads
}




//generate 3 matrices A,B,C with size n*n , 
//and store them into .csv files
//each row is a column of the matrix
void generateMatrix(int n){
    char mat1_name[128] = "N"; 
    generateSquareIntMatrix(n,mat1_name);
}



//we view matrix as a large 1-D array in memory, and 
//split this 1-D array into several chunks to each thread
//calculate the startIndex and endIndex of the chunk in this 1-D array
//count the distributions
void *Count(void *arg){
    int *distribution = (int *) malloc(10*sizeof(int));  //initilize an array with all 0's, note!! don;t use static type, may race condition
    int i, j,val,startIndex,endIndex;
    //int number = *((int *)arg); //convert the passed-in parameter into (thread_data *) type and assign the address
    thread_data *data = (thread_data *)arg;
    //printf("matN address %p\n",data->matrix);
    startIndex = data->thread_id * data->chunk_size;
    if( (data->N *data->N) - (data->thread_id+1)*(data->chunk_size) < data->chunk_size){
        endIndex = data->N * data->N ;
    }
    else{
        endIndex = (data->thread_id+1)*(data->chunk_size);
    }
    for(i= startIndex; i < endIndex; i++) {
        val = *(data->matrix + i);  //access the its own chunk of matN 
        distribution[val-1] += 1;   // aggregate the count into the array distribution
    }
    
    //used to check the counting 
    //for(i=0;i<10;i++){
    //    printf("%d: %d\n",data->thread_id,distribution[i]);
    //} 

    printf("\n");
    free(arg);
    pthread_exit((void *)distribution);
}



