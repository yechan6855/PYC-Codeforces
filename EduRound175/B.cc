#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct SimResult {
    ll t;
    bool hit;
    ll final;
    bool stopped;
};

SimResult solve(ll p, const string &s) {
    ll t = 0;
    for (char ch : s) {
        t++;
        if(ch == 'L') {
            p -= 1;
        } else {
            p += 1;
        }
        if(p == 0) {
            return {t, true, 0, false};
        }
    }
    return {t, false, p, true};
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        ll x, k;
        string s;

        cin >> n >> x >> k;
        cin >> s;

        SimResult first = solve(x, s);
        ll ans = 0;

        if(!first.hit) {
            cout << 0 << "\n";
            continue;
        }

        if(k < first.t) {
            cout << 0 << "\n";
            continue;
        }

        ans = 1;
        ll rem = k - first.t;

        SimResult cycle = solve(0, s);

        if(!cycle.hit) {
            cout << ans << "\n";
            continue;
        }

        ll time = cycle.t;
        ll res = rem / time;
        ans += res;
        rem %= time;

        ll pos = 0;

        for (int i = 0; i < rem; i++){
            pos += (s[i] == 'L' ? -1 : 1);
            if(pos == 0) {
                ans++;
                break;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}