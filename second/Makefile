CC = gcc
FLAGS = -Wall -Werror -std=c11 -fsanitize=address
BIN = second

$(BIN): second.o second_helpers.o
	$(CC) -o $(BIN) $(FLAGS) $^

second.o: second.c
	$(CC) -c $^ $(FLAGS)

second_helpers.o: second_helpers.c
	$(CC) -c $^ $(FLAGS)

clean:
	rm -f $(BIN) *.o

