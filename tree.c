/*
Team no : 51
ID :   2012C6PS650P      2012C6PS696P
Name : Vivek Kishore   Shantanu Prakash 
*/

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "adjacencyList.h"
#include "lexer.h"

int maxID = 100; //needs to be updated

NodeLexer sTable[100];
LexerList sTableList;


char* terminal1[] = {	
	"tk_build",
	"tk_func_id",
	"tk_lb",
	"tk_rb",
	"tk_begin",
	"tk_end",
	"tk_void",
	"tk_main",
	"tk_int",
	"tk_float",
	"tk_string",
	"tk_return",
	"tk_sc",
	"tk_arith_id",
	"tk_define",
	"tk_id",
	"tk_point",
	"tk_ob",
	"tk_integer_literal",
	"tk_cb",
	"tk_polygon",
	"tk_com",
	"tk_comment",
	"tk_equal",
	"tk_plus",
	"tk_minus",
	"tk_dist",
	"tk_nn",
	"tk_opencurl",
	"tk_closecurl",
	"tk_while",
	"tk_if",
	"tk_else",
	"tk_G",
	"tk_EQ",
	"tk_LT",
	"tk_LE",
	"tk_GE",
	"E",
	"$"
};

char* nonTerminal1[]= {"program","functions","function","func_sign","func_body",
"main_function","main_signature","main_func_body","func_type","return_statements","XX",
"void_return","declarations","type","point_type","polygon_type","func",
"args","calling_args","statements","func_call","assign","expr","num1",
"op1","point_literal","point_arr","iteration","selection","else_selection","cond_exp","op2"
};


int arr[10];
int arr1[10];


void makeBigAST(int index,int parent)
{
	List x = tree[index];
	if(x->first==NULL)
		{


		}	
	else
	{
		Node curr=x->first;
		while(curr!=NULL)
			{
				// displayNode(curr);
				reduceLinearChains(curr->data,index);
				curr=curr->next;
			}
		// if(curr==NULL)
			// printf("\n");
	}
	if(x->sz==1)
	{

		int child = x->first->data;
		tree[index]->first = tree[child]->first;
		tokenTypeAST[index] = tokenTypeAST[child];
		tree[child]->first=NULL;
	}
}



void displayBigParseTree()
{

	printf("\n----------------------------------------------\n");
	printf("Adjacency List of Big Parse Tree :- \n\n");
	printf("Parent            ->              Children \n\n");
	int i,j;
	int k=0;
	for ( i = 0; i < TID2; ++i)
	{
		LexerList x = bigTree[i];
		if(x->first==NULL)
		{

		}	
		else
		{
			printf("%d -> ",i);
			NodeLexer curr = x->first;
			while(curr!=NULL)
			{
				printf(" %d-%d",curr->tokenId,curr->yval);
				curr = curr->next;	

			}
			printf("\n");

		}

	}


}



void displayParseTree()
{

	printf("\n----------------------------------------------\n");
	printf("Adjacency List of Parse Tree :- \n\n");
	printf("Parent            ->              Children \n\n");
	int i,j;
	int k=0;
	for ( i = 0; i < TID; ++i)
	{
		List x = tree[i];
		
		if(x->first==NULL)
		{
		}	
		else
		{
		int temp2 = tokenType[i];
			printf("%d ->",temp2);

			k=0;

			arr[0]=temp2;
			arr1[0]=-1;
			k++;


		Node curr=x->first;
		while(curr!=NULL)
			{
				// displayNode(curr);
				int temp = tokenType[curr->data];
				int temp3 = curr->index;
				if(temp>=1000)
					{
						// printf("%d ",temp);
						arr[k]=temp;

						// temp=temp-1000;
						// if(temp>3)
						// printf("%s ",nonTerminal1[temp-1]);
						// else
						// printf("%s ",nonTerminal1[temp]);
					}
				else
				{	
					arr[k]=temp;
					// printf("%d ",temp);
				}
				arr1[k]=temp3;
				k++;
					// printf("%s ",terminal1[temp]);


				curr=curr->next;
			}
			k--;
			for (j = k; j >0; --j)
			{
				printf("%d-%d  ",arr[j],arr1[j]);
				/* code */
			}

			printf("\n");

	}

		/* code */
	}


}



