CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lncurses -lpanel
TARGET = Program

SRCS = main.c circuit.c globals.c utils.c ui.c factory.c program.c logger.c handle.c circuit_ui.c command_console.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=definite ./$(TARGET)
