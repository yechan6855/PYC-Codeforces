#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int LOG = 20;

void solve() {
   int n;
   cin >> n;
   vector<vector<int>> adj(n + 1);
   for (int i = 0; i < n - 1; i++) {
       int u, v;
       cin >> u >> v;
       adj[u].push_back(v);
       adj[v].push_back(u);
   }

   vector<int> depth(n + 1, 0);
   vector<int> parent(n + 1, -1);
   vector<int> maxdep(n + 1, 0);
   vector<vector<int>> child(n + 1);

   function<void(int, int)> dfs = [&](int u, int p) {
       parent[u] = p;
       if (p == -1) depth[u] = 1;
       else depth[u] = depth[p] + 1;
       maxdep[u] = depth[u];

       for (int v : adj[u]) {
           if (v != p) {
               child[u].push_back(v);
               dfs(v, u);
               maxdep[u] = max(maxdep[u], maxdep[v]);
           }
       }
   };

   dfs(1, -1);

   vector<map<int, int>> maxexc(n + 1);
   for (int u = 1; u <= n; u++) {
       if (child[u].empty()) continue;

       vector<int> cdepth;
       for (int c : child[u]) {
           cdepth.push_back(maxdep[c]);
       }

       int max1 = *max_element(cdepth.begin(), cdepth.end());
       int maxcnt = count(cdepth.begin(), cdepth.end(), max1);

       int max2 = -1;
       for (int d : cdepth) {
           if (d != max1) max2 = max(max2, d);
       }

       for (int c : child[u]) {
           int excl;
           if (maxdep[c] == max1) {
               excl = (maxcnt > 1) ? max1 : max2;
           } else {
               excl = max1;
           }
           excl = max(excl, depth[u]);
           maxexc[u][c] = excl;
       }
   }

   vector<vector<int>> lift(n + 1, vector<int>(LOG, -1));
   vector<vector<ll>> maxval(n + 1, vector<ll>(LOG, LLONG_MIN));

   for (int u = 1; u <= n; u++) {
       lift[u][0] = parent[u];
       if (parent[u] != -1) {
           int c = u;
           int excl = maxexc[parent[u]][c];
           maxval[u][0] = excl - 2LL * depth[parent[u]];
       }
   }

   for (int j = 1; j < LOG; j++) {
       for (int u = 1; u <= n; u++) {
           if (lift[u][j-1] != -1) {
               lift[u][j] = lift[lift[u][j-1]][j-1];
               maxval[u][j] = max(maxval[u][j-1], maxval[lift[u][j-1]][j-1]);
           } else {
               lift[u][j] = -1;
               maxval[u][j] = maxval[u][j-1];
           }
       }
   }

   int q;
   cin >> q;
   while (q--) {
       int vi, ki;
       cin >> vi >> ki;

       ll max1 = maxdep[vi] - depth[vi];
       if (ki == 0) {
           cout << max1 << " ";
           continue;
       }

       int limdep = max(1, depth[vi] - ki);
       ll maxext = LLONG_MIN;
       int node = vi;
       int remain = ki;

       for (int j = LOG - 1; j >= 0; j--) {
           if (remain >= (1 << j) && lift[node][j] != -1 && depth[lift[node][j]] >= limdep) {
               maxext = max(maxext, maxval[node][j]);
               node = lift[node][j];
               remain -= (1 << j);
           }
       }

       ll answer = (maxext == LLONG_MIN) ? max1 : max(max1, depth[vi] + maxext);
       cout << answer << " ";
   }
   cout << "\n";
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);

   int t;
   cin >> t;
   while (t--) {
       solve();
   }
   return 0;
}