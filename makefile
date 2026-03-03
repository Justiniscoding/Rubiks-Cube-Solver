COMPILER = clang++
FLAGS = -I ./include -o
NAME = RubiksCubeSolver
MAIN = ./src/main.cpp

# arduino_compile:
# 	arduino-cli compile --fqbn arduino:avr:mega arduino
# 	arduino-cli upload --fqbn arduino:avr:mega arduino -p /dev/cu.usbmodem11101

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

