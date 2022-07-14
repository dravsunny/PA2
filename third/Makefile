CC = gcc
FLAGS = -Wall -Werror -std=c11 -fsanitize=address
BIN = third

$(BIN): third.o third_helpers.o queue.o
	$(CC) -o $(BIN) $(FLAGS) $^

third.o: third.c
	$(CC) -c $^ $(FLAGS)

third_helpers.o: third_helpers.c
	$(CC) -c $^ $(FLAGS)

queue.o: queue.c
	   $(CC) -c $^ $(FLAGS)

clean:
	rm -f $(BIN) *.o

