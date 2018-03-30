CC=g++ $(CFLAGS)
CFLAGS=-g -O0 
all: quatTst
quatTst: quatTst.o Quat.o
	$(CC) quatTst.o Quat.o -o quatTst
quatTst.o: quatTst.cpp Quat.h
	$(CC) -c quatTst.cpp
Quat.o: Quat.cpp Quat.h
	$(CC) -c Quat.cpp
clean:
	rm -f *.o quatTst
