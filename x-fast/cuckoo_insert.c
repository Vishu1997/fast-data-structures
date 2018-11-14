#include<stdio.h>
#include<stdlib.h>

int h1(int x,int n){return x%n;}
int h2(int x,int n){return (x/n)%n;}

int main(){
    int n,i,j,k,p,d[]={56,23,13,57,24,8,34,2,3,75},*x,*y;
    //scanf("%d",&n);
    n=20;
    x=malloc(sizeof(int)*n);y=malloc(sizeof(int)*n);
    for(i=0;i<n;i++)x[i]=y[i]=-1;
    for(k=0;k<10;k++){p=d[k];while(1){
        i=h1(p,n);j=x[i];x[i]=p;
        if(j==-1)break;
        i=h2(j,n);p=y[i];y[i]=j;
    }
    for(i=0;i<n;i++)printf("%d, ",x[i]);putchar('\n');
    for(i=0;i<n;i++)printf("%d, ",y[i]);putchar('\n');putchar('\n');
    }
    return 0;
}