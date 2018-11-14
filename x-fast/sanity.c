#include<stdio.h>
#include<stdlib.h>
#include"xstruc.h"
int main(){
    int i,j,n=8;int x[]={17,26,192,93,12,432,14,1};
    char *d[]={"abcd","cdad","eiubd","ei","ffg","e","dw","yrs"};
    struct nlnd root;struct lnd *a;char *b;
    root.l.l=root.r.l=NULL;root.p=NULL;root.tl=root.tr=0;
    insrep(&root,30,(void*)"nkjo");
    b=findd(&root,30);
    printf("found:%s\n",b);
    a=min(&root,31);
    printf("min:%p\n",a);
    a=max(&root,31);
    printf("max:%p\n",a);
    a=succd(&root,20);
    printf("succ:%p\n",a);
    a=predd(&root,10);
    printf("pred:%p\n",a);
    insrep(&root,30,(void*)"boko");
    b=findd(&root,30);
    printf("found:%s\n",b);
    insrep(&root,20,(void*)"tw");
    b=findd(&root,20);
    printf("found:%s\n",b);
    return 0;
}