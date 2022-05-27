//
// Created by sbeve72 on 02/04/22.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "utils.h"

// get a line of text of upto lim characters from the console
int getln(char *s, int lim) {
	int i, c;
	
	for (i = 0; (i != 0 || i < lim - 1) && (c = getchar()) != EOF && c != '\n'; i++) {
		s[i] = c;
	}
	
	s[i] = '\0';
	
	return i;
}

// raise base to the power of exp
int power(int base, int exp) {
	int power = 1;
	
	for (int i = 1; i <= exp; i++) {
		power *= base;
	}
	
	return power;
}

// verify and convert a string into an integer
int vatof(char *c, float *nump) {
	int sindex = (int) strlen(c), decimal = 1;
	
	*nump = 0;
	
	while (isspace(*c)) {
		c++;
	}
	
	while (sindex--) {
		if (isdigit(*c)) {
			*nump = *nump * 10 + (*c - '0');
		} else if (*c == '.') {
			decimal = (int) power(10, sindex);
		} else {
			return 0;
		}
		c++;
	}
	
	*nump /= decimal;
	
	return 1;
}

int validateoperand(const char *operand) {
	if (*operand == '>' && *(operand + 1) == '>' && *(operand + 2) == '\0') {
		return BITSHIFT_RIGHT;
	} else if (*operand == '<' && *(operand + 1) == '<' && *(operand + 2) == '\0') {
		return BITSHIFT_LEFT;
	} else if (*operand == '+' && *(operand + 1) == '\0') {
		return ADD;
	} else if (*operand == '-' && *(operand + 1) == '\0') {
		return SUBTRACT;
	} else if (*operand == '/' && *(operand + 1) == '\0') {
		return DIVIDE;
	} else if (*operand == '*' && *(operand + 1) == '\0') {
		return MULTIPLY;
	} else if (*operand == '%' && *(operand + 1) == '\0') {
		return MODULUS;
	} else if (*operand == '^' && *(operand + 1) == '\0') {
		return EXPONENT;
	}
	
	return 0;
}


char *getoperandfromtype(int type) {
	char *operand = malloc(sizeof(char) * 3);
	
	switch (type) {
		case 1:
			strcpy(operand, ">>");
			break;
		case 2:
			strcpy(operand, "<<");
			break;
		case 3:
			strcpy(operand, "+");
			break;
		case 4:
			strcpy(operand, "-");
			break;
		case 5:
			strcpy(operand, "/");
			break;
		case 6:
			strcpy(operand, "*");
			break;
		case 7:
			strcpy(operand, "%");
			break;
		case 8:
			strcpy(operand, "^");
			break;
	}
	
	return operand;
}

// convert a string of binary to decimal
int todecimal(const char *binaryrep) {
	int num;
	
	num = 0;
	
	for (int i = 0; binaryrep[i] != '\0'; i++) {
		num = num * 2 + binaryrep[i] - '0';
	}
	
	return num;
}

// find the number of bits required to fit in a number
int bitlength(unsigned int x) {
	int length = 0;
	
	if (x == 0) return 1;
	
	while (x > 0) {
		x >>= 1;
		length++;
	}
	
	return length;
}

// convert an integer to a string of binary
char *tobinary(int x) {
	int length, counter;
	char *birep;
	
	length = bitlength(x) + 1;
	counter = length - 2;
	birep = malloc(length);
	
	while (counter >= 0) {
		birep[counter] = '0' + (x & 01);
		x >>= 1;
		counter--;
	}
	
	birep[length - 1] = '\0';
	
	return birep;
}

// split a string by spaces
int spacesplit(const char *s, char **slist) {
	char *scpy = malloc(sizeof(char) * strlen(s));
	int elementcount = 0;
	
	/* make a copy of s*/
	strcpy(scpy, s);
	
	
	/* skip leading spaces */
	while (isspace(*scpy)) {
		scpy++;
	}
	
	if (*scpy != 0) {
		/* make the first element of slist point to the first word of s */
		slist[elementcount] = scpy;
		/* increase word count by 1 (the first element has been initiated) */
		elementcount++;
	}
	
	while (*scpy) {
		/* when space is found, replace the space character with a 0
		 * add the pointer to the next non-space character to slist[elementcount]
		 * increase element count, another element has been created */
		if (isspace(*scpy)) {
			*scpy = '\0';
			slist[elementcount] = scpy + 1;
			elementcount++;
		}
		
		/* if it is a non-space character, continue moving forward*/
		scpy++;
		
	}
	
	return elementcount;
}
