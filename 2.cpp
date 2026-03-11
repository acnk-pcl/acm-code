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
 
void pre(){} 
 
void solve (){
    int n; cin >> n;

    long double sum = 1.0L;
    long double t = 1.0L;
    for (int k = 1; k <= n; ++k) {
        t /= k;
        sum += t;
    }

    cout << fixed << setprecision(8) << (double)sum << '\n';
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