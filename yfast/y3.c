#include<stdio.h>
#include<stdlib.h>
#define xheight 32
#include"avl.h"
#include"xfast.h"


//yfast methods
void yfins(struct nlf *rt,int x){       //well test and implement now and later put that w/2 and w limits
    struct lf *t,*q;int i,j,k,st;
    t=xsucc3(rt,x);
    if(t==NULL)if((q=xpred(rt,x))!=NULL&&q->n<(xheight/2))
    {xinsert(rt,x);t=xfind(rt,x);t->root=insertNode(q->root,x,&st);t->n=getsize(t->root);xdel(rt,q->x);return;}
    //printf("succ found:%p\n",t);printf("succ %d:%d\n",x,t==NULL?-1:t->x);
    st=0;//printf("succ %d:%d\n",x,t==NULL?-1:t->x);
    if(t==NULL){xinsert(rt,x);return;}
    else t->root=insertNode(t->root,x,&st);
    if(st)t->n++;printf("st:%d,%d,%d\n",x,t->n,st);
    if(t->n>=xheight){printf("limit exceeded:%d\n",t->n);
        k=t->root->value;
        xinsert(rt,k);
        q=xfind(rt,k);
        q->root=t->root->left;
        q->root=insertNode(q->root,k,&st);
        q->n=getsize(q->root);
        t->root=t->root->right;
        t->n=getsize(t->root);
    }
}

void yfdel(struct nlf *rt,int x){
    struct lf *t,*q;int i,j,k,st;struct avl_node *e;
    t=xsucc3(rt,x);
    if(t==NULL)return;
    if(t->x==x){
        if(t->n==1){xdel(rt,x);free((void*)t->root);}
        k=getmax(t->root);
        xinsert(rt,k);q=xfind(rt,k);
        q->root=deleteNode(t->root,k,&st);
        }
    else{
        t->root=deleteNode(t->root,k,&st);
        if(st)t->n--;
    }
}

int main(){
    int p[]={1,2,3,4,5,6,7,8,9,9,10,23,124,13,53,1,23,456,2132,1342194,1232,453,14546,1234725},i,j,n;
    int p2[]={100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80};
    struct nlf rt;
    struct lf *a;
    rt.l.l=rt.r.l=NULL;rt.tl=rt.tr=0;rt.p=NULL;rt.lv=xheight;
    //for(i=400;i>0;i-=2)yfins(&rt,i);
    for(i=100;i<300;i+=2)yfins(&rt,i);
    a=xmin(&rt);
    while(a!=NULL){printf("%d:",a->x);putchar('\n');preorder(a->root);a=a->r;putchar('\n');}putchar('\n');
    return 0;
}