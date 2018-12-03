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
	rm test_tree

# Include all your .o files in the below rule
obj: 537malloc.o wiki_tree.o

537malloc.o: 537malloc.c 537malloc.h rb_tree.h
	$(CC) -Wall -Wextra -g -O0 -c 537malloc.c

wiki_tree.o: wiki_tree.c rb_tree.h
	$(CC) -Wall -Wextra -g -O0 -c wiki_tree.c

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
