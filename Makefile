# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra -std=c99

# Source files
SRC = src/gui.c

#src/gui.c src/game_engine.c src/player_behavior.c

# Output executable
OUT = myapp

# Libraries to link
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Default target
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

# Clean up
clean:
	rm -f $(OUT)

