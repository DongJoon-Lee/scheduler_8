run : scheduler.o
	gcc -o run scheduler.o -g

scheduler.o : scheduler.c
	gcc -c -o scheduler.o -g scheduler.c

clean:
	rm *.o scheduler
