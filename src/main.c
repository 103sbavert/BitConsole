#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

const int MAX_EXP_LEN = 100;
const int QUIT_COMMAND = 100;
const int CLEAR_COMMAND = 200;
const int UNKNOWN_COMMAND = 300;
const int VALID_EXP = 400;
const int INVALID_EXP = 500;

float a = 0;
float b = 0;
int optype = 0;

int main() {
	void displayoperation();
	void showguidelines();
	int getexptype(char *exp);
	
	char *exp = malloc(sizeof(char) * MAX_EXP_LEN);
	int commandcode;
	
	while (true) {
		showguidelines();
		getln(exp, MAX_EXP_LEN);
		commandcode = getexptype(exp);
		
		switch (commandcode) {
			case 100:
				goto free;
			case 200:
				system("clear");
				break;
			case 300:
				printf("Error: unknown command \"%s\"", exp);
				break;
			case 400:
				displayoperation();
				break;
			case 500:
				printf("Error: illegal expression \"%s\"", exp);
				break;
			default:
				printf("An unknown error occurred");
				goto free;
		}
	}
	
	free:
	free(exp);
}

void displayoperation() {
	printf(" %s\n", tobinary(a));
	printf(" %s\n", tobinary(b));
	printf("%s", getoperandfromtype(optype));
}

void showguidelines() {
	printf("\nEnter a mathematical expression to show an illustration of how the operations work under the hood\n");
	printf("You can enter an expression upto 100 characters. Please, do not exceed this limit.\n>>> ");
}

int getexptype(char *exp) {
	char **explist = malloc(sizeof(char *) * 3);
	int code = INVALID_EXP;
	
	if (*exp == ':') {
		printf("at 1");
		switch (*(exp + 1)) {
			case 'q':
				code = QUIT_COMMAND;
				break;
			case 'c':
				code = CLEAR_COMMAND;
				break;
			default:
				code = UNKNOWN_COMMAND;
				break;
		}
	} else {
		int explistsize;
		printf("At 2");
		
		explistsize = spacesplit(exp, explist);
		
		if (explistsize == 3) {
			int isavalid = vatof(explist[0], &a);
			int isbvalid = vatof(explist[2], &b);
			optype = validateoperand(explist[1]);
			
			if (!(isavalid && isbvalid && optype)) {
				code = INVALID_EXP;
			} else {
				code = VALID_EXP;
			}
		}
	}
	
	free(*explist);
	free(explist);
	

	return code;

}
