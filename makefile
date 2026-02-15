COMPILER = clang++
# FLAGS = $(shell pkg-config --libs --cflags raylib) -I./include -o
FLAGS = -I ./include -o
NAME = RubiksCubeSolver
MAIN = ./src/main.cpp

test:
	make clean
	make compile
	clear
	./$(NAME)

compile: $(MAIN)
	$(COMPILER) $(FLAGS) $(NAME) $(MAIN) $(filter-out ./src/main.cpp,$(wildcard ./src/*.cpp))

debug:
	$(COMPILER) $(FLAGS) $(NAME) $(MAIN) $(filter-out ./src/main.cpp,$(wildcard ./src/*.cpp)) -gdwarf-4 -g
	lldb ./$(NAME)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM


time: 
	make compile
	time ./$(NAME)

