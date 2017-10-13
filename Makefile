All: Part_1_navie.out Part_1_opt.out Part_2_serial.out Part_2_parallel.out Part_3_parallel.out

Part_1_navie.out: part_1_navie.c generateSquareMatrix.c timing.c 
	gcc part_1_navie.c generateSquareMatrix.c timing.c -o Part_1_navie.out

Part_1_opt.out: part_1_opt.c generateSquareMatrix.c timing.c 
	gcc part_1_opt.c generateSquareMatrix.c timing.c -o Part_1_opt.out

Part_2_serial.out: part_2_serial.c timing.c
	gcc part_2_serial.c timing.c -o Part_2_serial.out

Part_2_parallel.out: part_2_parallel.c timing.c
	gcc part_2_parallel.c timing.c -o Part_2_parallel.out -lpthread

Part_3_parallel.out: part_3_parallel.c timing.c generateSquareMatrix.c
	gcc part_3_parallel.c generateSquareMatrix.c timing.c -o Part_3_parallel.out -lpthread

clean:
	rm *.csv *.out
