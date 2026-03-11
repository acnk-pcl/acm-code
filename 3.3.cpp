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
    vector<int>z;
};

void pre(){} 
 
void solve (){
    int n,m; cin >> n >> m;
    vector<all>s(n+1);
    for(int i = 0 ; i < n ; i++){
        int x,y; cin >> x >> y;
        s[x].z.pb(y);
        s[y].z.pb(x);
    }

    vi ans(n+1);
    
    for(int i = 1 ; i <= n ; i++){
        vector<int> vis(n+1,0);
        int cnt = 0,sum = 0;

        deque<int>t;
        t.pb(i);
        while(cnt <= 5){
            deque<int>temp;
            for(auto q:t){
                for(auto p:s[q].z){
                    if(vis[p]|| p < 1 || p > n) continue;

                    temp.pb(p);
                    sum += 1;
                    vis[p]++;
                }
            }
            t = temp;
            cnt++;
        }
        ans[i] = sum;
    }

    for(int i = 1 ; i <= n ; i++){
        double bb = ans[i] * 100.0 / n;
        printf("%d: %.2lf%%",i,bb);
        //printf("   %d",ans[i]);
        printf("\n");
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