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
// 使用 l, r 表示左右子节点 (l = 2*node, r = 2*node+1)
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
            int l = 2 * node, r = 2 * node + 1;
            build(arr, l, start, mid);
            build(arr, r, mid+1, end);
            tree[node] = tree[l] + tree[r];
        }
    }
    
    void push(int node, int start, int end) {
        if (has_set[node]) {
            tree[node] = (end - start + 1) * set_lazy[node];
            if (start != end) {
                int l = 2 * node, r = 2 * node + 1;
                set_lazy[l] = set_lazy[node];
                set_lazy[r] = set_lazy[node];
                has_set[l] = true;
                has_set[r] = true;
            }
            has_set[node] = false;
        }
    }
    
    void update_set(int node, int start, int end, int L, int R, ll val) {
        push(node, start, end);
        if (start > R || end < L) return;
        if (start >= L && end <= R) {
            set_lazy[node] = val;
            has_set[node] = true;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        int l = 2 * node, r = 2 * node + 1;
        update_set(l, start, mid, L, R, val);
        update_set(r, mid+1, end, L, R, val);
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
    SegmentTreeSet(const vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        set_lazy.resize(4 * n, 0);
        has_set.resize(4 * n, false);
        build(arr, 1, 0, n-1);
    }
    
    // 区间赋值: [L, R] 范围内所有元素设为 val
    void set_range(int L, int R, ll val) {
        update_set(1, 0, n-1, L, R, val);
    }
    
    // 区间查询: 返回 [L, R] 范围内的元素和
    ll query(int L, int R) {
        return query_range(1, 0, n-1, L, R);
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