INC    = /usr/include
LOCINC = ./include
CFLAGS = -I $(INC) -I $(LOCINC) -g -O2
LIB    = ./lib
LIBFNT = $(LIB)/libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr
EFLAGS = -Wall -Wextra

all: log contains contact xwin createObjects timing lab1

timing: $(LOCINC)/timing.c
	g++ $(LOCINC)/timing.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/timing.o

createObjects: $(LOCINC)/createObjects.cpp
	g++ $(LOCINC)/createObjects.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -lBox2D -c -o $(LIB)/createObjects.o

contains: $(LOCINC)/contains.cpp
	g++ $(LOCINC)/contains.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -lBox2D -c -o $(LIB)/contains.o

contact: $(LOCINC)/contact.cpp
	g++ $(LOCINC)/contact.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -lBox2D -c -o $(LIB)/contact.o

log: $(LOCINC)/log.c
	g++ $(LOCINC)/log.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/log.o

xwin: $(LOCINC)/xwin.c
	g++ $(LOCINC)/xwin.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/xwin.o

lab1: lab1.cpp $(LIB)/log.o $(LIB)/xwin.o $(LIB)/contact.o $(LIB)/contains.o $(LIB)/createObjects.o $(LIB)/timing.o
	g++ $(LIB)/*.o lab1.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -lBox2D

clean:
	rm -f a.out *.o *.gch core *.log $(LIB)/*.o $(LOCINC)/*.o $(LOCINC)/*.gch

