#include <bits/stdc++.h>
#include <ext/rope> // include this for rope
using namespace std;
using namespace __gnu_cxx; // and this
const int MAXN = 5e4 + 4;

int d;
int vcnt;
rope<char> version[MAXN]; // ropes that consists of char
int n;
char str[MAXN];

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        int op, v, p, c; scanf("%d", &op);
        if( op == 1 ){
            version[ ++vcnt ] = version[ vcnt - 1 ];
            scanf("%d%s", &p, str);
            p -= d;
            version[ vcnt ].insert( p, str );
        } else if( op == 2 ){
            version[ ++vcnt ] = version[ vcnt - 1 ];
            scanf("%d%d", &p, &c);
            p -= d, c -= d;
            version[ vcnt ].erase( p - 1, c );
        } else{
            scanf("%d%d%d", &v, &p, &c);
            v -= d, p -= d, c -= d;
            rope<char> ans = version[ v ].substr( p - 1, c );
            cout << ans << endl;
            d += count( ans.begin(), ans.end(), 'c' );
        }
    }
    return 0;
}
