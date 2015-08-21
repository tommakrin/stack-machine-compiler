%{
#define YYDEBUG 1
char *foobar;
%}

%start program

%token	NUMBER
%token  ID
%token	PLUS	MINUS	TIMES
%token	LP	RP	EQUALS	COMMA
%token	END

%token	LET	IN	AND

%left	PLUS	MINUS
%left	TIMES
%left	LET	IN	AND
%right	EQUALS

%%

program:{printf("Empty Input\n");}  /* empty */
        | program line /* do nothing */

line:   expr END			{printtree($1); printf("\n"); }
	;

expr    : /*Empty*/
	| LET deflist IN expr 		{$$ = make_let_tree($2,$4); printf("Detected LET sequence.\n");}
	| ID				{$$ = make_id_leaf($1); printf("Detected ID.\n");}
	| NUMBER			{$$ = make_number_leaf($1); printf("Detected NUMBER.\n");}
        | PLUS LP expr COMMA expr RP  	{$$ = make_plus_tree($3,$5); printf("Detected expr PLUS expr.\n");}
        | TIMES LP expr COMMA expr RP 	{$$ = make_times_tree($3,$5); printf("Detected expr TIMES expr.\n");}
	| MINUS arg			{$$ = make_minus_tree($2);}
        ;

deflist	: definition
	| definition AND deflist	{$$ = make_and_tree($1,$3);}
	;

arg	: ID				{$$ = make_id_leaf($1); printf("Detected MINUS ID.\n"); }
	| NUMBER			{$$ = make_number_leaf($1); printf("Detected MINUS NUMBER.\n");}
	;

definition : /*Empty*/
	   | ID EQUALS expr {$$ = make_eq_tree($1,$3); printf("Detected EQ-%s\n", $1);}
	   ;
%%

int yyerror (char *s) {fprintf (stderr, "%s\n", s);}
