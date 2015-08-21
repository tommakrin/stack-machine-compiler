#include <string.h>

typedef enum {ID_LEAF, NUM_LEAF, PLUS, TIMES, MINUS, EQ, AND, LET} node_type;

typedef struct tree{
	char *token;
	TREE *l;
	TREE *r;
	TREE *child;
	node_type type;
}TREE;

void command(int commandId, int arg);

char varlist[10][10][8];//10 nesting levels, each containing a maximum of 10 variable names, with each name being 7 chars long max
int nest_level=-1;
int vars_in_level[10];


/* Make identifier leaves */

TREE *make_id_leaf(char *s){

	TREE *leafId = malloc(sizeof(TREE));
	char *str = malloc(sizeof(char)*10);
	strcpy(str,s);

	leafId->type=ID_LEAF;
	leafId->token = str;
	leafId->l = NULL;
	leafId->r = NULL;
	leafId->child = NULL;

	printf("ID Leaf is: %s\n", leafId->token);
	printf("ID Leaf is: %s\n", s);
	printf("ID Leaf is: %s\n", str);

	return (leafId);
}

/* Make number leaves */

TREE *make_number_leaf(int n){

	TREE *leafNum = malloc(sizeof(TREE));

	char *ch = malloc(sizeof(char)*10);

	sprintf(ch, "%d", n); /* Effective way to convert int to string */

	leafNum->type=NUM_LEAF;
	leafNum->token = ch;
	leafNum->l = NULL;
        leafNum->r = NULL;
        leafNum->child = NULL;

	printf("NUM Leaf is: %s\n", leafNum->token);

	return (leafNum);
}

/* Addition tree */

TREE *make_plus_tree(TREE *l, TREE *r){

	TREE *plusTree = malloc(sizeof(TREE));

	plusTree->type=PLUS;
	plusTree->token = "+";
	plusTree->l = l;
	plusTree->r = r;
	plusTree->child = NULL;

	return (plusTree);

}

/* Multiplication tree */

TREE *make_times_tree(TREE *l, TREE *r){

	TREE *timesTree = malloc(sizeof(TREE));

	timesTree->type=TIMES;
	timesTree->token = "*";
	timesTree->l = l;
	timesTree->r = r;
	timesTree->child = NULL;

	return (timesTree);

}

/* Minus tree */

TREE *make_minus_tree(TREE *child){

	TREE *minusTree = malloc(sizeof(TREE));

	minusTree->type=MINUS;
        minusTree->token = "-";
        minusTree->l = NULL;
        minusTree->r = NULL;
        minusTree->child = child;

        return (minusTree);

}

TREE *make_eq_tree(char *s, TREE *child){

	char *c1, *c2;
	TREE *eqTree = malloc(sizeof(TREE));
	char *str = malloc(sizeof(char)*10);

	//parse token to contain var name only
	for(c1=s, c2=str; isalpha(*c1); *(c2++)=*(c1++));
	*c2='\0';

	eqTree->type=EQ;
        eqTree->token = str;
	eqTree->l = NULL;
	eqTree->r = NULL;
        eqTree->child = child;

        return (eqTree);

}

TREE *make_and_tree(TREE *l, TREE *r){

        TREE *andTree = malloc(sizeof(TREE));

	andTree->type=AND;
        andTree->token = "&&";
        andTree->l = l;
        andTree->r = r;
        andTree->child = NULL;

        return (andTree);

}

TREE *make_let_tree(TREE *l, TREE *r){

        TREE *letTree = malloc(sizeof(TREE));

	letTree->type=LET;
        letTree->token = "LET";
        letTree->l = l;
        letTree->r = r;
        letTree->child = NULL;

        return (letTree);

}


void printtree(TREE *tree)
{

	TREE *tr = malloc(sizeof(TREE));
	tr = tree;

        if (tr->l || tr->r){
                printf("(");
        }
	if (tr->child){
		printf("(");
		if (tr->token != "-"){
			printf(" = ");
		}
	}

	printf(" %s ", tr->token);

        	if (tr->l){
            		printtree(tr->l);
        	}

		if (tr->r){
	        	printtree(tr->r);
        	}

	if (tr->child){
	    printtree(tr->child);
	}
        if (tr->l || tr->r){
            printf(")");
        }
	if (tr->child){
	    printf(")");
	}
}

void generatecode(TREE *tree)
{
	int i, var, level;
	//char* str=malloc(sizeof(char)*10);

	TREE *tr = malloc(sizeof(TREE));
	tr=tree;

	switch(tr->type){

	case ID_LEAF:	
	for(level=0; level<=nest_level; level++)
	for(var=0; var<vars_in_level[level]; var++)
	if(!strcmp(tr->token, varlist[level][var])) goto entry_found;
	printf("Unknown variable '%s'\n",tr->token);
	exit(-1);

	entry_found:

	command(12,0);
	for(i=level; i<nest_level; i++) command(13,0);  
	command(14, var+1);
	command(5, 0);
	break;

	case NUM_LEAF:
	command(1, atoi(tr->token));
	break;

	case PLUS:
	generatecode(tr->l);
	generatecode(tr->r);
	command(2, 0);
	break;

	case TIMES:
	generatecode(tr->l);
	generatecode(tr->r);
	command(3, 0);
	break;
	
	case MINUS:
	generatecode(tr->child);
	command(4, 0);
	break;

	case LET:
	vars_in_level[++nest_level]=0;
	command(8, 0);
	command(6, 0);
	command(5, 0);
	generatecode(tr->l);
	generatecode(tr->r);
	--nest_level;
	command(10, 0);
	command(7, 0);
	command(9, 0);
	command(11, 0);
	break;

	case EQ:
	strcpy(varlist[nest_level][vars_in_level[nest_level]++],tr->token);
	generatecode(tr->child);
	break;

	case AND:
	generatecode(tr->l);
	generatecode(tr->r);
	break;
	}
}

void command(int commandId, int arg){
	switch (commandId){

	case 1:
	printf("Command 1 with arg '%d': Push argument to the stack.\n",arg);
	break;

	case 2:
	printf("Command 2: Pop two elements from the stack. Push the result of their summation to the stack.\n");
	break;

	case 3:
	printf("Command 3: Pop two elements from the stack. Push their product to the stack.\n");
	break;

	case 4:
	printf("Command 4: Pop one element from the stack. Push its inverse to the stack.\n");
	break;

	case 5:
	printf("Command 5: Increment 'top' by one.\n");
	break;

	case 6:
	printf("Command 6: Copy content of 'top' to 'base'.\n");
	break;

	case 7:
	printf("Command 7: Copy content of 'base' to 'top'.\n");
	break;

	case 8:
	printf("Command 8: Copy content of 'base' to the address contained in 'top'.\n");
	break;

	case 9:
	printf("Command 9: Copy element in stack which is pointed to by the address contained in 'top' to 'base'.\n");
	break;

	case 10:
	printf("Command 10: Extract top element from stack to 'temp'.\n");
	break;

	case 11:
	printf("Command 11: Push temp to the stack.\n");
	break;

	case 12:
	printf("Command 12: Copy content of 'base' to 'frame'\n");
	break;

	case 13:
	printf("Command 13: Copy element which is pointed to by 'frame' to 'frame'\n");
	break;

	case 14:
	printf("Command 14 with arg '%d': Add argument to the address contained in 'frame' and push the element in the resulting address to the stack\n",arg);
	break;



	}
}
