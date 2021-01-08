/* 
 * Binary search tree implementation in C.
 * Activity/lesson 4 from "C for Java Programmers"
 */

#include <stdlib.h>
#include <stdio.h>

struct node {
	int info;
	struct node* left;
	struct node* right;
};

/* allocate and initialize new node with an int value to store */
struct node* new_node(int val) {
	struct node* this = (struct node*)malloc(sizeof(struct node));
	if (this == NULL) {
		return NULL; // out of memory
	}

	this->info = val;
	this->left = NULL;
	this->right = NULL;

	return this;
}

/* recursively free this node and all children */
void free_node(struct node* this) {
	if (this == NULL) return;
	if (this->left == NULL && this->right == NULL) {
		free(this);
		return;
	}
	free_node(this->left);
	free_node(this->right);
}

/* print this node only */
void node_print(struct node* this) {
	if (this != NULL) {
		printf("Node[%d]", this->info);
	}
}

/* recursively print this node and all children, in-order traversal */
void node_treeprint(struct node* this) {
	if (this != NULL) {
		node_treeprint(this->left);
		node_print(this);
		node_treeprint(this->right);
	}
}

/* add a value to the binary search tree rooted at this node */
struct node* node_add(struct node* this, int val) {
	if (this == NULL) {
		this = new_node(val);
	} else if (val < this->info) {
		this->left = node_add(this->left, val);
	} else if (val > this->info) {
		this->right = node_add(this->right, val);
	} // no action taken if val is already in tree
	return this;
}

/* lookup a value using binary search tree return whether value is in tree */
int node_lookup(struct node* this, int val) {
	if (this == NULL) {
		return 0;
	} else if (val < this->info) {
		return node_lookup(this->left, val);
	} else if (val > this->info) {
		return node_lookup(this->right, val);
	} else {
		return 1;
	}
}

/* apply void function(int) referenced by fp to each value in sorted order */
void node_apply(struct node* this, void (*fp)(int)) {
	if (this != NULL) {
		node_apply(this->left, fp);
		(*fp)(this->info);
		node_apply(this->right, fp);
	}
}

struct tree {
	struct node* root;
};

struct tree* new_tree() {
	struct tree* this = (struct tree*)malloc(sizeof(struct tree));
	if (this == NULL) return this;
	this->root = NULL;
	return this;
}

void tree_print(struct tree* this) {
	node_treeprint(this->root);
}

void tree_add(struct tree* this, int val) {
	this->root = node_add(this->root, val);
}

int tree_lookup(struct tree* this, int val) {
	return node_lookup(this->root, val);
}

void tree_apply(struct tree* this, void (*fp)(int)) {
	node_apply(this->root, fp);
}

void callbackTest(int val) {
	printf("%d ", val);
}

int main(int argc, char* argv[]) {
	struct node* a = new_node(123);
	struct node* b = new_node(7);
	struct node* c = new_node(1);

	node_print(a);
	node_print(b);
	node_print(c);
	printf("\n");

	b->right = a;
	c->right = b;
	node_treeprint(c);
	printf("\n");

	struct node* d = node_add(NULL, 5);
	node_add(d, 6);
	node_add(d, 2);
	node_add(d, 1);
	node_add(d, 5);

	node_treeprint(d);
	printf("\n");

	struct tree* h = new_tree();
	tree_add(h, 1);
	tree_add(h, 2);
	tree_add(h, 4);
	tree_add(h, 3);
	tree_print(h);
	printf("\n");

	printf("3 in tree: %d\n5 in tree: %d\n", tree_lookup(h, 3), tree_lookup(h, 5));

	tree_apply(h, &callbackTest);
	printf("\n");
}
