#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct Node {
    int min_val;
    ll gcd_val;
};

class SegmentTree {
public:
    int n;
    vector<Node> tree;
    vector<int> a;

    SegmentTree(int size, const vector<int>& arr) {
        n = size;
        a = arr;
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    Node combine(const Node& left, const Node& right) {
        Node parent;
        parent.min_val = min(left.min_val, right.min_val);
        if(left.min_val == right.min_val){
            parent.gcd_val = gcd(left.gcd_val, right.gcd_val);
        }
        else{
            if(left.min_val < right.min_val){
                parent.gcd_val = gcd(left.gcd_val, right.gcd_val);
                parent.gcd_val = gcd(parent.gcd_val, (ll)(right.min_val - left.min_val));
            }
            else{
                parent.gcd_val = gcd(left.gcd_val, right.gcd_val);
                parent.gcd_val = gcd(parent.gcd_val, (ll)(left.min_val - right.min_val));
            }
        }
        return parent;
    }

    void build(int node, int l, int r){
        if(l == r){
            tree[node].min_val = a[l];
            tree[node].gcd_val = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        tree[node] = combine(tree[2*node], tree[2*node+1]);
    }

    Node query(int node, int l, int r, int ql, int qr){
        if(ql > r || qr < l){
            return {INT32_MAX, 0};
        }
        if(ql <= l && r <= qr){
            return tree[node];
        }
        int mid = (l + r) / 2;
        Node left = query(2*node, l, mid, ql, qr);
        Node right = query(2*node+1, mid+1, r, ql, qr);
        if(left.min_val == INT32_MAX){
            return right;
        }
        if(right.min_val == INT32_MAX){
            return left;
        }
        return combine(left, right);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    while(t--){
        int n, q;
        cin >> n >> q;
        
        vector<int> a(n);
        
        for(auto &x: a) {
            cin >> x;
        }

        SegmentTree st(n, a);

        while(q--){
            int l, r;
            cin >> l >> r;
            
            l--;
            r--;
            
            Node res = st.query(1, 0, n-1, l, r);
            
            int min_val = res.min_val;
            ll m = res.gcd_val;
            
            if(m == 0){
                cout << "0 ";
            } else{
                cout << m << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}