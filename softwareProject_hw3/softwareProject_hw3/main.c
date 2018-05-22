#include<time.h>
#include<stdio.h>
#include"solver.h"
#include <stdlib.h>
#include "ParserS.h"

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