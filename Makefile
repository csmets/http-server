CC = gcc

FILES = src/server.c \
				src/header.c \
				src/utils.c \
				src/server_response.c

BUILD_DIR = ./build/
BIN = $(BUILD_DIR)server

build:
	mkdir $(BUILD_DIR)
	$(CC) $(FILES) -o $(BIN)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build
