CC = gcc
FLAGS = -Wall -Werror -std=c11 -fsanitize=address
BIN = sixth

$(BIN): sixth.o sixth_helpers.o queue.o
	$(CC) -o $(BIN) $(FLAGS) $^

sixth.o: sixth.c
	$(CC) -c $^ $(FLAGS)

sixth_helpers.o: sixth_helpers.c
	$(CC) -c $^ $(FLAGS)

queue.o: queue.c
	$(CC) -c $^ $(FLAGS)

clean:
	rm -f $(BIN) *.o

