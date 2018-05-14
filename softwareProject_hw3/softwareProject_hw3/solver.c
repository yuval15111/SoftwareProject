#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include"game.h"
#define height 9
#define width 9
#define rangeOfNum blockHeight*blockWidth
int row = 0, col = 0;

Cell** generateSudoku() { /*should get the hints number*/
	Cell** sudoku = (Cell**)malloc(sizeof(Cell*)*height*width);
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			sudoku[i* width + j] = createCell(0);
		}
	}
	return sudoku;
}

/*returns true if the row is valid with num*/
bool isRowValid(Cell** sudoku, int num) {
	int j = 0;
	for (j = 0; j < width; j++) {
		if (sudoku[(row)*width + j]->value == num) {
			return false;
		}
	}
	return true;
}
bool isColValid(Cell** sudoku, int num) {
	int i;
	for (i = 0; i < height; i++) {
		if (sudoku[i*width + col]->value == num) {
			return false;
		}
	}
	return true;
}

bool isBlockValid(Cell** sudoku, int startRow, int startCol, int num) {/*should check the block[1] and block[0]!!!!!!!!!!!*/
	int i, j;
	for (i = 0; i < blockHeight; i++) {
		for (j = 0; j < blockWidth; j++) {
			if (sudoku[(i + startRow)*width + j + startCol]->value == num) {
				return false;
			}
		}
	}
	return true;
}

/*retuns true if its safe to insert num as the value of he current cell*/
bool isValidNum(Cell** sudoku, int num) {
	bool rowValid, colValid, blockValid;
	rowValid = isRowValid(sudoku, num);
	colValid = isColValid(sudoku, num);
	blockValid = isBlockValid(sudoku, row - row % blockWidth, col - col % blockHeight, num);
	if (rowValid && colValid && blockValid) {
		return true;
	}
	return false;
}

/*returns true if theres an empty cell and changes the row,col*/
bool findNextEmptyCell(Cell** sudoku) {
	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			if (sudoku[row*width + col]->empty == 0 && sudoku[row*width + col]->fixed == 0) { //enter to the cell using pointers add check to fixed
				return true;
			}
		}
	}
	return false;
}

void stepBack() {
	col--;
	if (col < 0) {
		col = width - 1;
		row--;
	}
}

bool detBacktrackRec(Cell** sudoku) {
	int num;
	if (!findNextEmptyCell(sudoku)) { /*if there is an empty cell-changes the row&col and returns true. otherwise returns false*/
		return true;
	}
	for (num = 1; num <= blockHeight * blockWidth; num++) { /*checks for every posible number:*/
		if (isValidNum(sudoku, num)) { /*if it's safe to put this num in this cell.*/
			sudoku[row*width + col]->value = num;
			sudoku[row*width + col]->empty = 1;
			if (detBacktrackRec(sudoku)) { /*if theres a solution*/
				return true;
			}
			sudoku[(row)*width + col]->value = 0; /*theres no solution with this num*/
			sudoku[row*width + col]->empty = 0;
		}
	}
	stepBack();
	return false; /*theres no solution at all*/
}

Cell** determenisticBacktrack(Cell** currentSudoku) {
	int i = 0, j;
	bool flag = false;
	Cell** copySudoku = (Cell**)malloc(height*width * sizeof(Cell));
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			copySudoku[i* width + j] = copyCell(currentSudoku[i* width + j]);
			if (currentSudoku[i*width + j]->empty != 0) {
				copySudoku[i*width + j]->fixed = 1;
			}
		}
	}
	flag = detBacktrackRec(copySudoku);
	if (flag) {
		freeSudoku(currentSudoku); /*free the previous sudoku beacuse now we will work on copy sudoku*/
		return copySudoku;
	}
	else return NULL;
}

void updateArrayForCell(Cell** boardGeneration) { /*return the length of the array for specific cell*/
	int i;
	for (i = 1; i <= blockHeight * blockWidth; i++) {
		boardGeneration[row*width + col]->arr[i] = 0;
		if (isValidNum(boardGeneration, i)) {
			boardGeneration[row*width + col]->arr[i] = 1;/*insert the valid numbers to the cell's array*/
			boardGeneration[row*width + col]->arr[0] ++;
		}
	}
}

int chooseRandomNumberToRemove(int* arrayOfNumbers) {/*return the index that we should remove*/
	return (rand() % arrayOfNumbers[0]);
}

void removeNumberFromArray(Cell** board, int rand) {/*find the number, remove, sort and change the length*/
	int temp = rand + 1;
	int i;
	for (i = 1; i <= blockHeight * blockWidth; i++) {
		if ((board[row*width + col]->arr[i]) == 1) {
			temp--;
			if (temp <= 0) {
				board[row*width + col]->value = i;
				board[row*width + col]->empty = 1;
				board[row*width + col]->arr[i] = 0;
				board[row*width + col]->arr[0]--;
				break;
			}
		}
	}
}

int findIndexToRemove(int* arr) {/*find index and update the len=0*/
	int i;
	for (i = 1; i <= blockHeight * blockWidth; i++) {
		if (arr[i] == 1) {
			break;
		}
	}
	arr[0] = 0;
	arr[i] = 0;
	return i;
}

bool randomBacktrack(Cell** boardGeneration) {
	if (!findNextEmptyCell(boardGeneration)) { /*if there is an empty cell-changes the row&col and returns true. otherwise returns false*/
		return true;
	}
	updateArrayForCell(boardGeneration);
	while (boardGeneration[row*width + col]->arr[0] == 0) {
		boardGeneration[row*width + col]->value = 0;
		boardGeneration[row*width + col]->empty = 0;
		stepBack();
	}
	if (boardGeneration[row*width + col]->arr[0] == 1) {
		boardGeneration[row*width + col]->value = findIndexToRemove(boardGeneration[row*width + col]->arr);
		boardGeneration[row*width + col]->empty = 1;
		if (randomBacktrack(boardGeneration)) {
			return true;
		}
	}
	if (boardGeneration[row*width + col]->arr[0] > 1) {
		removeNumberFromArray(boardGeneration, chooseRandomNumberToRemove(boardGeneration[row*width + col]->arr));
		if (randomBacktrack(boardGeneration)) {
			return true;
		}
	}
	return false;
}

void puzzleGeneration(int hints) { /*should get number of hints !!!!!!!!!!!!!! and return void* !!!*/
						  /*create 2 empty boards*/
	Cell** boardGeneration = generateSudoku();
	Cell** sudokoWithHints = generateSudoku();
	randomBacktrack(boardGeneration);
	getSolvedSudoku(boardGeneration);
	getHintsBoard(hints, boardGeneration, sudokoWithHints);
	getSudokuWithHints(sudokoWithHints);
	printSudoku(sudokoWithHints);
	/*use randomized backtracking algo to get a solved one and put it to 1 of the empty that created here
	getHintsBoard(hints); should get also the solved board and the other empty board*/
}

void getHintsBoard(int hints, Cell** solvedSudoku, Cell** sudokoWithHints) {
	int i, row, col;
	for (i = 0; i < hints; i++) {
		row = rand() % rangeOfNum;
		col = rand() % rangeOfNum;
		while (sudokoWithHints[row*width + col]->fixed == 1) {
			row = rand() % rangeOfNum;
			col = rand() % rangeOfNum;
		}
		sudokoWithHints[row*width + col]->fixed = 1;
		sudokoWithHints[row*width + col]->empty = 1;
		sudokoWithHints[row*width + col]->value = solvedSudoku[row*width + col]->value;
	}
}


