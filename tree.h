#ifndef TREE_H
#define TREE_H
#include "parser.h"
#include "adjacencyList.h"
#include "node.h"

typedef struct treenode* TNode;

void displayParseTree();
void displayASTTree();
void displaySymbolTable();
void makeSymbolTable();
int findType(NodeLexer x);
int charMatch(char c1[],char c2[]);
void displayBigParseTree();
int checkNum1(NodeLexer x);
int funcCheck();


void generateCode();
void initiateArrays();
void funcAssignment(int start,int e);
int findReg(int x);
int findIndexVariable(char a[]);
void populateVariables();

void funcIteration(int start,int end);
void funcConditional(int start,int end);

void funcAssign(int start,int end);








void reduceLinearChains(int index,int parent);
void transform();

extern NodeLexer sTable[100];
extern LexerList sTableList;



#endif