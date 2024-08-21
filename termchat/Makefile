# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Linker flags (if any libraries are required)
LDFLAGS_CLIENT = -lncurses
LDFLAGS_SERVER = 

# Source files for each target
SERVER_SRCS = server.c library.c
CLIENT_SRCS = client.c library.c window.c

# Object files for each target
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

# Dependencies (headers)
DEPS = library.h window.h

# Targets
SERVER_TARGET = server
CLIENT_TARGET = client

all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Build the server executable
$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS_SERVER)

# Build the client executable
$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS_CLIENT)

# Pattern rule for building object files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the server or client
run_server:
	./$(SERVER_TARGET)

run_client:
	./$(CLIENT_TARGET)

# Clean up
clean:
	rm -rf $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER_TARGET) $(CLIENT_TARGET)
