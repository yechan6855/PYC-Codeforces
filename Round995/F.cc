#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        ll n, k;
        cin >> n >> k;

        vector<ll> a(n), b(n);

        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        vector<ll> arr;
        arr.reserve(4 * n);

        for(int i = 0; i < n; i++){
            arr.push_back(a[i]);
            arr.push_back(a[i] + 1);
            arr.push_back(b[i]);
            arr.push_back(b[i] + 1);
        }

        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());

        ll ans = 0;

        for(auto &p : arr){
            if(p <= 0) continue;

            int lba = int(lower_bound(a.begin(), a.end(), p) - a.begin());
            int lbb = int(lower_bound(b.begin(), b.end(), p) - b.begin());

            ll ncnt = (ll)lba - lbb;
            if(ncnt <= k){
                ll bs = n - lbb;
                ll rv = p * bs;
                ans = max(ans, rv);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}