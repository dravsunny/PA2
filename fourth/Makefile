CC = gcc
FLAGS = -Wall -Werror -std=c11 -fsanitize=address
BIN = fourth

$(BIN): fourth.o fourth_helpers.o stack.o
	$(CC) -o $(BIN) $(FLAGS) $^

fourth.o: fourth.c
	$(CC) -c $^ $(FLAGS)

fourth_helpers.o: fourth_helpers.c
	$(CC) -c $^ $(FLAGS)

stack.o: stack.c
	$(CC) -c $^ $(FLAGS)

clean:
	rm -f $(BIN) *.o

