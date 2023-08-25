# Compiler setup
CXX			:= g++
CXXFLAGS	:= -pipe -O3 -Wall -Wextra -fPIC `pkg-config --cflags opencv Qt5Widgets`

# Linker setup
LINK		:= g++
LFLAGS		:= -Wl,-O1
LIBS		:= `pkg-config --libs opencv Qt5Widgets` -lGL -lpthread

# Output directory
OBJECTS_DIR	:= ./

# Source files
SOURCES		:= main.cpp manager.cpp simulation.cpp moc_simulationmanager.cpp

# Object files
OBJECTS		:= $(SOURCES:.cpp=.o)

# Target setup
TARGET		:= simulator

# Build rule for target
$(TARGET): $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Build rule for source files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# Clean rule
clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)

# Phony targets
.PHONY: clean