void pruningParseTree()
{
	int i,j;
	int k=0;
	for ( i = 0; i < TID; ++i)
	{
		List x = tree[i];
		
		if(x->first==NULL)
		{
		}	
		else
		{
		Node curr=x->first;
		while(curr!=NULL)
			{
				int temp = tokenType[curr->data];
				List yo = tree[curr->data];
				if(yo->sz==0 && temp>=1000)
					deleteNode(tree[i],curr->data);

				if(temp==4 || temp==5 || temp==12 || temp==2 || temp==3 || temp == 16 || temp==18 || temp==20 || temp==27 || temp==27 )
				{
					deleteNode(tree[i],curr->data);
				}	
				curr=curr->next;
			}
			k--;
		}
	}



}


void reduceLinearChains(int index,int parent)
{
	List x = tree[index];
	if(x->first==NULL)
		{
			// printf("ggg\n")
		}	
	else
	{
		Node curr=x->first;
		while(curr!=NULL)
			{
				// displayNode(curr);
				reduceLinearChains(curr->data,index);
				curr=curr->next;
			}
		// if(curr==NULL)
			// printf("\n");
	}
	if(x->sz==1)
	{

		int child = x->first->data;
		tree[index]->first = tree[child]->first;
		tokenTypeAST[index] = tokenTypeAST[child];
		tree[child]->first=NULL;
	}
}








void displayASTTree()
{

	printf("\n----------------------------------------------\n");
	printf("Adjacency List of AST Tree :- \n\n");
	printf("Parent            ->              Children \n\n");
	int i,j;
	int k=0;
	for ( i = 0; i < TID; ++i)
	{
		List x = tree[i];
		
		if(x->first==NULL)
		{
		}	
		else
		{
		int temp2 = tokenTypeAST[i];
			printf("%d ->",temp2);

			k=0;

			arr[0]=temp2;
			arr1[0]=-1;
			k++;

			// if(temp2>3)
			// 	printf("Node no.%d %s -> ",i,nonTerminal1[temp2-1001]);
			// else
			// 	printf("Node no.%d %s ->",i,nonTerminal1[temp2-1000]);

		Node curr=x->first;
		while(curr!=NULL)
			{
				// displayNode(curr);
				int temp = tokenTypeAST[curr->data];
				int temp3 = curr->index;
				if(temp>=1000)
					{
						// printf("%d ",temp);
						arr[k]=temp;
						// temp=temp-1000;
						// if(temp>3)
						// printf("%s ",nonTerminal1[temp-1]);
						// else
						// printf("%s ",nonTerminal1[temp]);
					}
				else
				{	
					arr[k]=temp;
					// printf("%d ",temp);
				}
				arr1[k]=temp3;
				k++;
					// printf("%s ",terminal1[temp]);


				curr=curr->next;
			}
			k--;
			for (j = k; j >0; --j)
			{
				if(arr1[j]!=-1)
				printf("%d-%d ",arr[j],arr1[j]);
				else
				printf("%d ",arr[j]);

				/* code */
			}

			printf("\n");
		// if(curr==NULL)
			// printf("\n");
	}

		/* code */
	}


}


