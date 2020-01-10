/*
Team no : 51
ID :   2012C6PS650P      2012C6PS696P
Name : Vivek Kishore   Shantanu Prakash 
*/

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

 
#define MAX_SIZE 10000
 
char* ter[] = {	
"tk_build","tk_func_id","tk_lb","tk_rb","tk_begin","tk_end","tk_void","tk_main","tk_int","tk_float","tk_string","tk_return","tk_sc","tk_id","tk_define","tk_point","tk_ob","tk_integer_literal","tk_cb","tk_polygon","tk_com","tk_comment","tk_equal","tk_point_literal","tk_plus","tk_minus","tk_dist","tk_nn","tk_while","tk_if","tk_else","tk_G","tk_EQ","tk_LT","tk_LE","tk_GE","tk_polygon_literal"

};

int stack[MAX_SIZE];
int code[MAX_SIZE];
int codeLineNo[MAX_SIZE];

List tree[10000];
List astTree[10000];
LexerList bigTree[10000];

int parse[1000][1000];
int rule[1000][1000];

//...........................................stack...............................................
void push();
int pop();
void traverse();
int is_empty();
int top_element();
int top = -1;

void push(int value) {   
   top++;
   stack[top] = value;
}
 
int pop() {
   int element;
 
   if (top == -1)
      return top;
 
   element = stack[top];
   top--;
 
   return element;
}   
 
void traverse() {
   int d;
 
   if (top == - 1) {
      printf("Stack is empty.\n\n");
      return;
   }   
 
   printf("There are %d elements in stack.\n", top+1);
 
   for (d = top; d >= 0; d--)
      printf("%d\n", stack[d]);
   printf("\n");
}  
 
int is_empty() {
   if (top == - 1)
      return 1;
   else
      return 0;
}
 
int top_element() {
   return stack[top];
}

//.........................................stack end.......................................


int presentCodeState=0;

int tokenType[10000];
int tokenTypeAST[10000];
int TID=0;
int TID2 = 0;
int presentIndex=0;

void pushToStack(int tokenID,int PID)
{
	tokenType[TID] = tokenID;
	tokenTypeAST[TID] = tokenID;
	push(TID);

	tree[TID] = createNewList();

	// if((tokenID!=2)&&(tokenID!=3)&&(tokenID!=19)&&(tokenID!=12))
	if(tokenID==13)
	{
		addToList(tree[PID],TID,presentIndex);
		presentIndex++;

	}

	else{
	if(tokenID!=37)
		addToList(tree[PID],TID,-1);
	}
	++TID;
	assert(TID<10000);
}


//need to make a line getter for present state code

int validate()
{
	
	// insert top elements..program id
	// pushToStack();
	int i;
	// printf("\n\nchecking..\n\n");

	tree[999] = createNewList();
	bigTree[999] = createNewLexerList();

	pushToStack(1000,999);
	//999 is the parent of root right

	// printf("\n\nchecking..\n\n");

	while(!is_empty())
	{
		int state=tokenType[top_element()];
		int parentID = top_element();

		// printf("state is %d .. parentID is %d %d\n",state,parentID,TID);

		pop();
		if(state<1000)
		{
			//terminal
			if(state==37)
			{
				//empty
			}
			else if(state==code[presentCodeState])
			{	
				presentCodeState++;
				// printf("match hai ...---------------------- %d  %s-----!!!!\n\n\n",state,ter[state]);
			}
			else
			{
				// printf("%d %d\n",state,code[presentCodeState]);
				printf(" Compilation Error at Line no.%d\n",codeLineNo[presentCodeState]);
				return 0;
			}
		}		
		else
		{
		int k;
		//non-terminal

		// printf("non-terminal\n");


// printf("\n\nSEE PARSE TABLE AT %d %d\n\n",state-1000,code[presentCodeState]);
		int z = parse[state-1000][code[presentCodeState]]-1;
		
		// printf("\nSee rule no %d\n\n",z);

		// printf("rule no %d -- %d -- %d \n",z,presentCodeState,code[presentCodeState]);
		if(z<0)
		{
				printf("Compilation Error at Line no.%d\n",codeLineNo[presentCodeState]);
			return 0;
		}	
		for ( k = 0;rule[z][k]!=-1;++k)
		{
			bigTree[TID2] = createNewLexerList();
			addToLexerList(bigTree[parentID],rule[z][k],-1,"\0",-1,-1,-1,-1,TID2);
			TID2++;
		}
		k--;
		for (;k>=0;--k)
			{
			// printf("rule=%d --parseentID=%d\n",rule[z][k],parentID);
			pushToStack(rule[z][k],parentID);			
			}
		}
	}

	for (i = 0; i < 10000; ++i)
	{
		tokenTypeAST[i] = tokenType[i];
	}

return 1;
}





