#include <bits/stdc++.h>
#define ll long long
using namespace std;

const long long MOD = 998244353;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        vector<int> parent(n+1, 0);
        vector<int> depth(n+1, 0);

        depth[1] = 0;
        for (int i = 2; i <= n; i++){
            cin >> parent[i];
            depth[i] = depth[parent[i]] + 1;
        }

        int maxD = 0;
        for (int i = 1; i <= n; i++){
            maxD = max(maxD, depth[i]);
        }

        vector<ll> freq(maxD+1, 0);
        for (int i = 2; i <= n; i++){
            freq[ depth[i] ]++;
        }

        vector<ll> F(maxD+2, 0);
        if(maxD >= 1)
            F[maxD] = freq[maxD] % MOD;

        for (int d = maxD - 1; d >= 1; d--){
            ll term = ((freq[d] - 1) % MOD + MOD) % MOD;
            F[d] = (freq[d] + term * F[d+1]) % MOD;
        }

        ll ans = (1 + F[1]) % MOD;
        cout << ans << "\n";
    }
}