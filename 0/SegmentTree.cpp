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

// 线段树模板 - 支持区间加、区间求和、懒标记
class SegmentTree {
private:
    vector<ll> tree, lazy;
    int n;
    
    void build(const vector<ll>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    void update_range(int node, int start, int end, int l, int r, ll val) {
        push(node, start, end);
        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update_range(2*node, start, mid, l, r, val);
        update_range(2*node+1, mid+1, end, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    ll query_range(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0;
        push(node, start, end);
        if (start >= l && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        ll left_sum = query_range(2*node, start, mid, l, r);
        ll right_sum = query_range(2*node+1, mid+1, end, l, r);
        return left_sum + right_sum;
    }

public:
    SegmentTree(const vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n-1);
    }
    
    // 区间更新: [l, r] 范围内每个元素加上 val
    void update(int l, int r, ll val) {
        update_range(1, 0, n-1, l, r, val);
    }
    
    // 区间查询: 返回 [l, r] 范围内的元素和
    ll query(int l, int r) {
        return query_range(1, 0, n-1, l, r);
    }
};

// 扩展版本：支持区间赋值（set）操作
class SegmentTreeSet {
private:
    vector<ll> tree, set_lazy;
    vector<bool> has_set;
    int n;
    
    void build(const vector<ll>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    void push(int node, int start, int end) {
        if (has_set[node]) {
            tree[node] = (end - start + 1) * set_lazy[node];
            if (start != end) {
                set_lazy[2*node] = set_lazy[node];
                set_lazy[2*node+1] = set_lazy[node];
                has_set[2*node] = true;
                has_set[2*node+1] = true;
            }
            has_set[node] = false;
        }
    }
    
    void update_set(int node, int start, int end, int l, int r, ll val) {
        push(node, start, end);
        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            set_lazy[node] = val;
            has_set[node] = true;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update_set(2*node, start, mid, l, r, val);
        update_set(2*node+1, mid+1, end, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    ll query_range(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0;
        push(node, start, end);
        if (start >= l && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        ll left_sum = query_range(2*node, start, mid, l, r);
        ll right_sum = query_range(2*node+1, mid+1, end, l, r);
        return left_sum + right_sum;
    }

public:
    SegmentTreeSet(const vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        set_lazy.resize(4 * n, 0);
        has_set.resize(4 * n, false);
        build(arr, 1, 0, n-1);
    }
    
    // 区间赋值: [l, r] 范围内所有元素设为 val
    void set_range(int l, int r, ll val) {
        update_set(1, 0, n-1, l, r, val);
    }
    
    // 区间查询: 返回 [l, r] 范围内的元素和
    ll query(int l, int r) {
        return query_range(1, 0, n-1, l, r);
    }
};

void pre(){} 

void solve (){
    // 示例用法
    int n = 5;
    vector<ll> arr = {1, 3, 5, 7, 9};
    
    // 基础线段树（支持区间加）
    SegmentTree st(arr);
    cout << "初始数组和: " << st.query(0, n-1) << endl;
    st.update(1, 3, 2); // [1,3] 区间加 2
    cout << "更新后 [1,3] 和: " << st.query(1, 3) << endl;
    
    // 扩展线段树（支持区间赋值）
    SegmentTreeSet st_set(arr);
    st_set.set_range(1, 3, 10); // [1,3] 区间设为 10
    cout << "赋值后 [1,3] 和: " << st_set.query(1, 3) << endl;
}

signed main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    pre();
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}