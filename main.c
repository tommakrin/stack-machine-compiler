#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "treedefs.h"

int main(int argc, char **argv){
/*	TREE *RootNode = malloc(sizeof(TREE));
	TREE *DummyNode = malloc(sizeof(TREE));
	DummyNode -> token = "0";
	DummyNode -> l = NULL;
	DummyNode -> r = NULL;
	DummyNode -> child = NULL;
	RootNode -> token = "+";
	RootNode -> l = DummyNode;
	RootNode -> r = DummyNode;
	RootNode -> child = NULL;

	printtree(RootNode);
*/
	yyparse();

	return 0;
}
