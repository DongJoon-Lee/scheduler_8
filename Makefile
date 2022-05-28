main : main.o
	gcc -o main main.o -g -lpthread

main.o : main.c
	gcc -c -o main.o -g main.c

clean :
	rm *.o main
