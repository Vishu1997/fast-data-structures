#include<stdlib.h>

struct avl_node{
	int value;
	struct avl_node * left;
	struct avl_node * right;
	int height;
};

typedef struct avl_node avl_node;

int getsize(avl_node *a){
	if(a==NULL)return 0;
	return getsize(a->left)+getsize(a->right)+1;
}

int getmax(avl_node *a){
	if(a==NULL)return -1;
	if(a->right!=NULL) return getmax(a->right);
	else return a->value;
}

int max(int a, int b){
	if(a>=b)
		return a;
	return b;
}

int height(avl_node * n){
	if(n == NULL)
		return 0;
	return n->height;
}

avl_node * newNode(int value){
	avl_node * n = malloc(sizeof(avl_node));
	n->value = value;
	n->left = NULL;
	n->right = NULL;
	n->height = 1;
	return n;
}

avl_node * rightRotate(avl_node * y){
	avl_node * x = y->left;
	avl_node * t = x->right;
	x->right = y;
	y->left = t;
	y->height = 1+max(height(y->left), height(y->right));
	x->height = 1+max(height(x->left), height(x->right));
	return x;
}

avl_node * leftRotate(avl_node *x){
	avl_node * y = x->right;
	avl_node * t = y->left;
	y->left = x;
	x->right = t;
	x->height = 1+max(height(x->left), height(x->right));
	y->height = 1+max(height(y->left), height(y->right));
	return y;
}

int getBalanceFactor(avl_node * n){
	if(n == NULL)
		return 0;
	return height(n->left)-height(n->right);
}

avl_node * insertNode(avl_node * n, int value,int *st){
	if(n == NULL){*st=1;
		return newNode(value);}
	if(value < n->value)
		n->left = insertNode(n->left, value,st);
	else if(value > n->value)
		n->right = insertNode(n->right, value,st);
	else
		return n;
	n->height = 1+ max(height(n->left), height(n->right));
	int bf = getBalanceFactor(n);
	if(bf > 1 && value < n->left->value)
		return rightRotate(n);
	if(bf < -1 && value > n->right->value)
		return leftRotate(n);
	if(bf > 1 && value > n->left->value){
		n->left = leftRotate(n->left);
		return rightRotate(n);
	}
	if(bf < -1 && value < n->right->value){
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}
	return n;
}

avl_node * minNode(avl_node * n){
	avl_node * curr = n;
	while(curr->left !=NULL)
		curr = curr->left;
	return curr;
}

avl_node * deleteNode(avl_node * n, int value,int *st){
	if(n == NULL)
		return n;
	if(value < n->value)
		n->left = deleteNode(n->left, value,st);
	else if(value > n->value)
		n->right = deleteNode(n->right, value,st);
	else{	*st=1;
		if(n->left == NULL || n->right == NULL){
			avl_node * t = n->left ? n->left : n->right;
			if(t == NULL){
				t = n;
				n = NULL;
			}
			else
				*n = *t;
			free(t);
		}
		else{
			avl_node * t = minNode(n->right);
			n->value = t->value;
			n->right = deleteNode(n->right, t->value,st);
		}
	}
	if(n == NULL)
		return n;
	n->height = 1+max(height(n->left), height(n->right));
	int bf = getBalanceFactor(n);
	if(bf > 1 && getBalanceFactor(n->left) >=0)
		return rightRotate(n);
	if(bf > 1 && getBalanceFactor(n->left) < 0){
		n->left = leftRotate(n->left);
		return rightRotate(n);
	}
	if(bf < -1 && getBalanceFactor(n->right) <=0)
		return leftRotate(n);
	if(bf < -1 && getBalanceFactor(n->right) > 0){
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}
	return n;
}

void preorder(avl_node *root){
	if(root!=NULL){
		printf("%d ", root->value);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(avl_node *root){
	if(root!=NULL){
		inorder(root->left);
		printf("%d ", root->value);
		inorder(root->right);
	}
}

avl_node * searchNode(avl_node *root, int value){
	if(root == NULL || (root->left == NULL && root->right == NULL && root->value != value))
		return NULL;
	if(root->value == value)
		return root;
	else if(root->value < value)
		return searchNode(root->right, value);
	else
		return searchNode(root->left, value);
}

/*avl_node * predecessor(avl_node *root, int value){
	avl_node * node = root, * prev = NULL;
	while(node != NULL){
		if(node->value == value)
			break;
		prev = node;
		if(node->value < value)
			node = node->right;
		else
			node = node->left;
	}
	return prev;
}*/

avl_node * replaceNode(avl_node *root, int value1, int value2,int *st){
	root = deleteNode(root, value1,st);
	return insertNode(root, value2,st);
}

void findPredSuc(avl_node *root, avl_node **pred, avl_node **suc, int value){
	avl_node *node = root;
	if(root == NULL)
		return;
	while(node != NULL){
		if(node->value == value){
			if(node->right){
				*suc = node->right;
				while((*suc)->left)
					*suc = (*suc)->left;
			}
			if(node->left){
				*pred = node->left;
				while((*pred)->right)
					*pred = (*pred)->right;
			}
			return;
		}
		else if(node->value < value){
			*pred = node;
			node = node->right;
		}
		else{
			*suc = node;
			node = node->left;
		}
	}
}
