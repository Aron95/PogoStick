# Variables
CC = clang 
# Added -g for debugging and -O0 to ensure the code isn't optimized (which can skip lines in the debugger)
CFLAGS = -Wall -std=c99 -Wno-missing-braces -g -O0 
INCLUDE_PATHS = -I. -I$(shell brew --prefix raylib)/include
LDFLAGS = -L. -L$(shell brew --prefix raylib)/lib
LDLIBS = -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL

# Source files
SOURCES = main.c animations.c input.c collision/collision.c gameObject/gameObject.c gameObject/gameObjectDefinitions.c navigation/grid.c movement/movement.c
# Object files
OBJECTS = $(SOURCES:.c=.o)

# Name of your output file
TARGET = main

# The build rule
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

# Clean rule to remove the executable
clean:
	rm -f $(TARGET) $(OBJECTS)