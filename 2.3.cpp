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

const int MAX = 1e4+5;

struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }

        if (siz[x] < siz[y]) {
            std::swap(x, y);
        }

        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

void pre(){
} 
 
void solve (){
    DSU dsu(MAX);
    int mx = -1;
    int n; cin >> n;
    for(int i = 0 ; i < n ; i++){
        int k; cin >> k;
        int tag; cin >> tag;
        if(tag > mx) mx = tag;
        for(int j = 1 ; j < k ; j++){
            int t; cin >> t;
            dsu.merge(tag,t);
            if(t > mx) mx = t;
        }
    }

    map<int,int>mp;
    int dif = 0 ;
    for(int i = 1 ; i <= mx ; i++){
        int f = dsu.find(i);
        if(!mp[f]) dif++;
        mp[f]++;
    }

    cout << mx << " " << dif << endl;

    int q; cin >> q;
    for(int i = 0 ; i < n ; i++){
        int x,y; cin >> x >> y;
        if(dsu.same(x,y)) cout << "Y" << endl;
        else cout << "N" << endl;
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