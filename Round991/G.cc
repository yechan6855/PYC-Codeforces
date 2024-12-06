#include <bits/stdc++.h>
#define ll long long
using namespace std;

int dfs(int u, int parent, vector<vector<int>> &adj, vector<int> &val, int &max_sum){
    int cval = val[u];
    vector<int> chsum;

    for(auto &v: adj[u]){
        if(v != parent){
            int child_max = dfs(v, u, adj, val, max_sum);

            chsum.push_back(child_max);
        }
    }

    if(chsum.empty()){
        max_sum = max(max_sum, cval);

        return cval;
    }

    sort(chsum.begin(), chsum.end(), greater<int>());

    int top1 = chsum[0];
    int top2 = (chsum.size() >=2 ? chsum[1] : 0);

    int path_sum = cval;

    if(top1 > 0){
        path_sum += top1;
    }
    if(top2 > 0){
        path_sum += top2;
    }

    max_sum = max(max_sum, path_sum);

    int exsum = cval + (top1 > 0 ? top1 : 0);
    exsum = max(exsum, cval);

    return exsum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        vector<vector<int>> adj(n+1, vector<int>());

        for(int i=0; i<n-1; ++i){
            int u, v;
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> val(n+1, 0);

        for(int u=1; u<=n; ++u){
            val[u] = adj[u].size() - 2;
        }

        int max_sum = INT32_MIN;

        dfs(1, -1, adj, val, max_sum);

        cout << (max_sum + 2) << "\n";
    }

    return 0;
}