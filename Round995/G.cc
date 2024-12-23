#include <bits/stdc++.h>
#define ll long long
using namespace std;


static vector<pair<ll,ll>> solve(vector<pair<ll,ll>> &arr) {
   vector<pair<ll,ll>> ans;
   ans.reserve(arr.size());
   for (auto &iv : arr) {
       if (ans.empty() || ans.back().second < iv.first - 1) {
           ans.push_back(iv);
       } else {
           ans.back().second = max(ans.back().second, iv.second);
       }
   }
   return ans;
}

int main(){
   ios::sync_with_stdio(false);
   cin.tie(nullptr);

   int t;
   cin >> t;
   while(t--){
       ll n, m;
       int q;
       cin >> n >> m >> q;

       vector<pair<ll,ll>> arr;
       arr.push_back({m,m});

       while(q--){
           ll a;
           cin >> a;

           vector<pair<ll,ll>> res;
           res.reserve(arr.size()*2 + 2);

           for (auto &iv : arr) {
               ll l = iv.first, r = iv.second;
               if (r < a) {
                   res.push_back({l, r});

                   ll l2 = l+1, r2 = r+1;
                   if (r2 >= 1 && l2 <= n) {
                       l2 = max(l2, 1LL);
                       r2 = min(r2, n);
                       if (l2 <= r2) {
                           res.push_back({l2,r2});
                       }
                   }
               }
               else if (l > a) {
                   res.push_back({l,r});

                   ll l2 = l-1, r2 = r-1;
                   if (r2 >= 1 && l2 <= n) {
                       l2 = max(l2, 1LL);
                       r2 = min(r2, n);
                       if (l2 <= r2) {
                           res.push_back({l2,r2});
                       }
                   }
               }
               else {
                   if (l <= a-1) {
                       ll lsub = l, rsub = a-1;
                       res.push_back({lsub, rsub});
                       ll l2 = lsub+1, r2 = rsub+1;
                       if (l2<=r2 && l2<=n && r2>=1) {
                           l2 = max(l2,1LL);
                           r2 = min(r2,n);
                           if (l2<=r2) {
                               res.push_back({l2,r2});
                           }
                       }
                   }

                   if (l <= a && a <= r) {
                       res.push_back({1,1});
                       res.push_back({n,n});
                   }

                   if (a+1 <= r) {
                       ll ls = a+1;
                       ll rs = r;
                       res.push_back({ls, rs});
                       ll l2 = ls-1, r2 = rs-1;
                       if (l2<=r2 && l2>=1 && r2<=n) {
                           res.push_back({l2,r2});
                       }
                   }
               }
           }

           sort(res.begin(), res.end());
           arr = solve(res);

           ll ans = 0;

           for (auto &iv : arr) {
               ans += (iv.second - iv.first + 1);
           }

           cout << ans << " ";
       }
       cout << "\n";
   }

   return 0;
}