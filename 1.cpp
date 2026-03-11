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
 
struct all{
    int id;
    int mon;
    int cnt;
};

bool cmp(const all a,const all b){
    if(a.mon != b.mon){
        return a.mon > b.mon;
    }
    else if(a.cnt != b.cnt){
        return a.cnt > b.cnt;
    }
    else a.id < b.id;
}


void pre(){} 
 
void solve (){
    int n; cin >> n;
    vector<all>mp(n+1);
    for(int i = 1 ; i <= n ; i++){
        mp[i].id = i;
        int k; cin >> k;

        ll sum = 0;
        while(k--){
            int n,p; cin >> n >> p;
            mp[n].mon += p;
            sum += p;
            mp[n].cnt++;
        }
        mp[i].mon -= sum;
    }

    sort(all(mp),cmp);

    for(auto [x,y,z]:mp){
        if(x == 0) continue;
        double mon = y / 100.0;
        printf("%d %.2lf\n",x,mon);
    }
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