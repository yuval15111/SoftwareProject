#include<time.h>
#include<stdio.h>
#include"solver.h"
#include <stdlib.h>
#include "ParserS.h"

/*
The main function is in charge of doing only one time srand with the seed we will get from the user,
after that, we will call the function that generate our board with the number of hints that the
user ask to get.
Finally - we will start the game with the playGame() func.
*/
int main(int argc, char* argv[]) {
	int seed;
	if (argc == 2) {
		seed = atoi(argv[1]);
		srand(seed);
		puzzleGeneration(initNumberOfHints());
		playGame();
	}
	return 0;
}