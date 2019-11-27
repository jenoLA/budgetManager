CC = gcc
Cflags = -Wall -Wextra \
		 -pedantic -pedantic

OBJECTS = main.o commands.o paper.o struct.o

%.o: src/%.c
	@$(CC) -c $^ -o $@

bgtmanager: $(OBJECTS)
	@$(CC) $(Cflags) $(OBJECTS) -o bgtmanager

clean:
	@rm bgtmanager

install:
	@sudo mv bgtmanager /usr/bin/
