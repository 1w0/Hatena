#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;

struct Query{
    int ql, qr, id;
    int mex;
    void read(int _id){
        scanf("%d %d", &ql, &qr);
        --ql, --qr;
        id = _id;
    }
} qry[MAXM];
bool cmp_l(const Query &a, const Query &b){ // sort by l
    return a.ql < b.ql;
}
bool cmp_id(const Query &a, const Query &b){
    return a.id < b.id;
}

int vis[MAXN], init_mex[MAXN], next_idx[MAXN];
struct IntervalTree{
    int lb, rb, size, min_tag;
    IntervalTree *lc, *rc;
    IntervalTree(): min_tag(INF), lc(NULL), rc(NULL){}
    void push(){ // only the leaf is valid
        if( lb == rb ) return;
        if( min_tag == INF ) return;
        if( lc ) lc->min_tag = min( lc->min_tag, min_tag );
        if( rc ) rc->min_tag = min( rc->min_tag, min_tag );
        min_tag = INF;
    }
} *root;
void build(IntervalTree *t, int lb, int rb){
    t->lb = lb, t->rb = rb, t->size = rb - lb + 1;
    if( lb == rb ){
        t->min_tag = init_mex[lb];
        return;
    }
    int mid = ( lb + rb ) / 2;
    t->lc = new IntervalTree();
    t->rc = new IntervalTree();
    build( t->lc, lb, mid ); build( t->rc, mid + 1, rb );
}
void update(IntervalTree *t, int ql, int qr, int v){
    if( qr < t->lb || t->rb < ql ) return;
    if( ql <= t->lb && t->rb <= qr ){
        t->min_tag = min( t->min_tag, v );
        return;
    }
    t->push();
    update( t->lc, ql, qr, v ); update( t->rc, ql, qr, v );
}
int query(IntervalTree *t, int k){
    if( t->lb == t->rb ) return t->min_tag;
    t->push();
    int mid = ( t->lb + t->rb ) / 2;
    if( k <= mid ) return query( t->lc, k );
    return query( t->rc, k );
}

int n, m;
int a[MAXN];

void init(){
    memset( vis, -1, sizeof(vis) );
    for(int i = n - 1; i >= 0; --i)
        next_idx[i] = vis[ a[i] ], vis[ a[i] ] = i;
    memset( vis, 0, sizeof(vis) );
    int cur_mex = 0;
    for(int i = 0; i < n; ++i){
        if( a[i] < MAXN ) vis[ a[i] ] = 1; // not gonna use if too big
        while( vis[ cur_mex ] ) ++cur_mex;
        init_mex[i] = cur_mex;
    }
    // for(int i = 0; i < n; ++i) printf("%d ", init_mex[i]);
    root = new IntervalTree();
    build( root, 0, n - 1 );
}

void solve(){
    init();
    sort( qry, qry + m, cmp_l );
    int l = 0;
    for(int i = 0; i < m; ++i){
        while( l < qry[i].ql ){
            int nxt = next_idx[l]; // next same occurence
            if( nxt < 0 ) nxt = MAXN;
            if( l + 1 <= nxt - 1 ) update( root, l + 1, nxt - 1, a[l] );
            ++l;
        }
        qry[i].mex = query( root, qry[i].qr );
    }
    sort( qry, qry + m, cmp_id );
}

int main(){
    int T; scanf("%d", &T);
    while( T-- ){
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; ++i){
            scanf("%d", &a[i]);
            if( a[i] >= MAXN ) a[i] = MAXN - 1;
        }
        for(int i = 0; i < m; ++i)
            qry[i].read( i );
        solve();
        for(int i = 0; i < m; ++i)
            printf("%d\n", qry[i].mex);
    }
    return 0;
}
