CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = 

SRCS = main.c library.c
OBJS = $(SRCS:.c=.o)
DEPS = library.h

TARGET = pomo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
