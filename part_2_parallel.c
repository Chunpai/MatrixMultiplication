/******************************************************************************
 * * FILE: part_2_parallel.c 
 * * DESCRIPTION: this code will do following things 
 * 1. in command-line pass in 2 variables number and number of threads
 * 2. create threads and call the SumUpto in each thread
 * 3. print out the results of each thread
 * 4. join the threads 
 * 4. print out the total running time
 * ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "timing.h"
#include <pthread.h>

void *SumUpto(void *arg);


//first passed-in parameter is number, the second the number of thread 
int main(int argc, char *argv[]){
    timing_start();  // start the timing

    int number,num_threads;
    if( argc == 2 ){
        number = atoi(argv[1]);
        num_threads = 2;
    }
    else if( argc == 3 ) {
        number = atoi(argv[1]);
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
    
    pthread_t threads[num_threads];   //declare number of threads
    int rc;
    long t;
    for(t=0; t<num_threads;t++){
        rc = pthread_create(&threads[t], NULL, SumUpto, (void *)&number); //create threads, (void *)&number convert number's address to (void *) type
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    void *status;
    for(t=0; t<num_threads;t++){
        rc = pthread_join(threads[t],&status);  // need pthread_join to join threads first, otherwise, will not wait, and it will print wrong timing
        if (rc){
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    timing_stop(); //stop the timing
    print_timing();
    pthread_exit(NULL); //exit threads
}



//sum all the numbers from 0 to number in serial
//and prints the sum on stdout
void *SumUpto(void *arg){
    int i=0,sum=0;
    int number;
    number = *((int *)arg); //convert the passed-in parameter into (int *) type and access the value
    while(i <= number){
        sum += i;
        i++;
    }
    //printf("%d\n",sum);
    pthread_exit(NULL); //exit threads
}



