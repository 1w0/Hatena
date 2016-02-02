#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXM = 1e6 + 6;
const int MAXB = 1e3 + 3; // sqrt( MAXM )

struct Query{
    int ql, qr, id;
    int ans_freq, ans_cnt;
    void read(int _id){
        scanf("%d %d", &ql, &qr);
        id = _id;
    }
} qry[MAXM];
int pos[MAXN]; // pos[i]: which block i belongs to
bool cmp_lr(const Query &a, const Query &b){
    if( pos[ a.ql ] != pos[ b.ql ] ) return pos[ a.ql ] < pos[ b.ql ];
    return a.qr < b.qr;
}
bool cmp_id(const Query &a, const Query &b){
    return a.id < b.id;
}

int n, m;
int s[MAXN];

int freq[MAXN], cnt[MAXN], max_freq;
void update(int x, int v){
    if( v == 1 ){
        --cnt[ freq[x] ];
        ++freq[x];
        ++cnt[ freq[x] ];
        if( cnt[ max_freq + 1 ] > 0 ) ++max_freq;
    } else if( v == -1 ){
        --cnt[ freq[x] ];
        --freq[x];
        ++cnt[ freq[x] ];
        if( cnt[ max_freq ] == 0 ) --max_freq;
    }
}
void solve_MuoDuei(){
    int bs = (int)sqrt( n ) + 1; // block size
    for(int i = 1; i <= n; ++i)
        pos[i] = ( i - 1 ) / bs; // which block i would belong to
    sort( qry, qry + m, cmp_lr );
    int ql = 1, qr = 0;
    for(int i = 0; i < m; ++i){
        while( qr < qry[i].qr ) ++qr, update( s[qr], 1 );
        while( qr > qry[i].qr ) update( s[qr], -1 ), --qr;
        while( ql > qry[i].ql ) --ql, update( s[ql], 1 );
        while( ql < qry[i].ql ) update( s[ql], -1 ), ++ql;
        qry[i].ans_freq = max_freq;
        qry[i].ans_cnt = cnt[max_freq];
    }
    sort( qry, qry + m, cmp_id ); // reorder chronologically
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &s[i]);
    for(int i = 0; i < m; ++i)
        qry[i].read( i );
    solve_MuoDuei();
    for(int i = 0; i < m; ++i)
        printf("%d %d\n", qry[i].ans_freq, qry[i].ans_cnt);
    return 0;
}