void makeSymbolTable()
{
	sTableList = createNewLexerList();
	NodeLexer tempNode;

	if(codeTokens->first!=NULL)
	{
		NodeLexer curr = codeTokens->first;
		while(curr!=NULL)
		{
			if(curr->next!=NULL)
			{
			if(curr->next->next!=NULL && curr->tokenId==14)
			{
				if(curr->next->tokenId==8)
				{
					curr->next->next->type = 0; //integer
					tempNode = curr->next->next;


					if(tempNode->tokenId==13)
						addToLexerList(sTableList,tempNode->tokenId,tempNode->lineNo,tempNode->lexeme,tempNode->scope,tempNode->scopeCnt,0,0,0);

				}

				if(curr->next->next->next!=NULL && curr->next->tokenId==15)
				{
					if(curr->next->next->next->next!=NULL)
					{
						if(curr->next->next->next->next->next!=NULL)
					{
						curr->next->next->next->next->next->type = 1; //point
						tempNode = curr->next->next->next->next->next;
					if(tempNode->tokenId==13)
						addToLexerList(sTableList,tempNode->tokenId,tempNode->lineNo,tempNode->lexeme,tempNode->scope,tempNode->scopeCnt,1,tempNode->xval,tempNode->yval);

					}
					}
				}


				if(curr->next->next->next!=NULL && curr->next->tokenId==19)
				{
					if(curr->next->next->next->next!=NULL)
					{
						if(curr->next->next->next->next->next!=NULL)
						{
						if(curr->next->next->next->next->next->next!=NULL)
							{
								if(curr->next->next->next->next->next->next->next!=NULL)
								{
									if(curr->next->next->next->next->next->next->next->next!=NULL)
										{
									curr->next->next->next->next->next->next->next->next->type = 2; //polygon
										
										tempNode = curr->next->next->next->next->next->next->next->next;
							if(tempNode->tokenId==13)
							{
						
						addToLexerList(sTableList,tempNode->tokenId,tempNode->lineNo,tempNode->lexeme,tempNode->scope,tempNode->scopeCnt,2,tempNode->xval,tempNode->yval);


							}

										}

								}
							}
						}
					}
				}

				}

				}

				if(curr->tokenId==1)
			{
				addToLexerList(sTableList,curr->tokenId,curr->lineNo,curr->lexeme,curr->scope,curr->scopeCnt,curr->type,0,0);
			}
			curr=curr->next;

		}



	}



}


void displaySymbolTable()
{	


	printf("\n\nSymbol Table :- \n\n");
	int index=1;



	if(sTableList->first!=NULL)
	{
		// printf("%d\n\n",sTableList->sz);

		printf("Index  ID_Variant  Lexeme  Type   ScopeNo   LineNo\n");
		printf("----------------------------------------\n");

		NodeLexer curr = sTableList->first;
  
		while(curr!=NULL)
		{
				float scopeTemp = curr->scope+0.1*curr->scopeCnt;
				if(curr->tokenId==1)
				{
				printf("%d.     ",index++);
				printf(" func_ID  ");
				printf("   %s    ",curr->lexeme);
				printf("int    ");
				printf("    -           ");
				printf("%d      ",curr->lineNo);
				printf("\n");	
				}
				else
				{
				printf("%d.     ",index++);
				printf("    ID       ");
				printf("%s   ",curr->lexeme);
				int x=curr->type;
				if(x==0)
					printf(" int      ");
				if(x==1)
					printf(" point      ");
				if(x==2)
					printf(" polygon       ");
				printf("%.1f     ",scopeTemp);
				printf("%d      ",curr->lineNo);
				printf("%d      ",curr->xval);
				printf("%d      ",curr->yval);

				printf("\n");
				}
			curr=curr->next;
		}

	}
	else
	{
		printf("Symbol Table is empty\n");
	}



}


int charMatch(char c1[],char c2[])
{
	int n1 = 0;
	while(c1[n1]!='\0')
	{
		n1++;
	}
	int n2 = 0;
	while(c2[n2]!='\0')
	{
		n2++;
	}
	if(n1!=n2)
		return 0;
	else
	{
		int i;
		for (i = 0; i < n1; ++i)
		{
			if(c1[i]!=c2[i])
				return 0;
		}
		return 1;
	}
}

//duplicates hasnt been taken care of now



int findType(NodeLexer x)
{
	if(sTableList->first==NULL)
		return -1;
	char c[100];
	c[0] = '\0';
	if(x->tokenId == 13)
		{
			int i;
			for (i = 0; i < 50; ++i)
			{
				c[i] = x->lexeme[i];
			}
		}
	else
	{
		return x->type;			
	}
	NodeLexer curr = sTableList->first;
	while(curr!=NULL)
	{
		if(charMatch(curr->lexeme,c))
		{
			return curr->type;
		}
		curr=curr->next;
	}

	return -1;
}

