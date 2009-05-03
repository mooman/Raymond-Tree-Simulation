CC=g++
CPPFLAGS=-g
OBJ= queue.o event.o messenger.o simulator.o main.o

rts: $(OBJ)
	g++ -o rts $(OBJ)

clean:
	rm -f *.o
	rm -f rts
