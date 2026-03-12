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
    int n;cin >> n;
    stack<int>st;
    bool is = false;

    while(n--){
        int op;cin >> op;
        if(op == 1){
            int x; cin >> x;
            st.push(x);
        }
        else if(op == 2){
            int x; cin >> x;
            cout << st.top() << endl; st.pop();
            is = true;
        }
    }

    if(!is){
        cout << "Lazy Caiki!!!" << endl;
        return;
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