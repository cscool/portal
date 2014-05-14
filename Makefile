INC    = /usr/include
LOCINC = ./include
CFLAGS = -I $(INC) -I $(LOCINC) -g -O2
LIB    = ./lib
LIBFNT = $(LIB)/libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr
EFLAGS = -Wall -Wextra

all: log contains contact xwin createObjects createDoor ppm timing physics render portal

physics: $(LOCINC)/physics.cpp
	g++ $(LOCINC)/physics.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/physics.o

render: $(LOCINC)/render.cpp
	g++ $(LOCINC)/render.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/render.o

ppm: $(LOCINC)/ppm.c
	g++ $(LOCINC)/ppm.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/ppm.o

timing: $(LOCINC)/timing.c
	g++ $(LOCINC)/timing.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/timing.o

createObjects: $(LOCINC)/createObjects.cpp
	g++ $(LOCINC)/createObjects.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/createObjects.o

createDoor: $(LOCINC)/createDoor.cpp
	g++ $(LOCINC)/createDoor.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/createDoor.o

contains: $(LOCINC)/contains.cpp
	g++ $(LOCINC)/contains.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/contains.o

contact: $(LOCINC)/contact.cpp
	g++ $(LOCINC)/contact.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/contact.o

log: $(LOCINC)/log.c
	g++ $(LOCINC)/log.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/log.o

xwin: $(LOCINC)/xwin.c
	g++ $(LOCINC)/xwin.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/xwin.o

portal: portal.cpp $(LIB)/log.o $(LIB)/xwin.o $(LIB)/contact.o $(LIB)/contains.o $(LIB)/createObjects.o $(LIB)/createDoor.o $(LIB)/timing.o $(LIB)/ppm.o $(LIB)/physics.o $(LIB)/render.o
	
	g++ $(LIB)/*.o portal.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) $(LOCINC)/Box2D/libBox2D.a

clean:
	rm -f a.out *.o *.gch core *.log $(LIB)/*.o $(LOCINC)/*.o $(LOCINC)/*.gch

