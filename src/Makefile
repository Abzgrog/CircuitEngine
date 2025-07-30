CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lncurses
TARGET = Program

SRCS = main.c circuit.c globals.c utils.c ui.c factory.c program.c logger.c handle.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)