.PHONY: all test

all: 
	g++ -g Phase2Main.cpp -o Phase2

test:
	g++ -g TestingSuite.cpp RBTree.cpp -o test

valall:
	valgrind -s --leak-check=full --show-leak-kinds=all ./Phase2

valtest:
	valgrind -s --leak-check=full --show-leak-kinds=all ./test 5