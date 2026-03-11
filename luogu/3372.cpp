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

class SegmentTree {
private:
    vector<ll> tree, lazy;
    int n;
    
    void build(const vector<ll>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            int l = 2 * node, r = 2 * node + 1;
            build(arr, l, start, mid);
            build(arr, r, mid+1, end);
            tree[node] = tree[l] + tree[r];
        }
    }
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                int l = 2 * node, r = 2 * node + 1;
                lazy[l] += lazy[node];
                lazy[r] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    void update_range(int node, int start, int end, int L, int R, ll val) {
        push(node, start, end);
        if (start > R || end < L) return;
        if (start >= L && end <= R) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        int l = 2 * node, r = 2 * node + 1;
        update_range(l, start, mid, L, R, val);
        update_range(r, mid+1, end, L, R, val);
        tree[node] = tree[l] + tree[r];
    }
    
    ll query_range(int node, int start, int end, int L, int R) {
        if (start > R || end < L) return 0;
        push(node, start, end);
        if (start >= L && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int l = 2 * node, r = 2 * node + 1;
        ll left_sum = query_range(l, start, mid, L, R);
        ll right_sum = query_range(r, mid+1, end, L, R);
        return left_sum + right_sum;
    }

public:
    SegmentTree(const vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n-1);
    }
    
    // 区间更新: [L, R] 范围内每个元素加上 val
    void update(int L, int R, ll val) {
        update_range(1, 0, n-1, L, R, val);
    }
    
    // 区间查询: 返回 [L, R] 范围内的元素和
    ll query(int L, int R) {
        return query_range(1, 0, n-1, L, R);
    }
};

void pre(){} 
 
void solve (){
    int n,m; cin >> n >> m;
    vector<ll> arr(n+1);
    for(int i = 1 ; i <= n ; i++) cin >> arr[i];
    SegmentTree st(arr);

    for(int i = 0 ; i < m ; i++){
        int op; cin >> op;
        if(op == 1){
            ll x,y,t; cin >> x >> y >> t;
            st.update(x,y,t);
        }
        else if(op == 2){
            int x,y; cin >> x >> y;
            cout << st.query(x,y) << endl;
        }
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