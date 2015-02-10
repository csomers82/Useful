#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ==============================================================
// ==============================================================
// DATA STRUCTURES
struct BST {
	struct BST * left;
	struct BST * right;
	char val;
};

struct Stack {
	struct SNode * sn;
};

struct SNode {
	struct SNode * next;
	struct BST * ret;	
	int ldone;
	int rdone;
};


// ==============================================================
// ==============================================================
// PROGRAM 

// ==============================================================
// STACK & NODE FUNCTION 
struct Stack *	stack_create(void);
void			stack_destroy(struct Stack * S);
struct BST *	stack_pop(struct Stack * S, int * lf, int * rf);
struct Stack *	stack_push(struct Stack * S, struct BST * bst);

void			stack_flags(struct Stack * S, int lf, int rf);

int				stack_isempty(struct Stack * S);
struct SNode *	stack_node_create(struct BST *);
void			stack_node_destroy(struct SNode * S);
// ==============================================================
// BST FUNCTIONS
struct BST *	tree_combine_with(struct BST ** lc, struct BST ** rc, char c);
struct BST *	tree_plant(char c);
void			tree_chop_down(struct BST * vic);
char	 		tree_visit(struct BST * node);
void			tree_print(struct BST * root, int depth);
void			tree_prefix(struct BST * node);
void			tree_infix(struct BST * node);
void			tree_postfix(struct BST * node);


// ==============================================================
// BST FUNCTIONS

// COMBINE
/* This function can be implemented a number of ways. In this case, it is both
 * a create function, a combine function, and clears the previous pointers
 */
struct BST * tree_combine_with(struct BST ** lc, struct BST ** rc, char c) {
	struct BST * root = tree_plant(c);
	if(!root) return NULL;
	root->left = *lc;
	root->right = *rc;
	*lc = NULL;
	*rc = NULL;
	return(root);
}
// ALLOC
struct BST * tree_plant(char c) {
	struct BST * root = malloc(sizeof(struct BST));
	if(!root) return NULL;
	root->val = c;
	root->left = NULL;
	root->right = NULL;
	return(root);
}
// DEALLOC
void tree_chop_down(struct BST * vic) {
	if(vic) {
		tree_chop_down(vic->left);
		tree_chop_down(vic->right);
		free(vic);
	}
}
// PRINT NODE
char tree_visit(struct BST * node) {
	//printf("%c", node->val);
	return(node->val);
}
// PRINT TREE
void tree_print(struct BST * root, int depth) {
	if(root) {
		printf("\n");
		int count; 
		for(count = 0; count <= depth; count++) {
			printf("\t");
		}
		printf("(%c)", root->val);
		tree_print(root->left, depth + 1);
		tree_print(root->right, depth + 1);
	}
}
// COUNT NODES
int tree_count(struct BST * bst) {
	if(bst) {
		return(tree_count(bst->left) + tree_count(bst->right) + 1);
	}
	return 0;
}


/* --------------------------------------------------------------\
 *  Traverse Functions
 *		currently set up to print out prefix, infix, and postfix,
 *		representations of an expression tree. It is to do this 
 *		with a stack, *non-recursively*. 
\* -------------------------------------------------------------*/
int check_visit(int how, int ldone, int rdone, struct BST * node) {
	if(!node) return(-1000);
	if((!node->left && !node->right)||
	(how == -1 && !ldone && !rdone) ||
	(how ==  0 &&  ldone && !rdone) ||
	(how ==  1 &&  ldone &&  rdone) ){
		return 1;
	}
	return 0;	
}

void tree_traverse(struct BST * root, int how) {
	// important objects
	struct BST * node = root;
	struct Stack * STACK = stack_create();
	// counters and flags
	int count = tree_count(root);
	char * expression = malloc(sizeof(char) * (1 + count));
	expression[count] = '\0';
	int ldone = 0;
	int rdone = 0;
	int letter = 0;
	// PROCESS
	while(!(node == root && rdone == 1 && ldone == 1)) {//(count--) {
		if(node) {
			// VISIT CONDITIONS
			if(check_visit(how, ldone, rdone, node)) { 
				if(letter < count) {
					expression[letter++] = tree_visit(node);
				}
			}
			// TRAVEL CONDITONS
			if((node->left || node->right) && (!ldone || !rdone)){
				if(!ldone && node->left) {
					stack_push(STACK, node);					
					stack_flags(STACK, 1, 0);
					node = node->left;
					ldone = 0; 
					rdone = 0;
				}
				else if(!rdone && node->right) {
					stack_push(STACK, node);
					stack_flags(STACK, 1, 1);
					node = node->right;
					ldone = 0; 
					rdone = 0;
				}
			}// RETURN CONDITIONS
			else {
				node = stack_pop(STACK, &ldone, &rdone);		
			}
		}
	}
	// TROUBLE SHOOT
	printf("%s\n", expression);
	// DEALLOCATE
	stack_destroy(STACK);
	free(expression);
}

