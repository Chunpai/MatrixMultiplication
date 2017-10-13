/******************************************************************************
 * * FILE: part_2_serial.c 
 * * DESCRIPTION: this code will do following things 
 * 1. in command-line pass in 2 variables number and loop
 * 2. use SumUpto to do the summation in serial
 * 3. print out the results of each loop, 
 * 4. print out the total running time
 * ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "timing.h"

void SumUpto(int number);

//first passed-in parameter is number, the second is the loop
int main(int argc, char *argv[]){
    timing_start();

    int number,loop,i;
    if( argc == 2 ){
        number = atoi(argv[1]);
        loop = 2;
    }
    else if( argc == 3 ) {
        number = atoi(argv[1]);
        loop = atoi(argv[2]);
    }
    else if( argc > 3 ) {
      printf("Too many arguments.\n");
      return -1;
    }
    else {
      printf("One argument expected.\n");
      return -1;
    }
    
    for(i=0; i<loop;i++){
        SumUpto(number);
    }

    timing_stop();
    print_timing();
}



//sum all the numbers from 0 to number in serial
//and prints the sum on stdout
void SumUpto(int number){
    int i=0,sum=0;
    while(i <= number){
        sum += i;
        i++;
    }
    printf("%d\n",sum);
}



