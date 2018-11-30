all:pro1.o pro2.o
	g++ -o task1 pro1.o -lpthread
	g++ -o task2 pro2.o -lpthread
pro1.o:pro1.c
	g++ -c pro1.c
pro2.o:pro2.c
	g++ -c pro2.c
clean:
	rm *.o task1 task2
