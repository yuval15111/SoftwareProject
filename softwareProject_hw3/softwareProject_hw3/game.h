
#ifndef GAME_H_
#define GAME_H_
#include<stdbool.h>
#define blockHeight 3
#define blockWidth 3
typedef struct cell_t {
	int value;
	int fixed; /*0 meaning not used*/
	int empty;
	int arr[(blockWidth*blockHeight) + 1];
}Cell;
Cell* createCell(int value);
Cell* copyCell(Cell* cell);

bool isRowValidGame(Cell** sudoku, int row, int num);
bool isColValidGame(Cell** sudoku, int col, int num);
bool isBlockValidGame(Cell** sudoku, int startRow, int startCol, int num);
void validate(Cell** sudoku);
void hint(int row, int col);
bool isGameOver(Cell** sudoku);
void set(Cell** sudoku, int row, int col, int val);
void printSudoku(Cell** sudoku);
void getSolvedSudoku(Cell** boardGeneration);
void getHintsBoard(int hints, Cell** solvedSudoku, Cell** sudokoWithHints);
void doCommand(char* command);
void freeSudoku(Cell** sudoku);
void exitGame();
void playGame();
void restart();

#endif /*GAME_H_*/