int checkNum1(NodeLexer x)
{	
	if(x->tokenId==13 || x->tokenId==17 || x->tokenId==23 || x->tokenId==36)
		return 1;
	else 
		return 0;
}

	
int funcCheck()
{

	NodeLexer curr = codeTokens->first;
	int returnType;

	if(curr==NULL)
	{
		exit(0);
	}
	else
	{
		while(curr!=NULL)
		{
			// printf("%d\n",curr->tokenId);
			if(curr->tokenId== 13)
			{	
				NodeLexer temp0 = curr;
				int x1 = findType(curr);
				NodeLexer temp1 = curr->next->next;
				int type0,type1=-1,type2=-1;
				NodeLexer op1 = curr->next->next->next;
				NodeLexer temp2 = curr->next->next->next->next;

				type0 = findType(temp0);

				if(temp1->tokenId==13)
					type1 = findType(temp1);
				if(temp1->tokenId==17)
					type1 = 0;
				if(temp1->tokenId==23)
					type1 = 1;
				if(temp1->tokenId==36)
					type1 = 2;

				if(temp2->tokenId==13)
					type2 = findType(temp2);
				if(temp2->tokenId==17)
					type2 = 0;
				if(temp2->tokenId==23)
					type2 = 1;
				if(temp2->tokenId==36)
					type2 = 2;




				if(checkNum1(temp1) && checkNum1(temp2))
				{
				// printf("\n\ntypes are  :  %d %d\n\n",type1,type2);
					
					if(op1->tokenId==24)  //plus
					{
						if(type1==type2 && type1==type0 && type1==0)
						{
							// return -1;   //okay
						}
						else
						{
							printf("Type checking error at Line %d\n",temp1->lineNo);
							return 0;
						}
							// return temp1->lineNo;
					}

					if(op1->tokenId==26)  //dist
					{
						if(type1==type2 && type0==0 && type1==1)
						{
							// return -1;   //okay
						}
						else
						{
							printf("Type checking error at Line %d\n",temp1->lineNo);
							return 0;
						}
							// return temp1->lineNo;
					}

					if(op1->tokenId==27)  //nn
					{
						if(type1==1 && type0==1 && type2==2)
						{
							// return -1;   //okay
						}
						else
						{
							printf("Type checking error at Line %d\n",temp1->lineNo);
							return 0;
						}
							// return temp1->lineNo;
					}

				}

			}

			if(curr->tokenId==29 || curr->tokenId==28)
			{	

				NodeLexer temp1 = curr->next->next;
				NodeLexer temp2 = curr->next->next->next->next;

				int type1 = findType(temp1);
				if(temp1->tokenId==17)
					type1 = 0;
				int type2 = findType(temp2);
				if(temp2->tokenId==17)
					type2 = 0;
				if(type1==0 && type2==0)
				{

				}
				else
				{
							printf("Type checking error at Line %d\n",temp1->lineNo);
					return 0;
				}

			}


			if(curr->tokenId == 0)
			{
				returnType = findType(curr->next);
			}
			if(curr->tokenId == 11)
			{
				if(curr->next->tokenId==13)
				{
					int type4 = findType(curr->next);
					if(type4!=returnType)
					{
						printf("Return Type error at Line %d\n",curr->lineNo);
					return 0;

					}
				}
			}

			curr=curr->next;
		}
	}
	return 1;
}




//---------------------------------------------------------
int codeArray[1000];
char lexemeChar[1000][100];
char variables[10][100];
int variableID[10];
int visit[10];
int totalCode=0;
int lbl=0;
int variableCnt=0;
int regFlag[5];
char regist[4][10];


void populateVariables()
{
	NodeLexer curr = sTableList->first;
	int k = 0;
	while(curr!=NULL)
	{	
		if(curr->tokenId == 13 && curr->type==0)
		{
			strcpy(variables[k],curr->lexeme);
			k++; 
		}
		curr=curr->next;
	}
	variableCnt=k;
}

int findIndexVariable(char a[])
{
	int i;
	for (i = 0; i < 5; ++i)
	{
		if(strcmp(variables[i],a)==0)
			return 2000+i;
	}
	return -1;
}




