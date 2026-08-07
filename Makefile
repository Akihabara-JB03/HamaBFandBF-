CC = gcc
CFLAGS = -Wall

TARGET = brainfuck.exe

SRCS = intp.c jmp.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	del $(TARGET)