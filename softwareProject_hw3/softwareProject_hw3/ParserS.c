#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "game.h"

int initNumberOfHints() {
	char hints[20];
	int flag = 1;
	int convertHintsToInt = -1;
	while (flag) {
		printf("Please enter the number of cells to fill [0-80]:\n");
		if (fgets(hints, 1024, stdin) == NULL) {
			exitGame();
		}
		convertHintsToInt = atoi(hints);
		if (hints[0] == '0') {
			return 0;
		}
		if (convertHintsToInt > 80 || convertHintsToInt <= 0) {
			printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
		}
		else flag = 0;
	}
	return convertHintsToInt;
}

char* getCommand() { /*should call to this func in while or to do all this func in while true - exit only if exit command.
					 values[0]=: 1->set, 2->hint, 3->validate, 4->restart, 5->exit*/
	char command[1024];
	int check;
	int j = 1;
	char* newType;
	char* values = (char*)malloc(sizeof(char) * 4);
	if (values == NULL) {
		printf("Error: getCommand has failed\n");
		exit(0);
	}
	memset(values, '\0', 3);
	if (fgets(command, 1024, stdin) == NULL) {
		exitGame();
	}
	newType = strtok(command, " \t\r\n");
	if ((check = strcmp(newType, "set")) == 0) {
		while (newType != NULL && j<4) {
			newType = strtok(NULL, " \t\r\n");
			values[j] = *newType;
			j++;
		}
		values[0] = '1';
	}
	else if ((check = strcmp(newType, "hint")) == 0) {
		while (newType != NULL && j < 3) {
			newType = strtok(NULL, " \t\r\n");
			values[j] = *newType;
			j++;
		}
		values[0] = '2';
	}
	else if ((check = strcmp(newType, "validate")) == 0) {
		values[0] = '3';
	}
	else if ((check = strcmp(newType, "restart")) == 0) {
		values[0] = '4';
	}
	else if ((check = strcmp(newType, "exit")) == 0) {
		values[0] = '5';
	}
	else printf("Error: invalid command\n");
	return values;
}





