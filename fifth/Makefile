CC = gcc
FLAGS = -Wall -Werror -std=c11 -fsanitize=address
BIN = fifth

$(BIN): fifth.o fifth_helpers.o stack.o
	$(CC) -o $(BIN) $(FLAGS) $^

fifth.o: fifth.c
	$(CC) -c $^ $(FLAGS)

fifth_helpers.o: fifth_helpers.c
	$(CC) -c $^ $(FLAGS)

stack.o: stack.c
	$(CC) -c $^ $(FLAGS)

clean:
	rm -f $(BIN) *.o

