#ifndef PARSERS_H_
#define PARSERS_H_

/*This function get from the user the number of hints that he wants to start with in his sudoku game
and interpret this number.
@return
the number of hints - should be between 1 to 80
*/
int initNumberOfHints();

/**This function get the command that the user write in the command line and interpret 
to one of our possibles command:
1->set, 2->hint, 3->validate, 4->restart, 5->exit
@return
values - array of chars that:
values[0]=: 1->set, 2->hint, 3->validate, 4->restart, 5->exit
If its set or hint command the values of the row, col and the number will be in the array
*/
char* getCommand();

#endif /*PARSERS_H_*/
