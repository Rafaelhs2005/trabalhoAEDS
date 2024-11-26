CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o ingrediente.o pizza.o
EXEC = pizzaria

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c ingrediente.h pizza.h
	$(CC) $(CFLAGS) -c main.c

ingrediente.o: ingrediente.c ingrediente.h
	$(CC) $(CFLAGS) -c ingrediente.c

pizza.o: pizza.c pizza.h ingrediente.h
	$(CC) $(CFLAGS) -c pizza.c

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)