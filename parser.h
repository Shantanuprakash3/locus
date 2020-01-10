#ifndef PARSER_H
#define PARSER_H
#include "adjacencyList.h"
#include <assert.h>

extern int code[10000];
extern int codeLineNo[10000];
extern int TID;
extern int TID2;



extern List tree[10000];
extern List astTree[10000];
extern int tokenType[10000];
extern int tokenTypeAST[10000];
extern int parse[1000][1000];
extern int rule[1000][1000];
extern LexerList bigTree[10000];



void initializeParseTable();
void initializeRuleTable();





#endif