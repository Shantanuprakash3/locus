/*
Team no : 51
ID :   2012C6PS650P      2012C6PS696P
Name : Vivek Kishore   Shantanu Prakash 
*/


#include "lexer.h"
#include "adjacencyList.h"
#include "node.h"

char buffer[1000];
int lineno;
char *tok,*lex;
char lex1[1000];
LexerList codeTokens;
int tid;
FILE *fp;


//for scope
int scope=0;
int scopeCnt[100];
int type=-1;

int isNumeric(char c)
{
	if(c>='0' && c<='9')
		return 1;
	return 0;
}

int isLetter(char c)
{
	if((c>='a' && c<='z')||(c>='A' && c<='Z'))
		return 1;
	return 0;
}

char nextValid(int index)
{
	while(buffer[index]==' ')
	{
		index++;
	}
	return buffer[index];
}



void lexerFunc()
{

	codeTokens = createNewLexerList();

	fp=fopen("input.txt","r");
	if(fp==NULL)
	{
		printf("File is not present.\n");
		exit(1);
	}
	char ch;
	int buffer_size=0;
	while((ch=fgetc(fp))!=EOF)
		{
			buffer[buffer_size] = ch;
			buffer_size++; 
			printf("%c",ch);
			// printf("%d",ch);
		}



	int start=1;
	int jump;
	lineno=1;
	int i;
	for ( i = 0; i < buffer_size	;i+=jump)
		{

			memset(&lex1[0], 0, sizeof(lex1));

			if(buffer[i]==' ')
			{
				jump=1;
				continue;
			}
			if(buffer[i]=='\t')
			{
				jump=1;
				continue;
			}
			
			if(buffer[i]=='\r')
			{
				jump=1;
				continue;
			}

			if(buffer[i]=='\n')
			{
				printf("\n");
				lineno++;
				jump=1;
				continue;
			}
			// if(i!=0)
			// {
			// 	addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type);

			// }
			

			printf(" ");

			// cout<<"loop no "<<i<<"\n";
			// cout<<buffer[i]<<endl;
			//reserved words
			if(start && buffer[i]=='b' && buffer[i+1]=='u' && buffer[i+2]=='i' && buffer[i+3]=='l' && buffer[i+4]=='d' && ((buffer[i+5]==' ')||(buffer[i+5]=='\n')||(buffer[i+5]=='\0')||(buffer[i+5]=='\t')||(buffer[i+5]=='\r')))
			{
				printf("tk_build");
				tid=0;
				tok="TK_BUILD";
				lex="build";
				jump=6;
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
			}

			//find out the tab and enter operation

			if(start && buffer[i]=='b' && buffer[i+1]=='e' && buffer[i+2]=='g' && buffer[i+3]=='i' && buffer[i+4]=='n' && ((buffer[i+5]=='\r')||(buffer[i+5]==' ')||(buffer[i+5]=='\n')||(buffer[i+5]=='\t')))
			{
				printf("tk_begin");
				tok="TK_BEGIN";
				lex="begin";
				tid = 4;
				jump=5;
				scope++;
				scopeCnt[scope]++;

								
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}


			if(start && buffer[i]=='e' && buffer[i+1]=='n' && buffer[i+2]=='d' && ((buffer[i+3]==' ')||(buffer[i+3]=='\n')||(buffer[i+3]=='\0')||(buffer[i+3]=='\t')||(buffer[i+3]=='\r')))
			{
				printf("tk_end");
				tok="TK_END";
				lex="end";
				jump=3;
				tid = 5;
				scope--;
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(start && buffer[i]=='d' && buffer[i+1]=='e' && buffer[i+2]=='f' && buffer[i+3]=='i' && buffer[i+4]=='n' && buffer[i+5]=='e' && ((buffer[i+6]==' ')||(buffer[i+6]=='\n')||(buffer[i+6]=='\0')||(buffer[i+6]=='\t')||(buffer[i+6]=='\r')))
			{
				// print("")
				printf("tk_define");
				tok="TK_DEFINE";
				lex="define";
				tid = 14;
				jump=7;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(start && buffer[i]=='i' && buffer[i+1]=='n' && buffer[i+2]=='t' && ((buffer[i+3]==' ')||(buffer[i+3]=='\n')||(buffer[i+3]=='\0')||(buffer[i+3]=='\t')||(buffer[i+3]=='\r')))
			{
				printf("tk_int");
				tok="TK_INT";
				lex="int";
				jump=4;
				tid = 8;
				type = 0;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(start && buffer[i]=='p' && buffer[i+1]=='o' && buffer[i+2]=='i' && buffer[i+3]=='n' && buffer[i+4]=='t' && ((buffer[i+5]==' ')||(buffer[i+5]=='\n')||(buffer[i+5]=='\0')||(buffer[i+5]=='\t')||(buffer[i+5]=='[')||(buffer[i+5]=='\r')))
			{
				printf("tk_point");
				tok="TK_POINT";
				lex="point";
				tid = 15;
				jump=5;
				type = 1;

				int vv = buffer[i+6]-'0';
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,vv,0);continue;
			}

			if(start && buffer[i]=='p' && buffer[i+1]=='o' && buffer[i+2]=='l' && buffer[i+3]=='y' && buffer[i+4]=='g' && buffer[i+5]=='o' && buffer[i+6]=='n' && ((buffer[i+7]==' ')||(buffer[i+7]=='\n')||(buffer[i+7]=='\0')||(buffer[i+7]=='\t')||(buffer[i+7]=='[')||(buffer[i+7]=='\r')))
			{
				printf("tk_polygon");
				tok="TK_POLYGON";
				lex="polygon";
				tid = 19;
				jump=7;
				type = 2;

				int v1 = buffer[i+8]-'0';
				int v2 = buffer[i+11]-'0';

				printf("--%d %d--",v1,v2);


				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,v1,v2);continue;
			}

			if(start && buffer[i]=='r' && buffer[i+1]=='e' && buffer[i+2]=='t' && buffer[i+3]=='u' && buffer[i+4]=='r' && buffer[i+5]=='n' && ((buffer[i+6]==' ')||(buffer[i+6]=='\n')||(buffer[i+6]=='\0')||(buffer[i+6]=='\t')||(buffer[i+6]=='\r')||(buffer[i+6]==';')))
			{
				printf("tk_return");
				tok="TK_RETURN";
				tid = 11;
				lex="return";
				jump=6;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
			}

			if(buffer[i]=='w' && buffer[i+1]=='h' && buffer[i+2]=='i' && buffer[i+3]=='l' && buffer[i+4]=='e' && ((buffer[i+5]==' ')||(buffer[i+5]=='\n')||(buffer[i+5]=='\0')||(buffer[i+5]=='\t')||(buffer[i+5]=='\r')||(buffer[i+5]=='(')))
			{
				printf("tk_while");
				tid = 28;
				jump=5;
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;

			}





			if(start && buffer[i]=='m' && buffer[i+1]=='a' && buffer[i+2]=='i' && buffer[i+3]=='n' && ((buffer[i+4]==' ')||(buffer[i+4]=='\n')||(buffer[i+4]=='\0')||(buffer[i+4]=='\t')||(buffer[i+4]=='(')||(buffer[i+4]=='\r')))
			{
				printf("tk_main");
				tok="TK_MAIN";
				lex="main";
				tid = 7;
				jump=4;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
			}

			if(start && buffer[i]=='v' && buffer[i+1]=='o' && buffer[i+2]=='i' && buffer[i+3]=='d'&& ((buffer[i+4]==' ')||(buffer[i+4]=='\n')||(buffer[i+4]=='\0')||(buffer[i+4]=='\t')||(buffer[i+4]=='\r')))
			{
				printf("tk_void");
				tok="TK_VOID";
				lex="void";
				tid = 6;
				jump=5;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
			}

			if(start && buffer[i]=='i' && buffer[i+1]=='f'&& ((buffer[i+2]==' ')||(buffer[i+2]=='\n')||(buffer[i+2]=='\0')||(buffer[i+2]=='\t')||(buffer[i+2]=='(')||(buffer[i+2]=='\r')))
			{
				printf("tk_if");
				tid = 29;
				tok="TK_IF";
				lex="if";
				jump=2;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
			}

			// if(buffer[i]=='&' && buffer[i+1]=='&')
			// {
			// 	tid = 33;
			// 	jump=2;
				
			// 	addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;

			// }

			if(start && buffer[i]=='e' && buffer[i+1]=='l' && buffer[i+2]=='s' && buffer[i+3]=='e'&& ((buffer[i+4]==' ')||(buffer[i+4]=='\n')||(buffer[i+4]=='\0')||(buffer[i+4]=='\t')||(buffer[i+4]=='\r')))
			{
				printf("tk_else");
				tok="TK_ELSE";
				tid = 30;
				lex="else";
				jump=5;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
			}

			if(buffer[i]=='=')
			{
				if(buffer[i+1]=='=')
				{
					printf("tk_isEqual");
					tok="TK_ISEQUAL";
				lex="==";
					jump=2;
					tid = 32;
					
					addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
				}
				else
				{
					printf("tk_equal");
					tok="TK_EQUAL";
				lex="=";
				tid = 22;
					jump=1;
					
					addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
				}

			}
			if(buffer[i]=='<')
			{
				if(buffer[i+1]=='=')
				{
					printf("tk_isLessEqual");
					tok="TK_ISLESSEQUAL";
				lex="<=";
				tid = 34;
					jump=2;
					
					addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
				}
				else
				{
					printf("tk_isLess");
					tok="TK_ISLESS";
				lex="<";
				tid = 33;
					jump=1;
					
					addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
				}
			}

			if(buffer[i]=='>')
			{
				if(buffer[i+1]=='=')
				{
					printf("tk_isGreaterEqual");
					tok="TK_ISGREATEREQUAL";
				lex=">=";
				tid = 35;
					jump=2;
					
					addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
				}
				else
				{
					printf("tk_isGreater");
					tok="TK_ISGREATER";
				lex=">";
				tid = 31;
					jump=1;
					
					addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
				}
			}

			// if(buffer[i]=='!')
			// {
			// 	if(buffer[i+1]=='=')
			// 	{
			// 		printf("tk_isNotEqual");
			// 		tok="TK_ISNOTEQUAL";
			// 	lex="!=";
			// 		jump=2;
			// 		tid = 36;
			// 		addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
			// 	}
			// 	else
			// 	{
			// 	}
			// }

			if(buffer[i]=='+')
			{
				printf("tk_add");
				tok="TK_ADD";
				lex="+";
				tid = 24;
				jump=1;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(buffer[i]=='-')
			{
				printf("tk_subtract");
				tok="TK_SUBTRACT";
				lex="-";
				jump=1;
				tid = 25;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}
			// if(buffer[i]=='*')
			// {
			// 	printf("tk_multiply");
			// 	tok="TK_MULTIPLY";
			// 	lex="*";
			// 	jump=1;
			// 	tid = 50;
				
			// 	addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
			// 	continue;
			// }
			// if(buffer[i]=='/')
			// {
			// 	printf("tk_divide");
			// 	tok="TK_DIVIDE";
			// 	lex="/";
			// 	tid = 28;
			// 	jump=1;
				
			// 	addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
			// 	continue;
			// }

			if(buffer[i]==';')
			{
				printf("tk_semicolon");
				tok="TK_SEMICOLON";
				lex=";";
				tid = 12;
				jump=1;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(buffer[i]=='(')
			{
				printf("tk_lb");
				tok="TK_LB";
				lex="(";
				tid = 2;
				jump=1;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(buffer[i]==')')
			{
				printf("tk_rb");
				tok="TK_RB";
				lex=")";
				tid =3 ;
				jump=1;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(buffer[i]==']')
			{
				printf("tk_squareCB");
				tok="TK_squareCB";
				lex="]";
				tid = 18;
				jump=1;
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);continue;
			}

			if(buffer[i]=='[')
			{
				printf("tk_squareOB");
				tok="TK_squareOB";
				lex="[";
				tid = 16;
				jump=1;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(buffer[i]==',')
			{
				printf("tk_comma");
				tok="TK_comma";
				lex=",";
				jump=1;
				tid = 20;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(buffer[i]=='_' && buffer[i+1]=='n' && buffer[i+2]=='n' && buffer[i+3]=='_')
			{
				printf("tk_nn");
				tok="TK_nn";
				lex="_nn_";
				tid = 27;
				jump=4;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			if(buffer[i]=='_' && buffer[i+1]=='d' && buffer[i+2]=='i' && buffer[i+3]=='s' && buffer[i+4]=='t' && buffer[i+5]=='_')
			{
				printf("tk_dist");
				tok="TK_dist";
				lex="_dist_";
				tid = 26;
				jump=6;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			

			if(isNumeric(buffer[i]))
			{
				// cout<<"number hai bhai \n\n\n";
				int j = i;
				int k=0;
				while(isNumeric(buffer[j]))
				{
					lex1[k]=buffer[j];
					k++;
					j++;
				}
				lex1[k]='\0';
				// lex1[k]='\0';

				printf("int_literal");
				tok = "INT_LITERAL";
				jump=j-i;
				tid = 17 ;
				type = 0;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;

			}

			// if(buffer[i]=='"')
			// {
				
			// 	int j=i;
			// 	int k=0;
			// 	while(!buffer[j]=='\"' || j<buffer_size)
			// 	{
			// 		lex1[k]=buffer[j];
			// 		j++;
			// 		k++;
			// 	}
			// 	lex1[k]='\"';
			// 	jump=j-i+1;
			// 	tid = 43;
			// 	tok="STRING_LITERAL";
			
			// 	addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
			// 		continue;


			// }


			if(isLetter(buffer[i]))
			{
				int j = i;
				int k=0;
				while(isLetter(buffer[j])||isNumeric(buffer[j]))
				{
					lex1[k]=buffer[j];
					j++;
					k++;
				}
				if(nextValid(j)=='(')
				{
					printf("func_id");
					tok = "tk_funcID";
					tid = 1;
				}
				else{
				printf("tk_ID");
				tok = "TK_ID";
				tid = 13;
				}	
				

				lex1[k]='\0';


				jump=j-i;


				// printf("%")
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}


			// if(buffer[i]=='{')
			// {
			// 	tid = 27;
			// 	jump=1;

			// 	printf("leftcurl");
				
			// 	addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
			// 	continue;
			// }
			// if(buffer[i]=='}')
			// {
			// 	tid = 28;
			// 	jump=1;
			// 	printf("rightcurl");

				
			// 	addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
			// 	continue;
			// }




			if(buffer[i]=='{')
			{
				int k=0;
				int j=i;
				if(nextValid(j+1)=='{')
				{
					while(!(buffer[j]=='}' && buffer[j+1]=='}'))
					{
						lex1[k]=buffer[j];
						j++;
						k++;
					}
					lex1[k]='}';
					lex1[k+1]='}';
					lex1[k+2] = '\0';
					printf("poly_literal");
					tok="TK_POLYLITERAL";
					tid = 36;
					type = 2;
					addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);

					jump=j-i+2;
				}
				else
				{
					// printf(" yaha hai\n");
					while(buffer[j]!='}')
					{
						// printf("%d ",j);
						lex1[k]=buffer[j];
						j++;
						k++;
					}
					printf(" yaha hai\n");

					lex1[k]='}';
					lex1[k] = '\0';
					printf("point_literal");
					tok="TK_POINTLITERAL";
					jump=j-i+1;
					tid = 23;
					type=1;
					addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);

				}

				continue;
			


			}


			if(buffer[i]=='#')
			{
				int j=i;
				int k;
				while(buffer[j]!='\n' ||(buffer[i+5]=='\r'))
				{
					lex1[k]=buffer[j];
					j++;
					k++;
				}
				printf("COMMMENT ");
				tok="comment";
				tid = 21;
				jump=j-i;
				
				addToLexerList(codeTokens,tid,lineno,lex1,scope,scopeCnt[scope],type,0,0);
				continue;
			}

			// errorList.push_back(lineno);
			printf("#");
			jump=1;

			tid=-1;
		}	





		// printf()

		// sort(tokenlist.begin(),tokenlist.end(),compare);

		// for (int i = 0; i < tokenlist.size(); ++i)
		// 	{
		// 		cout<<tokenlist[i].lineno<<" "<<tokenlist[i].token<<"  "<<tokenlist[i].lexeme<<"\n";
		// 		/* code */
		// 	}	


 
}



