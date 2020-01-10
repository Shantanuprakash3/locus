#ifndef __NODE_H
#define __NODE_H
#include <stdlib.h>
#include <stdio.h>
typedef struct node* Node;
typedef struct nodeLexer* NodeLexer;
struct node
{
	int data;
	int index;
	Node next;	
};

struct nodeLexer
{
	int tokenId;
	int lineNo;
	char lexeme[100];
	int scope;
	int scopeCnt;
	int type;
	int xval;
	int yval;
	NodeLexer next;
};

Node createNewNode(int data,int index);
void displayNode(Node n);

NodeLexer createNewLexerNode(int tokenId,int lineno,char x[100],int scope,int scopeCnt,int type,int xval,int yval);
void displayLexerNode(NodeLexer n);
#endif