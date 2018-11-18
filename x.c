#include<stdio.h>
#include<stdlib.h>

//height of tree in number of bits
#define height 32

//structures
union nxpt{
    struct nlf *nl;
    struct lf *l;
};

struct nlf{
    int lv;char tl,tr;
    struct nlf *p;
    union nxpt l,r;
};

struct lf{
    int x;void *d;
    struct lf *l,*r;
    struct nlf *p;
};
//resource allocators
struct nlf *getnlf(struct lf *pr,struct lf *sc,struct nlf *p,char tl,char tr,int lv){
    struct nlf *o;o=malloc(sizeof(struct nlf));
    o->l.l=pr;o->r.l=sc;o->tl=tl;o->tr=tr;o->p=p;o->lv=lv;
    return o;
}

struct lf *getlf(struct lf *pr,struct lf *sc,struct nlf *p,int x,void *d){
    struct lf *o;o=malloc(sizeof(struct lf));
    o->l=pr;o->r=sc;o->p=p;o->x=x;o->d=d;printf("x:%d\n",x);
    return o;
}


//minimum of a tree
struct lf *min(struct nlf *rt){
    int i,n;struct nlf *t;
    if(rt==NULL)return NULL;
    n=rt->lv;t=rt;
    for(i=n;i>1;i--){
        if(t->tl)t=t->l.nl;
        else t=t->r.nl;
    }
    if(t->tl)return t->l.l;else return t->r.l;
}

//maximum of a tree
struct lf *max(struct nlf *rt){
    int i,n;struct nlf *t;
    if(rt==NULL)return NULL;
    n=rt->lv;t=rt;
    for(i=n;i>1;i--){
        if(t->tr)t=t->r.nl;
        else t=t->l.nl;
    }
    if(t->tr)return t->r.l;else return t->l.l;
}


//predecessor of a data structure NULL if absent
struct lf *pred(struct nlf *rt,int x){
    int i,n;struct nlf *t;
    if(rt==NULL)return NULL;
    if(rt->tl==0&&rt->tr==0)return NULL;
    n=rt->lv;t=rt;
    for(i=n;i>1;i--){
        if(x&(1<<(i-1))){
            if(t->tr)t=t->r.nl;else {if(t->tl)return max(t->l.nl);else return t->l.l;}
        }
        else{
            if(t->tl)t=t->l.nl;else return t->l.l;
        }
    }

    if(x&1)return t->l.l;
    else {if(t->tl)return t->l.l->l;else return t->l.l;}
}

struct lf *succ(struct nlf *rt,int x){
    int i,n;struct nlf *t;
    if(rt==NULL)return NULL;
    if(rt->tl==0&&rt->tr==0)return NULL;
    n=rt->lv;t=rt;
    for(i=n;i>1;i--){
        if(x&(1<<(i-1))){
            if(t->tr)t=t->r.nl;else return t->r.l;
        }
        else{
            if(t->tl)t=t->l.nl;else {if(t->tr)return min(t->r.nl); else return t->r.l;}
        }
    }
    if(x&1){if(t->tr)return t->r.l->r;else return t->r.l;}
    else return t->r.l;
}


//insert or replace a node with new data 
void build(struct nlf *rt,int x,void *d){
    int i,j,k,n;struct nlf *t;struct lf *pr,*sc,*y;
    n=rt->lv;t=rt;pr=pred(rt,x);sc=succ(rt,x);
    for(i=n;i>1;i--){
        if(x&(1<<(i-1))){
            if(t->tr)t=t->r.nl;else {t->tr=1;t->r.nl=getnlf(pr,sc,t,0,0,i-1);t=t->r.nl;}
        }
        else{
            if(t->tl)t=t->l.nl;else {t->tl=1;t->l.nl=getnlf(pr,sc,t,0,0,i-1);t=t->l.nl;}
        }
    }
    if(x&1){
        if(t->tr){t->r.l->d=d;return;}else {t->tr=1;y=getlf(pr,sc,t,x,d);t->r.l=y;}
    }
    else{
        if(t->tl){t->l.l->d=d;return;}else {t->tl=1;y=getlf(pr,sc,t,x,d);t->l.l=y;}
    }
    //y->l=pr;y->r=sc;
    if(pr!=NULL){pr->r=y;t=pr->p;while(t!=NULL){if((t->tr==0)&&(t->r.l==sc))t->r.l=y;t=t->p;}}
    if(sc!=NULL){sc->l=y;t=sc->p;while(t!=NULL){if((t->tl==0)&&(t->l.l==pr))t->l.l=y;t=t->p;}}
}

//given x return its respective node pointer (just supporter function otherwise NULL)
struct lf *find(struct nlf *rt,int x){
    int i,j,k,n;struct nlf *t;
    if(rt==NULL)return NULL;
    if(rt->tl==0&&rt->tr==0)return NULL;
    n=rt->lv;t=rt;
    for(i=n;i>1;i--){
        if(x&(1<<(i-1))){if(t->tr)t=t->r.nl;else return NULL;}
        else {if(t->tl)t=t->l.nl;else return NULL;}
    }
    if(x&1){if(t->tr)return t->r.l;}
    else{if(t->tl)return t->l.l;}
    return NULL;
}

//given x retrieve its data or NULL
void *dict(struct nlf *rt,int x){
    struct lf *t;
    t=find(rt,x);
    if(t==NULL)return NULL;
    return t->d;
}


//delete a node (still untested)
void del(struct nlf *rt,int x){
    int i=0;struct nlf *t,*b;struct lf *pr,*sc,*a;
    a=find(rt,x);
    if(a==NULL)return;
    pr=a->l;sc=a->r;t=a->p;
    t=a->p;
    if(x&1){t->tr=0;t->r.l=sc;}else{t->tl=0;t->l.l=pr;}b=t->p;
    if((t->tr+t->tl)==0){free((void*)t);
    while(t!=NULL&&i<height){i++;t=b;
        if(x&(1<<i)){t->tr=0;t->r.l=sc;}
        else{t->tl=0;t->l.l=pr;}b=t->p;
        if((t->tr+t->tl)==0)free((void*)t);
        else break;
    }}

    if(pr!=NULL){pr->r=sc;t=pr->p;while(t!=NULL){if((t->tr==0)&&(t->r.l==a))t->r.l=sc;t=t->p;}}
    if(sc!=NULL){sc->l=pr;t=sc->p;while(t!=NULL){if((t->tl==0)&&(t->l.l==a))t->l.l=pr;t=t->p;}}
}

int main(){
    int p[]={74,18,183,2,29,185,940,100034,10},i,j,n=9;
    char *dat[]={"jfnj","domfk","fedd"};struct nlf rt;
    rt.p=NULL;rt.lv=height;rt.r.nl=rt.l.nl=NULL;rt.tl=rt.tr=0;
    //for(i=0;i<n;i++)build(&rt,p[i],dat[i]);
    build(&rt,24,(void*)"abcd");
    build(&rt,30,(void*)"neww");
    printf("succ:%d\n",succ(&rt,22)->x);printf("pred:%d\n",pred(&rt,31)->x);
    return 0;
}