CC = g++          # C++ compiler

CPPFLAGS = -I. -g -Wall -O3 -march=native -lglut -lGLU -lGL -fopenmp `pkg-config --cflags opencv4`
# include after "-march=native" if needed: -I/usr/local/include -L/usr/lib -lglut -lGLU -lGL

LDFLAGS = -fopenmp
LDLIBS = -lm `pkg-config --libs opencv`

DEPS = game.h macros.h   # dependency on the include files

OBJ = output.o matrix.o interface.o bfs.o GA.o carnivores.o main.o

# Rule for building object files
%.o: %.cpp $(DEPS)
	$(CC) $(CPPFLAGS) -c -o $@ $<

### -o $@ puts the output on the left side of the :
### $< is the first item in the dependencies list


# The main program target
prog: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

### $@ left side of :
### $^ right side of the :


.PHONY: run clean debug

run:
	./prog

clean:
	rm -f *.o prog

debug:
	gdb ./prog
