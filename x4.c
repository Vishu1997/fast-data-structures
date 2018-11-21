#include<stdio.h>
#include<stdlib.h>

//height of tree in number of bits
#define height 31

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
    o->l=pr;o->r=sc;o->p=p;o->x=x;o->d=d;
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

struct lf *succ2(struct nlf *rt,int x){
    int i,n;struct nlf *t;
    if(rt==NULL)return NULL;
    if(rt->tl==0&&rt->tr==0)return NULL;
    n=rt->lv;t=rt;
    for(i=n;i>1;i--){printf("cmp %d with %d\n",x,1<<(i-1));
        if(x&(1<<(i-1))){
            if(t->tr)t=t->r.nl;else {printf("pathx %d\n",t->r.l->x);return t->r.l;}
        }
        else{
            if(t->tl)t=t->l.nl;else {if(t->tr)return min(t->r.nl); else return t->r.l;}
        }
    }
    if(x&1){if(t->tr)return t->r.l->r;else return t->r.l;}
    else return t->r.l;
}

struct nlf *build(int x,int h,struct lf *sc,struct lf *pr,struct nlf *p,void *d,struct lf **y){
    struct nlf rt,*t;int i;t=getnlf(pr,sc,p,0,0,i);
    for(i=h;i>1;i--){
        if(x&(1<<(i-1))){t->tr=1;t->r.nl=getnlf(pr,sc,t,0,0,i-1);t=t->r.nl;}
        else{t->tl=1;t->l.nl=getnlf(pr,sc,t,0,0,i-1);t=t->l.nl;}
    }
    if(x&1){t->tr=1;*y=t->r.l=getlf(pr,sc,t,x,d);}
    else {t->tl=1;*y=t->l.l=getlf(pr,sc,t,x,d);}
}

//insert or replace a node with new data 
void insert(struct nlf *rt,int x,void *d){
    int i,j,k,n;struct nlf *t;struct lf *pr,*sc,*y;
    n=rt->lv;t=rt;pr=pred(rt,x);sc=succ(rt,x);
    switch(x){case 13:case 23:case 10:case 124://succ2(rt,x);
    printf("inserting:%d pr:%d sc:%d",x,pr==NULL?-1:pr->x,sc==NULL?-1:sc->x);getchar();}
    for(i=n;i>1;i--){
        if(x&(1<<(i-1))){
            if(t->tr)t=t->r.nl;
            else {t->tr=1;t->r.nl=build(x,i-1,sc,pr,t,d,&y);repl(t->l.nl,y,sc);trepl(sc,y,pr);return;}
        }
        else{
            if(t->tl)t=t->l.nl;
            else {t->tl=1;t->l.nl=build(x,i-1,sc,pr,t,d,&y);repr(t->r.nl,y,pr);trepr(pr,y,sc);return;}
        }
    }




    if(x&1){
        if(t->tr){t->r.l->d=d;return;}else {t->tr=1;y=getlf(pr,sc,t,x,d);t->r.l=y;y->r=pr->r;pr->r=y;
        if(sc!=NULL)sc->l=y;}
    }
    else{
        if(t->tl){t->l.l->d=d;return;}else {t->tl=1;y=getlf(pr,sc,t,x,d);t->l.l=y;y->l=sc->l;sc->l=y;
        if(pr!=NULL)pr->r=y;}
    }
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
    if(a==NULL)return;printf("found\n");
    pr=a->l;sc=a->r;printf("sc:%p pr:%p\n",sc,pr);
    t=a->p;
    if(x&1){t->tr=0;t->r.l=sc;}else{t->tl=0;t->l.l=pr;}b=t->p;
    if((t->tr+t->tl)==0){free((void*)t);printf("l:%d\n",i);
    while(t!=NULL&&i<height){i++;t=b;b=b->p;
        if(x&(1<<i)){t->tr=0;t->r.l=sc;}
        else{t->tl=0;printf("el:%d\n",t->tr);t->l.l=pr;}
        printf("l:%d\n",i);
        if((t->tr+t->tl)==0)free((void*)t);
        else break;
    }}
    //if(pr!=NULL){pr->r=sc;t=pr->p;while(t!=NULL){if((t->tr==0)&&(t->r.l==a))t->r.l=sc;t=t->p;}}
    //if(sc!=NULL){sc->l=pr;t=sc->p;while(t!=NULL){if((t->tl==0)&&(t->l.l==a))t->l.l=pr;t=t->p;}}
    if(pr!=NULL){pr->r=sc;t=pr->p;while(t!=NULL){if(t->tr==0)t->r.l=sc;else break;t=t->p;}}
    if(sc!=NULL){sc->l=pr;t=sc->p;while(t!=NULL){if(t->tl==1)t->l.l=pr;else break;t=t->p;}}
    free((void*)a);
}

void printwt(struct nlf *rt){
    if(rt==NULL)return;
    printf("%p ,\n",rt);
    if(rt->lv==1){
        if(rt->tl)printf("%p,%d ,\n",rt->l.l,rt->l.l->x);
        if(rt->tr) printf("%p,%d ,\n",rt->r.l,rt->r.l->x);
    }
    else{
        if(rt->tl)printwt(rt->l.nl);
        if(rt->tr)printwt(rt->r.nl);
    }
}

int main(){
    int p[]={1,2,3,4,5,6,7,8,9,9,10,23,124,13,53,1},i,j,n;
    char *dat[]={"jfnj","domfk","fedd","wwxc","wuiwgue","auvvxgh","wjhhgv","ped","eobbd"};struct nlf rt;
    struct lf *a;
    rt.l.l=rt.r.l=NULL;rt.tl=rt.tr=0;rt.p=NULL;rt.lv=height;
    for(i=10;i<14;i++)build(&rt,p[i],NULL);
    
    //del(&rt,2);
    a=min(&rt);
    while(a!=NULL){printf("%d,",a->x);a=a->r;}putchar('\n');
    //printf("ls:%d",succ2(&rt,940)->x);
    printwt(&rt);
    return 0;
}