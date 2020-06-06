CC = gcc
COMMON_FLAGS = -Wall -Wextra -Wpedantic
ifdef DEBUG
	CFLAGS = $(COMMON_FLAGS) -g -O0
else
	CFLAGS = $(COMMON_FLAGS) -O3 -DNDEBUG
endif

all: ListRotations

ListRotations: src/main.o
	$(CC) $(CFLAGS) $(LINKER_FLAGS) -o ListRotations $^

clean:
	rm -f ListRotations
	rm -f src/*.o
