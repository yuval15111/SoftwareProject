#include<stdio.h>
#include<string.h>
#include<math.h>

int dopow(int base, int num) {
	int sum = 1;
	int i = 0;
	for (i = 0; i < num; i++) {
		sum *= base;
	}
	return sum;
}
int ToDec(char *numInA, int baseA, int numL) {
	int i, NumDec = 0;
	for (i = numL - 1; i >= 0; i--) {
		if ((int)numInA[i] >= 48 && (int)numInA[i] <= 57) {

			NumDec += ((int)numInA[i] - 48) * (dopow(baseA, numL - i - 1));
		}
		else {
			NumDec += ((int)numInA[i] - 55) * (dopow(baseA, numL - i - 1));
		}
	}
	return NumDec;
}
int ToNewBase(int numDec, int toBaseB, char* numInA) {
	int remainder, i = 0;
	while (numDec > 0) {
		remainder = numDec % toBaseB;
		if (remainder > 9) {
			numInA[i] = 'A' + remainder - 10;
		}
		else {
			numInA[i] = '0' + remainder;
		}
		i++;
		numDec = numDec / toBaseB;
	}
	return i;
}
void reverse(char* numInA, int len, char* numInB) {
	int i = 0;
	for (i = 0; i < len / 2; i++) {
		numInB[i] = numInA[len - 1 - i];
		numInB[len - 1 - i] = numInA[i];
	}
	if (len % 2 != 0) {
		numInB[len / 2] = numInA[len / 2];
	}
}
void printArray(char* numInB, int len) {
	int i = 0;
	printf("The result is: ");
	for (i = 0; i < len; i++) {
		printf("%c", numInB[i]);
	}
	printf("\n");
}
int getinput(char* numInA, int baseA, char* range) {
	int i = 0, j = 0;
	int check = baseA;
	int flag = 0;
	char c;
	printf("Please enter a number in base %d:\n", baseA);
	if ((c = getchar()) != '\n') {
		printf("Invalid number!\n");
		return 0;
	}
	while ((c = getchar()) != EOF && c != '\n' && c != '\t' && c != ' ' && c != '\v') {
		for (j = 0; j < 17; j++) {
			if (c == range[j]) {
				numInA[i] = range[j];
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("Invalid number!\n");
			return 0;
		}
		flag = 0;
		if (baseA >= 2 && baseA <= 9) {
			check = baseA + 48;
		}
		else {
			check = baseA + 55;
		}
		if (c >= check) {
			printf("Invalid number!\n");
			return 0;
		}
		i++;
	}
	return i;
}
int main() {
	int baseB, numL = 0;
	int baseA;
	int NumInDec, lenB;
	char numInA[1024];
	char numInB[1024];
	char range[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	printf("Please enter the number's base:\n");
	if (scanf("%d", &baseA) != 1) {
		printf("An error occurred!\n");
		return 0;
	}
	if (baseA < 2 || baseA > 16) {
		printf("Invalid input base\n");
		return 0;
	}
	printf("Please enter the desired base:\n");
	if (scanf("%d", &baseB) != 1) {
		printf("An error occurred!\n");
		return 0;
	}
	if (baseB < 2 || baseB > 16) {
		printf("Invalid desired base\n");
		return 0;
	}
	numL = getinput(numInA, baseA, range);
	if (numL == 0) {
		return 0;
	}
	NumInDec = ToDec(numInA, baseA, numL);
	lenB = ToNewBase(NumInDec, baseB, numInA);
	reverse(numInA, lenB, numInB);
	printArray(numInB, lenB);
	return 0;
}