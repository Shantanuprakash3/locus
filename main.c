/*
Team no : 51
ID :   2012C6PS650P      2012C6PS696P
Name : Vivek Kishore   Shantanu Prakash 
*/


#include "lexer.h"
#include "parser.h"
#include "adjacencyList.h"
#include "tree.h"

void displayDictionary();


char* t[] = {	
"tk_build","tk_func_id","tk_lb","tk_rb","tk_begin","tk_end","tk_void","tk_main","tk_int","tk_float","tk_string","tk_return","tk_sc","tk_id","tk_define","tk_point","tk_ob","tk_integer_literal","tk_cb","tk_polygon","tk_com","tk_comment","tk_equal","tk_point_literal","tk_plus","tk_minus","tk_dist","tk_nn","tk_while","tk_if","tk_else","tk_G","tk_EQ","tk_LT","tk_LE","tk_GE","tk_polygon_literal"
};

char* nt[]= {"program","functions","function","func_sign","func_body","main_function","main_signature","main_func_body","func_type","return_statements","XX","void_return","declarations","type","point_type","polygon_type","func","args","calling_args","statements","func_call","assign","expr","num1","op1","iteration","selection","else_selection","cond_exp","op2"};


int main()
{
	lexerFunc();

	memset(rule,-1,sizeof rule);
	memset(parse,-1,sizeof parse);

	initializeParseTable();
	initializeRuleTable();



	int i=0;


	if(codeTokens->first==NULL)
		{
	
		}	
		else
		{
		NodeLexer curr=codeTokens->first;
		while(curr!=NULL)
			{
				// printf(" %d \n",curr->tokenId);				
				code[i]=curr->tokenId;	
				codeLineNo[i] = curr->lineNo;			
				curr=curr->next;
				i++;
			}
	}



	int valid = validate();



	if(valid)
		{
			printf("code is valid - grammer rules \n");
			// displayParseTree();
			// displayBigParseTree();

			pruningParseTree();
			printf("check\n\n");
			reduceLinearChains(0,1);
			printf("check\n\n");
			
			displayASTTree();
			makeSymbolTable();
			displaySymbolTable();

			if(funcCheck())
			{
				printf("\nCode is Valid\n");

				generateCode();
			}
			else
			{
				printf("\nCode is invalid\n");
			}
		}
	else
	{
			makeSymbolTable();
			displaySymbolTable();
		printf("code is invalid\n");
	}
	return 0;
}



void displayDictionary()
{
	int i;
	printf("Terminals are :\n\n");
	for ( i = 0; i < 40; ++i)
	{
		printf("%d  -> %s\n",i,t[i]);
		/* code */
	}

	printf("Non Terminals are :\n\n");
	for ( i = 0; i < 33; ++i)
	{
		printf("%d  -> %s",i,nt[i]);
		/* code */
	}

}