int findReg(int x)
{
	if(codeArray[x]==2000)
		printf("ax");
	if(codeArray[x]==2001)
		printf("bx");
	if(codeArray[x]==2002)
		printf("cx");
	if(codeArray[x]==2003)
		printf("dx");
	if(codeArray[x]==17)
		printf("%s",lexemeChar[x]);

}
void initiateArrays()
{
	NodeLexer curr = codeTokens->first;
	int k=0;
	while(curr!=NULL)
	{
		// printf("%d\n",curr->tokenId);
		codeArray[k] = curr->tokenId;
		int temp=-1;
		strcpy(lexemeChar[k],curr->lexeme);
		if(curr->tokenId==13)
		{
			temp = findIndexVariable(curr->lexeme);
		}
		if(temp!=-1)
			codeArray[k] = temp;
		k++;
		curr=curr->next;
		totalCode++;
	}


}


int findReg1()
{
		if(regFlag[0]==0)
		{
			printf("ax");
			regFlag[0]=1;
			return 0;
		}
		if(regFlag[1]==0)
		{
			printf("bx");
			regFlag[1]=1;

			return 1;

		}
		if(regFlag[2]==0)
		{
			printf("cx");
			regFlag[2]=1;

			return 2;

		}
		if(regFlag[3]==0)
		{
			regFlag[3]=1;

			printf("dx");
			return 3;

		}


}


void funcAssign(int start,int end)
{
	int first,second,third;
	// if(visit[codeArray[start]-2000]==0)
	// {
	// 	printf("mov ");
	// 	first = findReg1();

	// 	printf(",%s\n",variables[codeArray[start]-2000]);
	// 	visit[codeArray[start]-2000]=1;
	// 	regFlag[codeArray[start]-2000]=1;
	// }	
	if(codeArray[start+2]==17)
	{
		printf("mov ");
		printf("%s,%s\n",regist[first],lexemeChar[start+2]);
		regFlag[0]=1;
	}
	else
	{
		printf("mov ");
		second = findReg1();
		printf(",%s\n",variables[codeArray[start+2]-2000]);
		printf("mov %s,%s\n",regist[first],regist[second]);
	}

	if(codeArray[start+4]==17)
	{
		printf("add ");
		printf("%s,%s\n",regist[first],lexemeChar[start+4]);
	}
	else
	{
		printf("mov ");
		third = findReg1();
		printf(",%s\n",variables[codeArray[start+4]-2000]);
		printf("add %s,%s\n",regist[first],regist[third]);


	}	


	//back to memory

	printf("lea di,%s\n",variables[codeArray[start]-2000]);
	printf("mov [di],ax\n");
	int i;
	for ( i = 0; i < 4; ++i)
	{
		regFlag[i]=0;
	}




}


void funcAssignment(int start,int end)
{
	if(visit[codeArray[start]-2000]==0)
	{
		printf("mov ");
		findReg(start);
		printf(",offset %s\n",variables[codeArray[start]-2000]);
		// variableID[t]=
		visit[codeArray[start]-2000]=1;
	}
	printf("mov ");
	findReg(start);
	if(codeArray[start+2]==17)
	{
		printf(",%s\n",lexemeChar[start+2]);
	}
	else 	
	{
		printf(",");	
		findReg(start+2);
		printf(" \n");
	}
	printf("add ");
	findReg(start);
	if(codeArray[start+4]==17)
	{		
		printf(",%s\n",lexemeChar[start+4]);
	}
	else
	{
		printf("\n");
	}

}

void printCondition(int x)
{
	if(codeArray[x]==31)
		printf("jle ");
	if(codeArray[x]==33)
		printf("jge ");
	if(codeArray[x]==34)
		printf("jg ");
	if(codeArray[x]==35)
		printf("jl ");
}

