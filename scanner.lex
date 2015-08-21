%{
#include "parser.h"
%}

DIGIT [0-9]
LETTER [a-zA-Z]
ALPHANUM [a-zA-Z0-9]
%%

LET			{printf("Encountered LET\n"); return(LET);}
IN			{printf("Encountered IN\n"); return(IN);}
AND			{printf("Encountered AND\n"); return(AND);}
{DIGIT}+		{yylval = atoi(yytext); return (NUMBER);}
{LETTER}{ALPHANUM}*     { if (strlen(yytext) <= 8){
                  		yylval = (intptr_t) yytext;
				printf( "<ID, %s> ", yytext );
				return(ID);
        	        } else {
                        	yytext[8] = '\0';
                        	printf("WARNING! Long identifier. Truncating to 8 chars\n");
                        	printf( "<ID, %s> ", yytext );
				return(ID);
                  	}
                	}
[ \t] ;
[\n]     return(END); 
"+"      return(PLUS);
"-"      return(MINUS);
"*"      return(TIMES);
"="	 return(EQUALS);
"("      return(LP);
")"      return(RP);
","	 return(COMMA);
<<EOF>>	 return(0);
%%

int yywrap (void) {return 1;}
