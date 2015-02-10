#include <stdio.h>
#include <stdlib.h>

// ==============================================================
// ==============================================================
// DATA STRUCTURES
struct BST {
	struct BST * l;
	struct BST * r;
	char val;
};

struct Stack {
	struct SNode * sn;
};

struct SNode {
	struct SNode * next;
	struct BST * ret;	
};

// ==============================================================
// ==============================================================
// PROGRAM 
int main(int argc, char * argv[]) {
	
	
	return(EXIT_SUCCESS);
}



// ==============================================================
// BST FUNCTIONS
struct BST *	tree_combine(struct BST * lc, struct BST * rc);
struct BST *	tree_plant(char c);
void			tree_chop_down(struct BST * vic);
void			tree_visit(struct BST * node);
void			tree_prefix(struct BST * node);
void			tree_infix(struct BST * node);
void			tree_postfix(struct BST * node);
// ==============================================================
// STACK & NODE FUNCTION 
int				stack_isempty(struct Stack * S);
struct Stack *	stack_create(void);
void			stack_destroy(struct Stack * S);
struct Stack *	stack_node_create(struct BST *);
void			stack_node_destroy(struct SNode * S);
struct BST *	stack_pop(struct Stack * S);
struct Stack *	stack_push(struct Stack * S, struct BST * bst);

// ISEMPTY
int	stack_isempty(struct Stack * S) {
	return((!S->sn)? 1 : 0);
} 
// CREATE
struct Stack *	stack_create(void);
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
struct Stack *	stack_node_create(struct BST * bst) {
	struct SNode * nsn = malloc(sizeof(struct SNode));
	nsn->ret = bst;
	nsn->next = NULL;
	return(nsn);
}
// FREE NODE
void stack_node_destroy(struct SNode * sn) {	
	if(sn) {
		stack_node_destroy(sn->next);
		bst_destroy(sn->ret);
		free(sn);
	}
}
// POP NODE
struct BST * stack_pop(struct Stack * S) {
	if(stack_isempty(S)) return NULL;
	struct SNode * old = S->sn; 
	struct BST * contents = old->ret;// = S->sn;
	S->sn = old->next;
	old->next = NULL;
	old->ret = NULL;
	stack_node_destroy(old);
	return(contents);
}
// PUSH NODE
struct Stack * stack_push(struct Stack * S, struct BST * bst) {
	struct SNode * push = stack_node_create(bst);
	push->next = S->sn;// set current stack to 2nd pointer
	S->sn = push;// push new node onto top position
	return(S);
}

// ==============================================================
// ==============================================================
