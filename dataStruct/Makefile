
CC = clang
CFLAGS = -Wall -Wextra -std=c11 -g

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    # macOS-specific settings
    INCLUDE_PATHS = -I../ -I$(shell brew --prefix raylib)/include
    LDFLAGS = -L$(shell brew --prefix raylib)/lib
    LDLIBS = -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
else
    # Default / Fallback settings, adjust as needed for other OS
    INCLUDE_PATHS = -I../ -I/usr/local/include
    LDFLAGS = -L/usr/local/lib
    LDLIBS = -lraylib
endif

TARGET_TEST = priorityQueueTest
SOURCES = priorityQueue.c priorityQueueTest.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean test

all: $(TARGET_TEST)

$(TARGET_TEST): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

test: $(TARGET_TEST)
	./$(TARGET_TEST)

clean:
	rm -f $(TARGET_TEST) $(OBJECTS)
