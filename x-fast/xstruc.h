
union ptr{
    struct nlnd * nl;
    struct lnd *l;
};

struct nlnd{
    union ptr l,r;
    struct nlnd *p;char tl,tr;
};

struct lnd{
    struct lnd *l,*r;
    struct nlnd *p;
    int v;void *d;
};

struct lnd *getlnd(struct lnd *l,struct lnd *r,struct nlnd *p,void *d,int v){
    struct lnd *o;
    o=malloc(sizeof(struct lnd));
    o->l=l;o->r=r;o->p=p;o->d=d;o->v=v;
    return o;
}

struct nlnd *getnlnd(struct lnd *l,struct lnd *r,struct nlnd *p,char tl,char tr){
    struct nlnd *o;
    o=malloc(sizeof(struct nlnd));
    o->l.l=l;o->r.l=r;o->p=p;o->tl=tl;o->tr=tr;
    return o;
}

void *find(struct nlnd *r,int x,int o);
struct lnd *succ(struct nlnd *r,int x,int o);
struct lnd *pred(struct nlnd *r,int x,int o);
struct lnd *min(struct nlnd *r,int o);
struct lnd *max(struct nlnd *r,int o);
//void delete(struct nlnd *r,int x)

struct lnd *min(struct nlnd *r,int o){
    if(r==NULL)return NULL;
    if(o==0){if(r->tl)return r->l.l;return r->r.l;}
    if(r->tl)return min(r->l.nl,o-1);
    return min(r->r.nl,o-1);
}

struct lnd *max(struct nlnd *r,int o){
    if(r==NULL)return NULL;
    if(o==0){if(r->tr)return r->r.l;return r->l.l;}
    if(r->tr)return min(r->r.nl,o-1);
    return min(r->l.nl,o-1);
}

void *find(struct nlnd *r,int x,int o){
    if(r==NULL)return NULL;
    int a;
    a=x&(1<<o);
    if(a){if(!r->tr)return NULL;if(o==0)return r->l.l->d;return find(r->l.nl,x,o-1);}
    else {if(!r->tl)return NULL;if(o==0)return r->r.l->d;return find(r->r.nl,x,o-1);}
}


void *findd(struct nlnd *r,int x){
    if(r==NULL)return NULL;
    int i,j;
    for(i=31;i>0;i--){
        if(x&(1<<i)){
            if(r->tr)r=r->r.nl;
            else return NULL;
        }
        else{
            if(r->tl)r=r->l.nl;
            else return NULL;
        }
    }
    if(x%2){if(r->tr)return r->r.l->d;}
    else {if(r->tl)return r->l.l->d;}
    return NULL;
}

struct lnd *succ(struct nlnd *r,int x,int o){int a;
    if(r==NULL)return NULL;
    if(o==0){a=x%2;
        if(a&&r->tr)return r->r.l->r;return r->r.l;
    }
    a=x&(1<<o);
    if(a){if(!r->tr)return r->r.l;return succ(r->r.nl,x,o-1);}
    else {if(r->tl)return succ(r->l.nl,x,o-1);
    if(r->tr)return pred(r->r.nl,x,o-1);
    return r->r.l;}
}

struct lnd *succd(struct nlnd *r,int x){int i,j,k;struct nlnd *t;
    if(r==NULL)return NULL;t=r;
    for(i=31;i>0;i--){
        if(x&(1<<i)){
            if(t->tr)t=t->r.nl;else return t->r.l;
        }
        else{
            if(t->tl)t=t->l.nl;
            else {if(t->l.nl!=NULL)return t->l.l->r;
            return min(t->r.nl,i-1);}
        }
    }
    if(x%2){
        if(t->tr)return t->r.l->r;return t->r.l;
    }
    else{
        return t->r.l;
    }
}

struct lnd *predd(struct nlnd *r,int x){int i,j,k;struct nlnd *t;
    if(r==NULL)return NULL;t=r;
    for(i=31;i>0;i--){
        if((x&(1<<i))==0){
            if(t->tl)t=t->l.nl;else return t->l.l;
        }
        else{
            if(t->tr)t=t->r.nl;
            else {if(t->r.nl!=NULL)return t->r.l->l;
            return max(t->l.nl,i-1);}
        }
    }
    if(x%2){
        if(t->tl)return t->l.l->l;return t->l.l;
    }
    else{
        return t->l.l;
    }
}


struct lnd *pred(struct nlnd *r,int x,int o){int a;
    if(r==NULL)return NULL;
    if(o==0){a=x%2;
        if(a==0&&r->tl)return r->l.l->l;return r->l.l;
    }
    a=x&(1<<o);
    if(a==0){if(!r->tl)return r->l.l;return pred(r->l.nl,x,o-1);}
    else {if(r->tr)return pred(r->r.nl,x,o-1);
    if(r->tl)return succ(r->l.nl,x,o-1);
    return r->l.l;}
}

void insrep(struct nlnd *r,int x,void *d){struct lnd *pr,*sc,*y;struct nlnd *t;int i,j;
    if(r==NULL)return;pr=sc=NULL;
    pr=predd(r,x);
    sc=succd(r,x);
    t=r;
    for(i=31;i>0;i--){
        if(x&(1<<i)){if(t->tr)t=t->r.nl;
        else {t->tr=1;t->r.nl=getnlnd(pr,sc,t,0,0);t=t->r.nl;}}
        else{if(t->tl)t=t->l.nl;
        else {t->tl=1;t->l.nl=getnlnd(pr,sc,t,0,0);t=t->l.nl;}}
    }
    if(x%2){
        if(t->tr){t->r.l->d=d;return;}
        else{y=t->r.l=getlnd(pr,sc,t,d,x);t->tr=1;}
    }
    else{
        if(t->tl){t->l.l->d=d;return;}
        else{y=t->l.l=getlnd(pr,sc,t,d,x);t->tl=1;}
    }
    if(pr!=NULL){pr->r=y;t=pr->p;while(t!=NULL){if(t->r.l!=sc)break;t->r.l=y;}}
    if(sc!=NULL){sc->l=y;t=sc->p;while(t!=NULL){if(t->l.l!=pr)break;t->l.l=y;}}
}