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
    int n, C;
    cin >> n >> C;
    vector<ll> a(n);
    ll maxx = 0, sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        maxx = max(maxx, a[i]);
        sum += a[i];
    }
 
    auto check = [&](ll mid) -> bool {
        int cnt = 1;
        ll t = 0;
        for (ll num : a) {
            if (t + num > mid) {
                cnt++;
                t = num;
                if (cnt > C) return false;
            } else {
                t += num;
            }
        }
        return cnt <= C;
    };
 
    ll l = maxx, r = sum, ans = r;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
 
    cout << ans << endl;
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