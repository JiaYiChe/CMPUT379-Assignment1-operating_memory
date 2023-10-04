all:mem_1 mem_2 mem_3 

mem_1: mem_1.o memlayout.o
	gcc -m32 mem_1.o memlayout.o -o mem_1
mem_2: mem_2.o memlayout.o
	gcc -m32 mem_2.o memlayout.o -o mem_2
mem_3: mem_3.o memlayout.o
	gcc -m32 mem_3.o memlayout.o -o mem_3
mem_1.o: mem_1.c 
	gcc -m32 -c mem_1.c 
mem_2.o: mem_2.c
	gcc -m32 -c mem_2.c
mem_3.o: mem_3.c
	gcc -m32 -c mem_3.c
memlayout.o:memlayout.c memlayout.h
	gcc -m32 -c memlayout.c 



.PHONY: clean
clean: rm mem_1 mem_1.o memlayout.o mem_2 mem_2.o

