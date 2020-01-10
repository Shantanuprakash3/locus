/*
Team no : 51
ID :   2012C6PS650P      2012C6PS696P
Name : Vivek Kishore   Shantanu Prakash 
*/

#include "adjacencyList.h"

List createNewList()
{
	List l=(List)malloc(sizeof(struct list));
	l->sz=0;
	l->first=NULL;
	l->last=NULL;
	return l;
}

void addToList(List l,int data,int index)
{
	Node n=createNewNode(data,index);
	
	if(l->first==NULL)
		{
			l->first=n;
			l->last=n;
		}
	else
		{
			l->last->next=n;
			l->last=n;
		}
	++(l->sz);
}
void displayList(List l)
{	
	if(l->first==NULL)
		printf("List is empty\n");
	
	else
	{
		Node curr=l->first;
		while(curr!=NULL)
				{
					displayNode(curr);
					curr=curr->next;
				}
		if(curr==NULL)
			printf("\n");
	}


}

void deleteNode(List l, int key)
{

	Node temp = l->first;

    // Node temp = head;
    Node prev;
 
    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key)
    {
        l->first = temp->next;
           // Changed head
        
        free(temp);               // free old head
        l->sz--;
        return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }
 
    // If key was not present in linked list
    if (temp == NULL) return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
    l->sz--;

 
    free(temp);  // Free memory
}


LexerList createNewLexerList()
{
	LexerList l=(LexerList)malloc(sizeof(struct lexerList));
	l->sz=0;
	l->first=NULL;
	l->last=NULL;
	return l;
}

void addToLexerList(LexerList l,int tokenId,int lineno,char x[100],int scope,int scopeCnt,int type,int xval,int yval)
{
	NodeLexer n=createNewLexerNode(tokenId,lineno,x, scope, scopeCnt, type,xval,yval);
	
	if(l->first==NULL)
		{
			l->first=n;
			l->last=n;
		}
	else
		{
			l->last->next=n;
			l->last=n;
		}
	++(l->sz);
}
void displayLexerList(LexerList l)
{	
	if(l->first==NULL)
		printf("LexerList is empty\n");
	
	else
	{
		NodeLexer curr=l->first;
		while(curr!=NULL)
				{
					displayLexerNode(curr);
					curr=curr->next;
				}
		if(curr==NULL)
			printf("\n");
	}


}