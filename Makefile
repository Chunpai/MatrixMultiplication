All: generateSquareMatrix.out serial.out parallel.out

generateSquareMatrix.out: generateSquareMatrix.c
	gcc generateSquareMatrix.c -o generateSquareMatrix.out

serial.out: serial.c timing.c 
	gcc serial.c timing.c -o serial.out

parallel.out: parallel.c timing.c
	gcc parallel.c timing.c -o parallel.out -pthread

clean:
	rm *.csv *.out
