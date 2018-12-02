CC = gcc
WARNING_FLAGS = -O0 -g -Wall -Wextra
EXE = 537memtest
SCAN_BUILD_DIR = scan-build-out

537memtest: memtest.o
	$(CC) -o $(EXE) memtest.o 

memtest.o: memtest.c memtest.h
	$(CC) $(WARNING_FLAGS) -c memtest.c 

test_tree: test_tree.c rb_tree.h wiki_tree.c
	$(CC) $(WARNING_FLAGS) -otest_tree test_tree.c rb_tree.h wiki_tree.c

clean:
	rm *.o
	rm 537memtest
