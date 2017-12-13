all: main.c tree.o queue.o
	gcc -DTEST main.c tree.o queue.o -o Lab10

tree.o: tree.c
	gcc -DTEST -c tree.c

queue.o: queue.c
	gcc -DTEST -c queue.c
