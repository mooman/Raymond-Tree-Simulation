CC=g++
CPPFLAGS=-g
OBJ= queue.o event.o messenger.o site.o RaymondTree.o simulator.o main.o

rts: $(OBJ)
	g++ -g -o rts $(OBJ)

cool:
	@echo "making moo..... done!"

clean:
	rm -f *.o
	rm -f rts
