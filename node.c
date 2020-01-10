/*
Team no : 51
ID :   2012C6PS650P      2012C6PS696P
Name : Vivek Kishore   Shantanu Prakash 
*/

#include "node.h"
Node createNewNode(int data,int index)
{	
	Node n=(Node)malloc(sizeof(struct node));
	n->next=NULL;
	n->index = index;
	n->data=data;
	return n;
}



void displayNode(Node n)
{
	printf("%d ",n->data);
}


NodeLexer createNewLexerNode(int tokenId,int lineno,char x[100],int scope,int scopeCnt,int type,int xval,int yval)
{	
	NodeLexer n=(NodeLexer)malloc(sizeof(struct nodeLexer));
	n->next=NULL;
	n->tokenId = tokenId;
	n->lineNo=lineno;
    n->scope = scope;
    n->scopeCnt = scopeCnt;
    n->type = type;
    n->xval = xval;
    n->yval = yval;

	int i;
	for (i = 0; i < 100; ++i)
	{
		n->lexeme[i] = x[i];
	}	
	return n;
}

void displayLexerNode(NodeLexer n)
{
	printf("%d %d",n->tokenId,n->lineNo);
}