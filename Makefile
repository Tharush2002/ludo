# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra -std=c99

# Source files
SRC = src/main.c src/gui.c src/board_mapping.c src/utils.c src/game_engine.c

# Output executable
OUT = ludo

# Libraries to link
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Default target
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

# Clean up
clean:
	rm -f $(OUT)

