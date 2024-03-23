CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm -ljpeg

SRCS = main.c library.c
OBJS = $(SRCS:.c=.o)
DEPS = library.h

TARGET = asciigen

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
