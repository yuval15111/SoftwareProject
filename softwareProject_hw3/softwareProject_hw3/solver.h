
#ifndef SOLVER_H_
#define SOLVER_H_
#include<stdbool.h>
#define height 9
#define width 9

Cell** generateSudoku();
bool isRowValid(Cell** sudoku, int num);
bool isColValid(Cell** sudoku, int num);
bool isBlockValid(Cell** sudoku, int startRow, int startCol, int num);
bool isValidNum(Cell** sudoku, int num);
bool findNextEmptyCell(Cell** sudoku);
void stepBack();
bool detBacktrackRec(Cell** sudoku);
Cell** determenisticBacktrack(Cell** sudoku);
void updateArrayForCell(Cell** boardGeneration);
int chooseRandomNumberToRemove(int* arrayOfNumbers);
void removeNumberFromArray(Cell** board, int rand);
int findIndexToRemove(int* arr);
bool randomBacktrack(Cell** boardGeneration);
void puzzleGeneration(int hints);
void getHintsBoard(int hints, Cell** solvedSudoku, Cell** sudokoWithHints);

#endif /*SOLVER_H_*/

