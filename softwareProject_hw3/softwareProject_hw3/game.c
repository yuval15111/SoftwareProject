#include<stdio.h>
#include<stdlib.h>
#include "solver.h"
#include "ParserS.h"

Cell** solvedSudoku;
Cell** currentSudoku;

Cell* createCell(int value) {
	Cell* cell = (Cell*)malloc(sizeof(Cell));
	if (cell == NULL) {
		printf("Error: createCell has failed\n");
		exit(0);
	}
	cell->value = value;
	cell->fixed = 0;
	cell->empty = 0;
	cell->arr[0] = 0;
	return cell;
}

Cell* copyCell(Cell* cell) {
	Cell* newCell = (Cell*)malloc(sizeof(Cell));
	if (newCell == NULL) {
		printf("Error: copyCell has failed\n");
		exit(0);
	}
	newCell->empty = cell->empty;
	newCell->fixed = cell->fixed;
	newCell->value = cell->value;
	return newCell;

}

bool isRowValidGame(Cell** sudoku, int row, int col, int num) {
	int j = 0;
	for (j = 0; j < width; j++) {
		if (sudoku[(row)*width + j]->value == num) {
			if (j != col) {
				return false;
			}
		}
	}
	return true;
}

bool isColValidGame(Cell** sudoku, int row, int col, int num) {
	int i;
	for (i = 0; i < height; i++) {
		if (sudoku[i*width + col]->value == num) {
			if (i != row) {
				return false;
			}
		}
	}
	return true;
}

bool isBlockValidGame(Cell** sudoku, int startRow, int startCol, int row, int col, int num) {
	int i, j;
	for (i = 0; i < blockHeight; i++) {
		for (j = 0; j < blockWidth; j++) {
			if (sudoku[(i + startRow)*width + j + startCol]->value == num) {
				if (row != i + startRow || col != j + startCol) {
					return false;
				}
			}
		}
	}
	return true;
}

void validate(Cell** currentSudoku) {
	Cell** newSolvedSudoku;
	newSolvedSudoku = determenisticBacktrack(currentSudoku);
	if (newSolvedSudoku == NULL) {
		printf("Validation failed: board is unsolvable\n");
	}
	else {
		freeSudoku(solvedSudoku);
		solvedSudoku = newSolvedSudoku;
		printf("Validation passed: board is solvable\n");
	}
}

void hint(int row, int col) { 
	printf("Hint: set cell to %d\n", solvedSudoku[row*width + col]->value);
}

bool isGameOver(Cell** sudoku) {
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (sudoku[i*width + j]->empty == 0) {
				return false;
			}
		}
	}
	return true;
}

void set(Cell** currentSudoku, int row, int col, int val, char* oldCommand) {
	bool rowValid, colValid, blockValid;
	char* command;
	if (currentSudoku[row*width + col]->fixed == 1) {
		printf("Error: cell is fixed\n");
	}
	else {
		if (val == 0) {
			currentSudoku[row*width + col]->value = 0;
			currentSudoku[row*width + col]->empty = 0;
			printSudoku(currentSudoku);
		}
		else {
			rowValid = isRowValidGame(currentSudoku, row, col, val);
			colValid = isColValidGame(currentSudoku, row, col, val);
			blockValid = isBlockValidGame(currentSudoku, row - row % blockWidth, col - col % blockHeight, row, col, val);
			if (rowValid && colValid && blockValid) {
				currentSudoku[row*width + col]->value = val;
				currentSudoku[row*width + col]->empty = 1;
				printSudoku(currentSudoku);
				if (isGameOver(currentSudoku)) {
					printf("Puzzle solved successfully\n");
					free(oldCommand);
					command = getCommand();
					while (command[0] != '4' && command[0] != '5') {
						if (command[0] == '1' || command[0] == '2' || command[0] == '3') {
							printf("Error: invalid command\n");
						}
						free(command);
						command = getCommand();
					}
					if (command[0] == '4') {
						free(command);
						restart();
					}
					else {
						free(command);
						exitGame();
					}
				}
			}
			else {
				printf("Error: value is invalid\n");
			}
		}
	}
}


void exitGame() {
	freeSudoku(currentSudoku);
	freeSudoku(solvedSudoku);
	printf("Exiting...\n");
	exit(0);
}

void restart() {
	freeSudoku(currentSudoku);
	freeSudoku(solvedSudoku);
	puzzleGeneration(initNumberOfHints());
	playGame();
}

void doCommand(char* command) {
	if (command[0] == '1') {
		set(currentSudoku, (command[2] - '0') - 1, (command[1] - '0') - 1, command[3] - '0', command);
	}
	else if (command[0] == '2') {
		hint((command[2] - '0') - 1, (command[1] - '0') - 1);
	}
	else if (command[0] == '3') {
		validate(currentSudoku);
	}
	else if (command[0] == '4') {
		free(command);
		restart();
	}
	else if (command[0] == '5') {
		free(command);
		exitGame();
	}
	free(command);
}

void printSudoku(Cell** sudoku) {
	int i = 0, j = 0, k = 0;
	for (k = 0; k < height; k++) {
		if (k % 3 == 0) {
			printf("----------------------------------\n");
		}
		printf("|");
		for (j = 0; j < width; j++) {
			if (sudoku[k* width + j]->fixed == 1) {
				printf(" .");
				printf("%d", sudoku[k* width + j]->value);
			}
			else if (sudoku[k* width + j]->empty == 0) {
				printf("   ");
			}
			else {
				printf("  %d", sudoku[k* width + j]->value);
			}
			if ((j + 1) % 3 == 0) {
				printf(" |");
			}
		}
		printf("\n");
	}
	printf("----------------------------------\n");
}

void getSolvedSudoku(Cell** boardGeneration) {/*take the pointer from solved Sudoku in solver to currentSudoku*/
	solvedSudoku = boardGeneration;
}

void getSudokuWithHints(Cell** sudokuWithHints) {
	currentSudoku = sudokuWithHints;
}

void freeSudoku(Cell** sudoku) {
	int i, j;
	if (sudoku != NULL) {
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				free(sudoku[i*width + j]);
			}
		}
		free(sudoku);
	}
}

void playGame() {
	char* command;
	while (true) {
		command = getCommand();
		doCommand(command);
	}
}