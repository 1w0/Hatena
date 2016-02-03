#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 2;

struct line{
    ll slope, inter;
    ll value(ll x){ return x * slope + inter; }
};

deque<line> dq;
int n;
ll a, b, c;
ll p[MAXN + 5]; // prefix-sum
ll dp[MAXN + 5];

ll t(int i){ return a * p[i] * p[i] + b * p[i] + c; }
ll f(int i){ return a * p[i] * p[i] - b * p[i] + dp[i]; }
ll g(int i){ return p[i]; }
ll h(int i){ return -2 * a * p[i]; }

bool check(line x, line y, line z){
    return ( z.slope - y.slope ) * ( z.inter - x.inter )
        <= ( z.slope - x.slope ) * ( z.inter - y.inter );
}

int main(){
    int T; scanf("%d", &T);
    while( T-- ){
        while( !dq.empty() ) dq.pop_back();
        scanf("%d", &n);
        scanf("%lld %lld %lld", &a, &b, &c);
        for(int i = 1; i <= n; ++i){
            int x; scanf("%d", &x);
            p[i] = p[i - 1] + x;
        }
        dp[0] = t( 0 );
        dq.push_back( (line){ 0LL, 0LL } );
        for(int i = 1; i <= n; ++i){
            while( dq.size() >= 2 && dq[0].value( g(i) ) < dq[1].value( g(i) ) )
                dq.pop_front();
            dp[i] = dq[0].value( g(i) ) + t( i );
            line newl{ h( i ), f( i ) };
            while( dq.size() >= 2 && check( dq[ dq.size() - 2 ], dq[ dq.size() - 1 ], newl ) )
                dq.pop_back();
            dq.push_back( newl );
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}
