CC = gcc
CFLAGS = -std=c11
LDFLAGS = -lncurses

SRCS = main.c library.c
OBJS = $(SRCS:.c=.o)
DEPS = library.h

TARGET = todo_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
