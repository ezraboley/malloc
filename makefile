CC = gcc
WARNING_FLAGS = -O0 -g -Wall -Wextra
EXE = 537memtest
SCAN_BUILD_DIR = scan-build-out

all: test_0 test_1 test_2 test_3 test_4 test_5 test_6 test_7 test_8 test_9 test_10 test_11 test_12

run_tests:
	./test_0
	./test_1
	./test_2
	./test_3
	./test_4
	./test_5
	./test_6
	./test_7
	./test_8
	./test_9
	./test_10
	./test_11
	./test_12

test_0: 
	$(CC) -o $@ wiki_tree.c 537malloc.c simple_testcase1.c

test_1:
	$(CC) -o $@ wiki_tree.c 537malloc.c simple_testcase2.c

test_2:
	$(CC) -o $@ wiki_tree.c 537malloc.c simple_testcase3.c

test_3:
	$(CC) -o $@ wiki_tree.c 537malloc.c simple_testcase4.c

test_4:
	$(CC) -o $@ wiki_tree.c 537malloc.c simple_testcase5.c

test_5:	
	$(CC) -o $@ wiki_tree.c 537malloc.c error_testcase1.c

test_6:
	$(CC) -o $@ wiki_tree.c 537malloc.c error_testcase2.c
	
test_7:
	$(CC) -o $@ wiki_tree.c 537malloc.c error_testcase3.c
	
test_8:
	$(CC) -o $@ wiki_tree.c 537malloc.c error_testcase4.c
	
test_9:
	$(CC) -o $@ wiki_tree.c 537malloc.c advanced_testcase1.c
	
test_10:
	$(CC) -o $@ wiki_tree.c 537malloc.c advanced_testcase2.c
	
test_11:
	$(CC) -o $@ wiki_tree.c 537malloc.c advanced_testcase3.c
	
test_12:
	$(CC) -o $@ wiki_tree.c 537malloc.c advanced_testcase4.c

537memtest: memtest.o
	$(CC) -o $(EXE) memtest.o 

memtest.o: memtest.c memtest.h
	$(CC) $(WARNING_FLAGS) -c memtest.c 

test_tree: test_tree.c rb_tree.h wiki_tree.c
	$(CC) $(WARNING_FLAGS) -otest_tree test_tree.c rb_tree.h wiki_tree.c

clean:
	#rm *.o
	#rm 537memtest
	#rm test_tree
	rm test_0
	rm test_1
	rm test_2
	rm test_3
	rm test_4
	rm test_5
	rm test_6 
	rm test_7
	rm test_8
	rm test_9
	rm test_10
	rm test_11
	rm test_12

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
