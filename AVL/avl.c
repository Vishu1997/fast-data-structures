#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

int main(){
	avl_node * root = NULL;
	int t;
	scanf("%d", &t);
	int n;
	for(int i=0;i<t;i++){
		scanf("%d", &n);
		root = insertNode(root, n);
	}
	//for(int i=1;i<8;i++)
		//root = insertNode(root, i);
	//root = insertNode(root, 25);
	/*root = insertNode(root, 50); 
    root = insertNode(root, 30); 
    root = insertNode(root, 70); 
    root = insertNode(root, 20); 
    root = insertNode(root, 60); 
    root = insertNode(root, 40); 
    root = insertNode(root, 80); 
    //root = insertNode(root, 1); 
    //root = insertNode(root, 2);
	preorder(root);
	//root = deleteNode(root, 10);
	//root = replaceNode(root, 10, 12);
	printf("\n");
	//preorder(root);
	inorder(root);
	avl_node * node = searchNode(root, 100);
	/*if(node == NULL)
		printf("Not Present\n");
	else
		printf("Present\n");
	avl_node *pred = NULL, *suc = NULL;
	findPredSuc(root, &pred, &suc, 65);
	if(pred != NULL)
		printf("%d\n", pred->value);
	if(suc != NULL)
		printf("%d\n", suc->value);*/
	inorder(root);
}
