typedef enum nodeclass {letnode,eqnode,andnode,plusnode,timesnode,minusnode,
idnode,numnode} NODECLASS;

/* binary trees treated as abstract data type */
typedef struct tree TREE;

/* constructors */

/* leaves hold numbers or identifiers */
TREE *make_id_leaf(char *s);
TREE *make_number_leaf(int n);

/* plus and times tree have two children, minus trees have one child */
TREE *make_plus_tree(TREE *l,TREE *r);
TREE *make_times_tree(TREE *l,TREE *r);
TREE *make_minus_tree(TREE *child);

/* let trees hve two children, the definitions go in the right child and
   the expression in the left child */
TREE *make_let_tree(TREE *l,TREE *r);

/* eq trees hold an identifier and have one child which should hold the
   expression */
TREE *make_eq_tree(char *s,TREE *child);

/* and trees have two children, the left child should be an eq tree and
   the right child shuld be either an eq tree or an and tree */
TREE *make_and_tree(TREE *l,TREE *r);

/* if there is insufficient memory to make a tree a message is printed
   and the program will exit with status 2 */

/* selectors */
NODECLASS cass_of_tree(TREE t);

/* left_child and right_child should only be used on plus,times,let and
and trees */
TREE left_child(TREE t);
TREE right_child(TREE t);

/* only_child should only be used on minus trees and eq trees */
TREE only_child(TREE t);

/* the remaining selectors sould only ne used on the appropriate trees */
char *string_of_id_leaf(TREE t);
int num_of_number_leaf(TREE t);
char *string_of_eq_tree(TREE t);

/* if these selectors are always used correctly empty trees will never be
   encountered; no check is performed that a selector is applied to the
   correct kind of tree - if this is not the case t behaviour is
   unpredictable */
void printtree(TREE *tree);