void initializeTerminals()
{


}


void initializeNonTerminals()
{
	

	
}

void initializeParseTable()
{	


parse[0][0]=1; parse[0][6]=1;
//program -> functions main_function.
parse[1][0]=2; parse[1][6]=3;
//functions -> function functions.
//functions ->  .
parse[2][0]=4;
//function -> func_sign func_body.
parse[3][0]=5;
//func_sign -> build func_type func_id tk_lb args tk_rb.
parse[4][4]=6;
//func_body -> begin declarations statements return_statements end.
parse[5][6]=7;
//main_function -> main_signature main_func_body.
parse[6][6]=8;
//main_signature -> void main tk_lb tk_rb.
parse[7][4]=9; 
//main_func_body -> begin declarations statements void_return end.
parse[8][8]=10; parse[8][9]=11; parse[8][10]=12;
//func_type -> int .
//func_type -> float .
//func_type -> string.
parse[9][11]=13;
//return_statements -> return XX .
parse[10][12]=15; parse[10][13]=14;
//XX -> arith_id .
//XX -> return tk_sc.
parse[11][11]=16;
//void_return -> return tk_sc.
parse[12][1]=18; parse[12][11]=18; parse[12][13]=18; parse[12][14]=17; parse[12][21]=18; parse[12][28]=18; parse[12][29]=18;
//declarations -> define type id tk_sc declarations  .
//declarations -> .
parse[13][8]=19; parse[13][9]=20; parse[13][15]=21; parse[13][19]=22; 
//type -> int  .
//type -> float .
//type -> point_type  .
//type -> polygon_type.
parse[14][15]=23;
//point_type -> point tk_ob integer_literal tk_cb.
parse[15][19]=24;
//polygon_type -> polygon tk_ob integer_literal tk_cb tk_ob integer_literal tk_cb.
parse[16][2]=25;
//func  -> tk_lb calling_args tk_rb.
parse[17][3]=27; parse[17][8]=26; parse[17][9]=26; parse[17][15]=26; parse[17][19]=26;
//args -> type id tk-com args  .
//args ->  .
parse[18][3]=29; parse[18][13]=28;
//calling_args  -> id tk_com calling_args .
//calling_args ->  .
parse[19][1]=33; parse[19][5]=35; parse[19][11]=35; parse[19][13]=30; parse[19][21]=34; parse[19][28]=31; parse[19][29]=32; 
//statements -> assign statements  .
//statements -> iteration statements .
//statements -> selection statements  .
//statements -> func_call  .
//statements -> comment .
//statements -> .
parse[20][1]=36;
//func_call -> func_id func.
parse[21][13]=37; 
//assign -> id tk_equal expr tk_sc .
parse[22][13]=38; parse[22][17]=38; parse[22][23]=38; parse[22][36]=38;
//expr -> num1 op1 num1 .
parse[23][13]=39; parse[23][17]=40; parse[23][23]=41; parse[23][36]=56; 
//num1 -> id .
//num1 -> integer_literal .
//num1 -> point_literal .
parse[24][24]=42; parse[24][25]=43; parse[24][26]=44; parse[24][27]=45;
//op1 -> tk_plus .
//op1 -> tk_minus .
//op1 -> tk_dist . 
//op1 -> tk_nn .
parse[25][28]=46;
//iteration -> while tk_lb cond_exp tk_rb begin statements end .
parse[26][29]=47;
//selection -> if tk_lb cond_exp tk_rb begin statements end else_selection .
parse[27][30]=48; parse[27][28]=49; parse[27][29]=49; parse[27][21]=49;parse[27][5]=49; parse[27][11]=49; parse[27][13]=49;parse[27][1]=49;
//else_selection -> else begin statements end .
//else_selection -> .
parse[28][13]=50; parse[28][17]=50; parse[28][23]=50; parse[28][36]=50;
//cond_exp -> num1 op2 num1 .
parse[29][31]=51; parse[29][32]=52;parse[29][33]=53;parse[29][34]=54;parse[29][35]=55;
//op2 -> tk_G .
//op2 -> tk_EQ . 
//op3 -> tk_LT .
//op4 -> tk_LE .
//op5 -> tk_GE .

}

