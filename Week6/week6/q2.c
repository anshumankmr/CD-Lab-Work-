#include "lex.yy.c"
#include <stdio.h>
#include <string.h>

Tokenptr tk;
void statement_list();
void assign_stat();
void expn();
void simple_expn();
void term();
void factor();
void eprime();
void relop();
void addop();
void tprime();
void mulop();
void statement();
Tokenptr getNextToken()
{
	Tokenptr tp;
	if(!(tp = yylex()))
		tp = NULL;
	return tp;
}

void looping_stat()
{
	// printf("Currently at %s in looping_stat \n",tk->lexeme );
	if(strcmp(tk->lexeme,"while")==0)
 	{
 		// printf("hi\n");
 	 tk = getNextToken();
     if(strcmp(tk->lexeme,"(")==0)
	 {
	 	tk = getNextToken();
 		expn();
		tk = getNextToken();
 		if (strcmp(tk->lexeme,")")==0)
 		{
         tk = getNextToken();
         if (strcmp(tk->lexeme,"{")==0)
 		 {
          tk = getNextToken();
          statement_list();
          tk = getNextToken();
          if (strcmp(tk->lexeme,"}")==0)
          {
           tk = getNextToken();
		   if(tk == NULL)
			{
			 printf("Accept\n");
			 exit(0);
			}
          } 
         }
 		}
     }		
	}
	else if(strcmp(	tk->lexeme, "for")==0)
	{
	 tk = getNextToken();
     // printf("%s\n",tk->lexeme );
     if(strcmp(tk->lexeme,"(")==0)
	 {
	 	tk = getNextToken();
 	    // printf("nsdfjnjfnjkdfnh");
 		assign_stat();//done
		tk = getNextToken();
 		if (strcmp(tk->lexeme,";")==0)
 		{
         tk = getNextToken();
         expn();//done
         tk = getNextToken();
         if (strcmp(tk->lexeme,";")==0)
         {
         	tk = getNextToken();
         	assign_stat();//
         	tk = getNextToken();
         	if (strcmp(tk->lexeme,")")==0)
         	{
         	 tk = getNextToken();
         	 if (strcmp(tk->lexeme,"{")==0)
         	 {
         	 	tk = getNextToken();
         	 	statement_list();//
         	 	tk = getNextToken();
         	 	if (strcmp(tk->lexeme,"}")==0)
         	 	{
         	 	 tk = getNextToken();
         	 	 if(tk == NULL)
			     {
			      printf("Accept\n");
			      exit(0);
			     }
         	 	}
         	 }
         	}
         }
 		}
     }		
	}
	else
	{
		printf("Reject\n");
		exit(0);
	}
	tk = getNextToken();
	if(tk == NULL)
	{
		printf("Accept\n");
		exit(0);
	}
}
void dprime()
{
	tk = getNextToken();
	if (strcmp(tk->lexeme,"else")==0)
	{
		tk = getNextToken(); 
       // statement_list();
	   if (strcmp(tk->lexeme,"{")==0)
	   {
        tk = getNextToken(); 
        statement_list();
        // dprime();
        tk = getNextToken(); 
       // statement_list();
	   if (strcmp(tk->lexeme,"}")==0)
	   {
        tk = getNextToken(); 
        // statement_list();
        // dprime();
        if (tk->lexeme == NULL)
        {
         printf("Accepted\n");
         return;
        }
	   }
	   }
	}
}
void decision_stat()
{
	tk = getNextToken();
	if (strcmp(tk->lexeme,"if")==0)
	{
	 tk = getNextToken();
	 if (strcmp(tk->lexeme,"(")==0)
	 {
      tk = getNextToken();
      if (strcmp(tk->lexeme,"{")==0)
	  {
       tk = getNextToken(); 
       statement_list();
	   if (strcmp(tk->lexeme,"}")==0)
	   {
        tk = getNextToken(); 
        // statement_list();
        dprime();
	   }	
	  }	 
	 }	
	}
}
void statement()
{
	tk = getNextToken();
	if (strcmp(tk->lexeme,"if")== 0)
	{
		decision_stat();
	}
	else if (tk->type == IDENTIFIER)
	{ 
		assign_stat();
	}
	else if (strcmp(tk->lexeme,"for")== 0 || strcmp(tk->lexeme,"while")== 0)
	{
		looping_stat();
	}
	else
	{
		printf("statement Rejected \n");
		exit(0);
	}
}
void statement_list()
{
	tk = getNextToken();
	if (tk == NULL)
	{
		printf("Accept\n");
		return;
	}
	statement();
	tk =  getNextToken();
	statement_list();
}
void assign_stat()
{
	// printf("%s\n",tk->lexeme );
	tk = getNextToken();
	if (tk->type == IDENTIFIER)
	{
	 tk = getNextToken();
	 // printf("ion \n");
	 if (strcmp(tk->lexeme,"=")==0)
	  {
	  	tk = getNextToken();
	  	return;
	  }
	  else if (strcmp(tk->lexeme,"+=")==0)
	  	{
	  		printf("skbffb k\n");
	  	 tk = getNextToken();
	  	 if(tk->type==NUMBER)
	  	 {
	  	 	// printf("%s\n", );
	  	 	printf("Accepted\n");
	  	 	exit(0);
	  	 }	
	  	}
	  	else if (strcmp(tk->lexeme,"++")==0)
	  	{
	  	 printf("Accepted\n");
	  	 	exit(0);
	  	}
	    else
	    {
	    	printf("Rejected\n");
	    	exit(0);
	    }
	  	return;
	}
}
void expn()
{
 printf("inside expn %s\n",tk->lexeme );
 // tk = getNextToken();
 printf("calling simple_expn %s\n",tk->lexeme );
 simple_expn();//
 tk = getNextToken();
 eprime();
}
void addop()
{
	tk = getNextToken();
	if (strcmp(tk->lexeme,"+")==0 || strcmp(tk->lexeme,"-")==0)
    {
    	return;
    }
    else
    {
    	printf("Addop Rejected \n");
    	exit(0);
    }
}
void seprime()
{
	tk = getNextToken();
	if (tk == NULL)
	{
		printf("Accepted\n");
		exit(0);
	}
	addop();
	tk = getNextToken();
	term();
	tk = getNextToken();
	seprime();
}
void simple_expn()
{
	// tk = getNextToken();
	printf("calling term %s\n",tk->lexeme );
	term();//
	tk = getNextToken();
	seprime();
}
void term()
{
	printf("calling factor %s\n",tk->lexeme );
	// tk = getNextToken();
	factor();//
	// tk = getNextToken();
	eprime();
	return;
}
void factor()
{
	printf("factor %s\n",tk->lexeme );

	if (tk->type == IDENTIFIER || tk->type == NUMBER)
	{
		 tk = getNextToken();
         	 	 if(tk == NULL)
			     {
			      printf("Accept\n");
			      exit(0);
			     }
	     printf("returning from factor %s \n",tk->lexeme);
	     // relop();
		return;
	}
	else
	{
       printf("%s\n",tk->lexeme );
   		printf("Rsjected\n");
		exit(0);

	}
}
void eprime()
{
	// tk = getNextToken();
	printf("soemthing %s\n",tk->lexeme );	
	if (tk == NULL)
	{
		// printf("Ac\n");
		return;
	}
	relop();//
	// tk = getNextToken();
	printf("%s\n",tk->lexeme );
	if (tk->type == IDENTIFIER || tk->type == NUMBER)
	{
        tk  = getNextToken();
        printf("eprime %s\n",tk->lexeme );
        // tk = getNextToken();
        assign_stat();
		return;
	}
	// simple_expn();//
}

