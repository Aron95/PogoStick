# Variables
CC = clang
CFLAGS = -Wall -std=c99 -Wno-missing-braces -g -O0

# OS Detection
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    # Linux-specific settings
    INCLUDE_PATHS = -I. $(shell pkg-config --cflags raylib)
    LDFLAGS = -L. $(shell pkg-config --libs raylib)
    LDLIBS = $(shell pkg-config --libs raylib)
    CLEAN_COMMAND = rm -f
else ifeq ($(UNAME_S),Darwin)
    # macOS-specific settings
    INCLUDE_PATHS = -I. -I$(shell brew --prefix raylib)/include
    LDFLAGS = -L. -L$(shell brew --prefix raylib)/lib
    LDLIBS = -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
    CLEAN_COMMAND = rm -f
else ifeq ($(UNAME_S),MINGW64_NT)
    # Windows (MinGW/MSYS2) specific settings
    # Assuming raylib is installed via MSYS2/MinGW-w64 or manually linked
    # You might need to adjust these paths based on your installation
    INCLUDE_PATHS = -I. -I/usr/local/include
    LDFLAGS = -L. -L/usr/local/lib
    LDLIBS = -lraylib -lwinmm -lgdi32
    CLEAN_COMMAND = del
else
    # Default / Fallback settings (can be adjusted or made to error out)
    $(error OS not supported: $(UNAME_S). Please add support for your OS.)
endif

# Source files
SOURCES = main.c animation/animations.c input/input.c collision/collision.c gameObject/gameObject.c gameObject/gameObjectDefinitions.c navigation/grid.c movement/movement.c
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
	$(CLEAN_COMMAND) $(TARGET) $(OBJECTS)
