CC = gcc
FLAGS = -Wall -Werror -std=c11 -fsanitize=address
BIN = first

$(BIN): first.o first_helpers.o
	$(CC) -o $(BIN) $(FLAGS) $^

first.o: first.c
	$(CC) -c $^ $(FLAGS)

first_helpers.o: first_helpers.c
	$(CC) -c $^ $(FLAGS)

clean:
	rm -f $(BIN) *.o

