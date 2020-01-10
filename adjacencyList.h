#ifndef __ADJACENCY_LIST_H
#define __ADJACENCY_LIST_H
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
typedef struct list* List;
typedef struct lexerList* LexerList;

struct list
{
	int sz;
	Node first;
	Node last;
};

struct lexerList
{
	int sz;
	NodeLexer first;
	NodeLexer last;
};




List createNewList();
void addToList(List l,int data,int index);
void displayList(List l);


LexerList createNewLexerList();
void addToLexerList(LexerList l,int tokenId,int lineno,char x[100],int scope,int scopeCnt,int type,int xval,int yval);
void displayLexerList(LexerList l);

#endif