void relop()
{
	if (strcmp(tk->lexeme,"==")==0 || strcmp(tk->lexeme,"!=")==0 || strcmp(tk->lexeme,"<=")==0 || strcmp(tk->lexeme,">=")==0 || strcmp(tk->lexeme,">")==0 || strcmp(tk->lexeme,"<")==0)
	{
		 tk = getNextToken();
         	 	 if(tk == NULL)
			     {
			      printf("Accept\n");
			      exit(0);
			     }
		return;
	}
	else
	{
		printf("Relop Rejected\n");
		exit(0);

	}
}
void tprime()
{
	if (strcmp(tk->lexeme,"*")!=0 || strcmp(tk->lexeme,"/")!=0 || strcmp(tk->lexeme,"%")!=0 )
	{
     return;
	}
	tk  = getNextToken();
	mulop();//
	tk = getNextToken();
	factor();//
	tk = getNextToken();
	tprime();
}
void mulop()
{
	if (strcmp(tk->lexeme,"*")==0 || strcmp(tk->lexeme,"/")==0 || strcmp(tk->lexeme,"%")==0 )
	{
         tk = getNextToken();
         	 	 if(tk == NULL)
			     {
			      printf("Accept\n");
			      exit(0);
			     }
		return;
	}
	else
	{
		printf("Rejeected\n");
		exit(0);

	}
}
int main()
{
	printf("Enter the string \n");
	scanf(" %[^\t\n]s",yyin);
	tk = getNextToken();
	looping_stat();
	printf("Reject\n");
}