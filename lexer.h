#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjacencyList.h"

extern LexerList codeTokens;

struct tokenInfo
{
int lineno;
char lexeme[300];
int tokenID;
};



void lexerFunc();
int isNumeric(char c);
int isLetter(char c);
char nextValid(int index);

#endif
