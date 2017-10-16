/******************************************************************************
 * * FILE: parallel.c 
 * * DESCRIPTION: this code will do following things 
 * 1. in command-line pass into size n of the matrices, and number of threads
 * 2. read those 2 matrices from those A.csv and B.csv files into 2D arrays 
 * 3. create threads and assign row vectors of A and B to each thread, 
 *      note that, each thread may have different number of row vectors
 * 4. for each thread, do multiple vector_in_A * vector_in_B outer product
 * 5. use mutex to avoid race condition and  do the synchronize once one outer product complete.
 * 6. There are N time synchronizations, where N is the number of row size 
 * ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "timing.h"
#include <pthread.h>


pthread_mutex_t matC_mutex;  //declare a mutex for matrix matC
//define a struct type, which is used to pass into each thread function
typedef struct thread_data{
    int thread_id;   
    int N;
    int startRow;
    int endRow;  
    double *matA;
    double *matB;
    double *matC;     // the address of the matrix
}thread_data;


void *VectorMul(void *arg){
    thread_data *data = (thread_data *)arg;
    int startRow = data->startRow;
    int endRow = data->endRow;
    double *matA = data->matA;
    double *matB = data->matB;
    double *matC = data->matC;
    int N = data->N;
    int i, j, k;
    //double Aij,Bik;

    for(i= startRow; i < endRow; i++) {
        pthread_mutex_lock(&matC_mutex);
        for(j=0; j<N ; j++){
            //pthread_mutex_lock(&matC_mutex);
            for(k=0; k<N; k++){
                //Aij = *(data->matA + i*(data->N) + j);
                //Bik = *(data->matB + i*(data->N) + k);
                //*(data->matC + j*data->N + k) += Aij * Bik;
                //pthread_mutex_lock(&matC_mutex);   //if set lock inside these loops, it will be much slower
                *(matC + j*N + k) += *(matA + i*N + j) * *(matB + i*N + k);
                //pthread_mutex_unlock(&matC_mutex);  
            }    
            //pthread_mutex_unlock(&matC_mutex);  
        }
        pthread_mutex_unlock(&matC_mutex);
    }
    free(arg); //free the memory
    pthread_exit(NULL); //exit threads
}


// Read matrices A,B,C stored in csv files into 2D arrays
// and do the calculation C = C+A*B
// and then print out C on console
int main(int argc, char *argv[]){
    timing_start();
    int n, num_threads; 
    if( argc == 3 ) {
        n = atoi(argv[1]);
        num_threads = atoi(argv[2]);
    }
    else {
      printf("Wrong Arguments.\n");
      return -1;
    }

    FILE *fp;
    char *record,*line;
    char buffer[1024000];
    int i,j,k;
    double matA[n][n],matB[n][n];
    
    /*--------------------------------------read 2 matrices-----------------------------*/ 
    i=0;j=0;
    fp = fopen("A.csv","r");
    if(fp==NULL){
        exit(-1);
    }
    fgets(buffer,sizeof(buffer), fp);  //skip the first line
    while((line=fgets(buffer,sizeof(buffer),fp))!=NULL){
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
    fclose(fp);
    fflush(stdin);

    i= 0;j=0;
    fp = fopen("B.csv","r");
    if(fp==NULL){
        exit(-1);
    }
    fgets(buffer,sizeof(buffer), fp);  //skip the first line
    while((line=fgets(buffer,sizeof(buffer),fp))!=NULL){
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
    fclose(fp);
    fflush(stdin);

    //initialize the mutex
    if (pthread_mutex_init(&matC_mutex, NULL) != 0)
    {
        perror("\n mutex init failed\n");
        exit(-1);
    }

    pthread_t threads[num_threads];   //declare number of threads
    int rc;
    int t;
    thread_data *tdata;
    double matC[n][n];
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            matC[i][j] = 0;   


    int num_rows_assigned[num_threads];
    //assign the different number of rows of matrices to each thread
    for(i=0;i<num_threads;i++){
        num_rows_assigned[i] = n/num_threads;
    }
    int remain = n%num_threads;
    if(remain!=0){
        for(i=0;i<remain;i++){
            num_rows_assigned[i]++;
        }
    }
    

    int row = 0;
    //printf("Main matA address %p\n",matA);
    //printf("Main matB address %p\n",matB);
    //printf("Main matC address %p\n",matC);
    for(t=0; t<num_threads;t++){
        //thread_data tdata;
        tdata = (thread_data *) malloc(sizeof(thread_data));
        tdata->thread_id = t;
        tdata->N = n;
        tdata->startRow = row;
        tdata->endRow = row+num_rows_assigned[t];
        row = row+num_rows_assigned[t];
        //tdata->matrix = (int*) malloc(sizeof(int)*N*N);
        //printf("%d,%d,%d\n",tdata->thread_id,tdata->startRow,tdata->endRow);
        tdata->matA =(double *) &matA;  
        tdata->matB =(double *) &matB;  
        tdata->matC =(double *) &matC;  
        //(* tdata).matrix = matN;
        rc = pthread_create(&threads[t], NULL, VectorMul, (void *) tdata); //create threads
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    

    void *status;  //used to store the return value of each thread
    for(t=0; t<num_threads;t++){
        rc = pthread_join(threads[t],&status);  // need pthread_join to join threads first
        //free(status);   //free the return array from each thread.
        //printf("value of rc: %d",rc); //used to check the return values from each threads
        if (rc){
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }
    
    
    //printf("Main matA address %p\n",matA);
    //printf("Main matB address %p\n",matB);
    //printf("Main matC address %p\n",matC);
    char comma[2];
    fp = fopen("C_parallel.csv", "w");
    fprintf(fp, "%d\n", n);
    for(i=0;i<n;i++)
    {
    sprintf(comma, "%s", "");
    for(j=0;j<n;j++)
    {
      fprintf(fp, "%s%f",comma,matC[i][j]);
      sprintf(comma, "%s", ",");;
    }
      fprintf(fp, "\n");
    }
    fclose(fp);
    

    pthread_mutex_destroy(&matC_mutex);
    printf("\n");
    timing_stop(); //stop the timing
    printf("Parallel Execution Time:\n");
    print_timing();
    pthread_exit(NULL); //exit threads
}