void initializeRuleTable()
{
rule[0][0]=1001 ;rule[0][1]=1005 ;
rule[1][0]=1002 ;rule[1][1]=1001 ;
rule[2][0]=37 ;
rule[3][0]=1003 ;rule[3][1]=1004 ;
rule[4][0]=0 ;rule[4][1]=1008 ;rule[4][2]=1 ;rule[4][3]=2 ;rule[4][4]=1017 ;rule[4][5]=3 ;
rule[5][0]=4 ;rule[5][1]=1012 ;rule[5][2]=1019 ;rule[5][3]=1009 ;rule[5][4]=5 ;
rule[6][0]=1006 ;rule[6][1]=1007 ;
rule[7][0]=6 ;rule[7][1]=7 ;rule[7][2]=2 ;rule[7][3]=3 ;
rule[8][0]=4 ;rule[8][1]=1012 ;rule[8][2]=1019 ;rule[8][3]=1011 ;rule[8][4]=5 ;
rule[9][0]=8 ;
rule[10][0]=9 ;
rule[11][0]=10 ;
rule[12][0]=11 ;rule[12][1]=1010 ;rule[12][2]=12 ;
rule[13][0]=13 ;
rule[14][0]=37 ;
rule[15][0]=11 ;rule[15][1]=12 ;
rule[16][0]=14 ;rule[16][1]=1013 ;rule[16][2]=13 ;rule[16][3]=12 ;rule[16][4]=1012 ;
rule[17][0]=37 ;
rule[18][0]=8 ;
rule[19][0]=9 ;
rule[20][0]=1014 ;
rule[21][0]=1015 ;
rule[22][0]=15 ;rule[22][1]=16 ;rule[22][2]=17 ;rule[22][3]=18 ;
rule[23][0]=19 ;rule[23][1]=16 ;rule[23][2]=17 ;rule[23][3]=18 ;rule[23][4]=16 ;rule[23][5]=17 ;rule[23][6]=18 ;
rule[24][0]=2 ;rule[24][1]=1018 ;rule[24][2]=3 ;
rule[25][0]=1013 ;rule[25][1]=13 ;rule[25][2]=20 ;rule[25][3]=1017 ;
rule[26][0]=37 ;
rule[27][0]=13 ;rule[27][1]=20 ;rule[27][2]=1018 ;
rule[28][0]=37 ;
rule[29][0]=1021 ;rule[29][1]=1019 ;
rule[30][0]=1025 ;rule[30][1]=1019 ;
rule[31][0]=1026 ;rule[31][1]=1019 ;
rule[32][0]=1020 ;
rule[33][0]=21 ;
rule[34][0]=37 ;
rule[35][0]=1 ;rule[35][1]=1016 ;rule[35][2]=12 ;
rule[36][0]=13 ;rule[36][1]=22 ;rule[36][2]=1022 ;rule[36][3]=12 ;
rule[37][0]=1023 ;rule[37][1]=1024 ;rule[37][2]=1023 ;
rule[38][0]=13 ;
rule[39][0]=17 ;
rule[40][0]=23 ;
rule[41][0]=24 ;
rule[42][0]=25 ;
rule[43][0]=26 ;
rule[44][0]=27 ;
rule[45][0]=28 ;rule[45][1]=2 ;rule[45][2]=1028 ;rule[45][3]=3 ;rule[45][4]=4 ;rule[45][5]=1019 ;rule[45][6]=5 ;

rule[46][0]=29 ;rule[46][1]=2 ;rule[46][2]=1028 ;rule[46][3]=3 ;rule[46][4]=4 ;rule[46][5]=1019 ;rule[46][6]=5 ;rule[46][7]=1027 ;


rule[47][0]=30 ;rule[47][1]=4 ;rule[47][2]=1019 ;rule[47][3]=5 ;
rule[48][0]=37 ;
rule[49][0]=1023 ;rule[49][1]=1029 ;rule[49][2]=1023 ;
rule[50][0]=31 ;
rule[51][0]=32 ;
rule[52][0]=33 ;
rule[53][0]=34 ;
rule[54][0]=35 ;
rule[55][0]=36 ;
}
