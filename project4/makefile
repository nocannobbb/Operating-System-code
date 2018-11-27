all:FIFO.o Clock.o
	gcc -o FIFO FIFO.o
	gcc -o Clock Clock.o
FIFO.o:FIFO.c
	gcc -c FIFO.c myqueue.h
Clock.o:Clock.c
	gcc -c Clock.c myqueue.h
clean:
	rm *.o FIFO Clock
