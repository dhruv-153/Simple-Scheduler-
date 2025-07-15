CPP = g++-12
#CFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow

all : main.cpp func_file.cpp
	@$(CPP) main.cpp func_file.cpp -o main
	@./main input.txt output.txt
