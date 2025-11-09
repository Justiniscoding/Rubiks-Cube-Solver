COMPILER = gcc
FLAGS = $(shell pkg-config --libs --cflags raylib) -I./include -o
NAME = "Cube Solver"
MAIN = ./src/main.c

test:
	clear
	make clean
	make compile
	./$(NAME)

compile: $(MAIN)
	$(COMPILER) $(FLAGS) $(NAME) $(MAIN) $(filter-out ./src/main.c,$(wildcard ./src/*.c))

debug:
	$(COMPILER) $(FLAGS) $(NAME) $(MAIN) $(filter-out ./src/main.c,$(wildcard ./src/*.c)) -g
	gdb $(MAIN)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM


time: 
	make compile
	time ./$(NAME)