// TRAVERSE [N__LR]
void tree_prefix(struct BST * root) {
	printf("Prefix  = ");
	tree_traverse(root, -1);
}
// TRAVERSE [L_N_R]
void tree_infix(struct BST * root) {
	printf("Infix   = ");
	tree_traverse(root, 0);
}
// TRAVERSE [LR__N]
void tree_postfix(struct BST * root) {
	printf("Postfix = ");
	tree_traverse(root, 1);
}


// ==============================================================
// STACK & NODE FUNCTION 

// ISEMPTY
int	stack_isempty(struct Stack * S) {
	return((!S->sn)? 1 : 0);
} 
// CREATE
struct Stack *	stack_create(void) {
	struct Stack * NEW = malloc(sizeof(struct Stack));
	NEW->sn = NULL;
	return(NEW);
}
// DESTROY
void stack_destroy(struct Stack * S) {
	if(!stack_isempty(S)) {
		stack_node_destroy(S->sn);
	}
	free(S);
}
// ALLOC NODE
struct SNode * stack_node_create(struct BST * bst) {
	struct SNode * nsn = malloc(sizeof(struct SNode));
	nsn->ret = bst;
	nsn->ldone = 0;
	nsn->rdone = 0;
	nsn->next = NULL;
	return(nsn);
}
// FREE NODE
void stack_node_destroy(struct SNode * sn) {	
	if(sn) {
		stack_node_destroy(sn->next);
		tree_chop_down(sn->ret);
		free(sn);
	}
}
// POP NODE
struct BST * stack_pop(struct Stack * S, int * L, int * R) {
	// assign and collect
	if(stack_isempty(S)) return NULL;
	struct SNode * old = S->sn; 
	struct BST * contents = S->sn->ret;
	*L = S->sn->ldone;
	*R = S->sn->rdone;
	// sever and return
	S->sn = old->next;
	old->next = NULL;
	old->ret = NULL;
	free(old);
	return(contents);
}
// PULL NODE
struct BST * stack_pull(struct Stack * S, int * L, int * R) {
	if(stack_isempty(S)) return NULL;
	return(S->sn->ret);	
}
// PUSH NODE
struct Stack * stack_push(struct Stack * S, struct BST * bst) {
	struct SNode * push = stack_node_create(bst);
	push->next = S->sn;// set current stack to 2nd pointer
	S->sn = push;// push new node onto top position
	return(S);
}
// STACK FLAGS
void stack_flags(struct Stack * S, int lf, int rf) {
	S->sn->ldone += lf;
	S->sn->rdone += rf;
}	
// ==============================================================
// ==============================================================
struct BST * function_tree(int tn);
void		 function_line(int ln);

int main(int argc, char * argv[]) {
	// [0] Validate and Parse
	if(argc >= 1) printf("%s ", argv[0]);
	if(argc >= 2) printf("%s ", argv[1]);
	if(argc != 2 || !isdigit(argv[1][0])) return EXIT_FAILURE;

	// [1] Build Expression Tree in Question
	int tn = atoi(argv[1]);
	struct BST * tree = function_tree(tn);	
	function_line(1);
	tree_print(tree, 0);
	function_line(0);
	if(!tree) return EXIT_FAILURE;

	// [2] Perform Tree Traversals
	printf("\n");
	tree_prefix(tree);
	tree_infix(tree);
	tree_postfix(tree);

	// [3] Deallocate and Return
	tree_chop_down(tree);

	return EXIT_SUCCESS ;
}

void function_line(int ln) {
	if(ln) printf("\n==============================================================");
	else   printf("\n--------------------------------------------------------------");
}
struct BST * function_tree(int tn) {
	struct BST * V = NULL;
	struct BST * W = NULL;
	struct BST * X = NULL;
	struct BST * Y = NULL;
	struct BST * Z = NULL;
	if(tn == 1) {
		W = tree_plant('A');
		X = tree_plant('B');
		Y = tree_combine_with(&W, &X, '+');
		Z = tree_plant('C');
		W = tree_combine_with(&Y, &Z, '-');	

		X = tree_plant('B');
		Y = tree_plant('A');
		Z = tree_combine_with(&X, &Y, '+');
		X = tree_plant('C');
		Y = tree_combine_with(&Z, &X, '$');

		X = tree_combine_with(&W, &Y, '-');
	}
	return(X);
}
