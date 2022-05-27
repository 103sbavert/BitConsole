#ifndef BITCONSOLE_UTILS_H
#define BITCONSOLE_UTILS_H

#include <stdbool.h>

#define BITSHIFT_RIGHT 1;
#define BITSHIFT_LEFT 2;
#define ADD 3;
#define SUBTRACT 4;
#define DIVIDE 5;
#define MULTIPLY 6;
#define MODULUS 7;
#define EXPONENT 8;

int getln(char *, int);

int spacesplit(const char *, char **);

int todecimal(const char *);

char *tobinary(int);

int vatof(char *, float *);

int validateoperand(const char *);

char *getoperandfromtype(int);

#endif //BITCONSOLE_UTILS_H
