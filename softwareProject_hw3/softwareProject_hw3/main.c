#include "ParserS.h"
#include"game.h"
#include"solver.h"
#include<stdio.h>


int main() {
	int seed = 3;
	srand(seed);
	puzzleGeneration(initNumberOfHints());
	playGame();
	return 0;
}