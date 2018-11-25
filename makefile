CC = gcc
WARNING_FLAGS = -O0 -g -Wall -Wextra
EXE = 537memtest
SCAN_BUILD_DIR = scan-build-out

537memtest: memtest.o
	$(CC) -o $(EXE) memtest.o 

memtest.o: memtest.c memtest.h
	$(CC) $(WARNING_FLAGS) -c memtest.c 

clean:
	rm *.o
	rm 537memtest
