CC=g++					# C compiler

CFLAGS=-I. -g -Wall -O3 -march=native -fopenmp `pkg-config --cflags --libs opencv` # list of flags
# include after "-march=native" if needed: -I/usr/local/include -L/usr/lib -lglut -lGLU -lGL

LIBS=-lm

DEPS=game.h				# dependency on the include files		

OBJ= matrix.o interface.o bfs.o GA.o carnivores.o main.o 


# rule for files ending in .o (.o file depends upon the .c version of the file and the .h files in the DEPS macro)

%.o: %.c $(DEPS)		
	$(CC) -c -o $@ $< $(CFLAGS)

### -o $@ puts the output on the left side of the :
### $< is the first item in the dependencies list




prog: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

### $@ left side of :
### $^ right side of the :

.PHONY: run

run:
	./prog

.PHONY: clean

clean:
	rm -f *.o  

.PHONY: debug

debug:
	gdb ./prog
