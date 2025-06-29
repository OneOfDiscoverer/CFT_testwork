BIN := main.out
SOURCES := main.c
HEADERS := main.h
CFLAGS := 

CC := gcc

.PHONY: clean

all: clean $(BIN) 

$LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH

$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) $(CFLAGS)
$(BIN): $(HEADERS)

clean:
		rm -rf $(BIN)