CC=g++
CPPFLAGS=-g
OBJ= queue.o event.o messenger.o Request.o MessageTracker.o site.o RaymondTree.o simulator.o main.o

rts: $(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^

cool:
	@echo "making moo..... done!"

clean:
	rm -f *.o
	rm -f rts