void funcConditional(int start, int end)
{
	int i;
	printf("cmp ");
	findReg(start+2);
	printf(",");
	findReg(start+4);
	printf("\n");
	printCondition(start+3);
	printf("Label%d\n",lbl);
	for (i = start+7; i < end; ++i)
	{
		if(codeArray[i]==24 || codeArray[i]==25)
		{
			funcAssign(i-3,i+2);
		}
		if(codeArray[i]== 29)
		{
			// printf("checking ... ");
			int j=0;
			int bol=0;
			int tmp=0;
			for(j=i;j<totalCode;j++)
			{
				if(codeArray[j]==4)
					bol++,tmp=1;
				if(codeArray[j]==5)
				{

					bol--;
					lbl++;
					funcConditional(i,j);
				}
				if(bol==0 && tmp==1)
					break;
			}
			i=j+1;
		}
		if(codeArray[i]==28)
		{
			// printf("ffffff\n\n");
			int j=0;
			int bol=0,tmp=0;
			for(j=i;j<totalCode;j++)
			{
				if(codeArray[j]==4)
					bol++,tmp=1;
				if(codeArray[j]==5)
				{
					bol--;
					funcIteration(i,j);
				}
				if(bol==0 && tmp==1)
					break;
			}
			i=j+1;	

		}
	}
	printf("Label%d :\n",lbl);
	lbl++;

}


void funcIteration(int start,int end)
{
	int i;

	printf("Label%d :\n",lbl);
	lbl++;
	printf("cmp ");
	findReg(start+2);
	printf(",");
	findReg(start+4);
	printf("\n");
	printCondition(start+3);
	printf("Label%d\n",lbl);
	for (i = start+7; i < end; ++i)
	{
		if(codeArray[i]==24 || codeArray[i]==25)
		{
			funcAssign(i-3,i+2);
		}
		if(codeArray[i]== 29)
		{
			// printf("checking ... ");
			int j=0;
			int bol=0;
			int tmp=0;
			for(j=i;j<totalCode;j++)
			{
				if(codeArray[j]==4)
					bol++,tmp=1;
				if(codeArray[j]==5)
				{

					bol--;
					funcConditional(i,j);
				}
				if(bol==0 && tmp==1)
					break;
			}
			i=j+1;
		}
		if(codeArray[i]==28)
		{
			// printf("ffffff\n\n");
			int j=0;
			int bol=0,tmp=0;
			for(j=i;j<totalCode;j++)
			{
				if(codeArray[j]==4)
					bol++,tmp=1;
				if(codeArray[j]==5)
				{
					bol--;
					funcIteration(i,j);
				}
				if(bol==0 && tmp==1)
					break;
			}
			i=j+1;	

		}
	}
	printf("jmp label%d\n",lbl-1);
	printf("Label%d :\n",lbl);
	lbl++;



}



void generateCode()
{
	int i;

strcpy(regist[0],"ax");	
strcpy(regist[1],"bx");	
strcpy(regist[2],"cx");	
strcpy(regist[3],"dx");	


	printf("generating code .... \n\n");


	printf(".model tiny\n");
	printf(".data\n");

	populateVariables();
	initiateArrays();
	for (i = 0; i < variableCnt; ++i)
	{
		printf("%s db 0\n",variables[i]);
	}

	printf(".code\n.startup\n");

	for (i = 0; i <totalCode ; ++i)
	{
		if(codeArray[i]==24 || codeArray[i]==25)
		{
			// findInAST();
			funcAssign(i-3,i+2);
		}
		if(codeArray[i]== 29)
		{
			// printf("checking ... ");
			int j=0;
			int bol=0;
			int tmp=0;
			for(j=i;j<totalCode;j++)
			{
				if(codeArray[j]==4)
					bol++,tmp=1;
				if(codeArray[j]==5)
				{

					bol--;
					funcConditional(i,j);
				}
				if(bol==0 && tmp==1)
					break;
			}
			i=j+1;
		}
		if(codeArray[i]==28)
		{
			// printf("ffffff\n\n");
			int j=0;
			int bol=0,tmp=0;
			for(j=i;j<totalCode;j++)
			{
				if(codeArray[j]==4)
					bol++,tmp=1;
				if(codeArray[j]==5)
				{
					bol--;
					funcIteration(i,j);
				}
				if(bol==0 && tmp==1)
					break;
			}
			i=j+1;	

		}
	}

	// for (int i = 0; i < variableCnt; ++i)
	// {
	// 	printf("lea di,");



	// }


	printf(".exit	\nend\n");

	printf("\n");
}




