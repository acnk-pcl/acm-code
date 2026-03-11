#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
 
vi a;

void pre(){
    int MAX = 1e9+1;
    for(int i = 0 ; i <= sqrt(MAX) ; i++){
        a.pb(i*i);
    }
} 
 
void solve (){
    int x,l,r; cin >> x >> l >> r;

    for(auto p:a){
        if(p % x == 0){
            int m = p / x;
            if(l <= m and l <= r){
                cout << m << endl;
                return;
            }
        }
    }
    cout << -1 << endl;
}
 
signed main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    pre();
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}