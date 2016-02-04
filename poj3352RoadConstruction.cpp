#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 1e3 + 3;
const int MAXM = 5e3 + 3;

int n, m;
vector<int> G[MAXN];
int dfs_clock;
int pre[MAXN], low[MAXN];
map<pii, bool> is_bridge;

int dfs(int u, int fa){
    int lowu = pre[u] = ++dfs_clock;
    for(int v: G[u]){
        if( v == fa ) continue;
        if( !pre[v] ){
            int lowv = dfs( v, u );
            lowu = min( lowu, lowv );
            if( lowv == pre[v] )
                is_bridge[ pii( u, v ) ] = is_bridge[ pii( v, u ) ] = true;
        } else if( pre[v] < pre[u] ) // back edge
            lowu = min( lowu, pre[v] );
    }
    return low[u] = lowu;
}

int bccno[MAXN], bcc_cnt, fvis[MAXN];
void floodfill(int _u, int col){
    queue<int> q; q.push( _u );
    while( !q.empty() ){
        int u = q.front(); q.pop();
        bccno[u] = bcc_cnt;
        fvis[u] = 1;
        for(int v: G[u]) if( !fvis[v] )
            if( !is_bridge.count( pii( u, v ) ) )
                q.push( v );
    }
}
void tarjan(int n){
    dfs_clock = 0;
    memset( pre, 0, sizeof(pre) );
    memset( low, 0, sizeof(low) );
    is_bridge.clear();
    dfs( 1, -1 );
    bcc_cnt = 0;
    memset( fvis, 0, sizeof(fvis) );
    for(int i = 1; i <= n; ++i) if( !fvis[i] )
        floodfill( i, bcc_cnt++ );
}

int deg[MAXN];
void solve(){
    memset( deg, 0, sizeof(deg) );
    for(int u = 1; u <= n; ++u)
        for(int v: G[u]){
            int bu = bccno[u], bv = bccno[v];
            if( bu != bv ) ++deg[bu], ++deg[bv];
        }
    int leaf_cnt = 0;
    for(int i = 1; i <= bcc_cnt; ++i)
        if( deg[i] == 2 )
            ++leaf_cnt;
    printf("%d\n", ( leaf_cnt + 1 ) / 2);
}

int main(){
    int T; scanf("%d", &T);
    while( T-- ){
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) G[i].clear();
        for(int i = 0; i < m; ++i){
            int x, y; scanf("%d %d", &x, &y);
            G[x].push_back( y );
            G[y].push_back( x );
        }
        tarjan( n );
        solve();
    }
    return 0;
}
