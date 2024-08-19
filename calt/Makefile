CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11
LDFLAGS = -lm

SRCS = main.c stack.c queue.c
OBJS = $(SRCS:.c=.o)
DEPS = stack.h queue.h

TARGET = calt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
