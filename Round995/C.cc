#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        ll n, m, k;
        cin >> n >> m >> k;

        vector<ll> a(m);

        for(auto &x: a) {
            cin >> x;
        }

        vector<ll> q(k);

        for(auto &x: q) {
            cin >> x;
        }

        vector<char> res(n+1, 0);

        for(auto x: q){
            if(x >=1 && x <=n){
                res[x] = 1;
            }
        }

        string ans = "";
        for(auto x: a){
            if(x >=1 && x <=n && res[x]){
                if(k == n){
                    ans += '1';
                }
                else{
                    ans += '0';
                }
            } else{
                if(k == n -1){
                    ans += '1';
                }
                else{
                    ans += '0';
                }
            }
        }

        cout << ans << "\n";
    }
}