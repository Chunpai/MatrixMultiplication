Part_1_serial.out: matrix_mul.c generateSquareMatrix.c timing.c 
	gcc matrix_mul.c generateSquareMatrix.c timing.c -o Part_1_serial 

clean:
	rm *.o *.csv Part_1_serial 
