Author: Chunpai Wang   
Email:  cwang25@albany.edu   
Date:   10/14/2017  

### Files:
```
    README                  - this file
    Makefile                - Makefile to compile all codes 
    serial.c                - navie implementation of matrix multiplication
    parallel.c              - parallel implementation of part 3, serial implementation is use command-line parameter P = 1
    generateSquareMatrix.c  - used to generate square matrices
    timing.c                - used to count the time
    timing.h                - header file
    
    A.csv                   - where matrix A is stored
    B.csv                   - where matrix B is stored
    C_serial.csv            - where matrix C result from serial program is stored
    C_parallel.csv          - where matrix C result from parallel program is stored

    generateSquareMatrix.out   - binary code 
    serial.out                 - binary code
    parallel.out               - binary code
```

```
Use commmands:
       make
                :- to compile and get the corresponding binary codes 
       
       ./generateMatrices.out N
                :- N is the matrix size

       ./serial.out N 
                :- N is the matrix size

       ./parallel.out N P 
                :- N is the matrix size, P is the number of threads

       make clean 
                :- clear all binary codes and matrices files which store in .csv
```
        
