#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        ll n, x, y;
        cin >> n >> x >> y;

        vector<ll> a(n);

        for(auto &val : a) {
            cin >> val;
        }

        ll S = 0;

        for(auto val : a) {
            S += val;
        }

        ll L = S - y;
        ll R = S - x;

        L = max(L, (ll)2);
        R = min(R, (ll)2000000000);

        sort(a.begin(), a.end());

        ll cnt = 0;

        for(ll i = 0; i < n-1; ++i){
            ll lv = L - a[i];
            ll uv = R - a[i];

            ll jl = lower_bound(a.begin() + i + 1, a.end(), lv) - a.begin();
            ll ju = upper_bound(a.begin() + i + 1, a.end(), uv) - a.begin() - 1;

            if(jl <= ju && jl < n && ju >= i +1){
                cnt += (ju - jl +1);
            }
        }

        cout << cnt << "\n";
    }
}