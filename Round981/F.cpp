#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MOD = 1e9 + 7;

struct PisanoInfo {
    int period;
    vector<int> zero_pos;
};

PisanoInfo compute_pisano(int k) {
    PisanoInfo info;

    vector<int> zero_pos;

    if (k == 1) {
        info.period = 1;
        zero_pos.push_back(1);
        info.zero_pos = zero_pos;

        return info;
    }

    int f_prev = 1 % k;
    int f_curr = 1 % k;

    if (f_prev == 0) {
        zero_pos.push_back(1);
    }
    if (f_curr == 0) {
        zero_pos.push_back(2);
    }

    int pos = 3;

    while (pos <= 6 * k + 2) {
        int f_next = (f_prev + f_curr) % k;

        if (f_next == 0) {
            zero_pos.push_back(pos);
        }

        f_prev = f_curr;
        f_curr = f_next;

        if (f_prev == 1 && f_curr == 1) {
            break;
        }
        pos++;
    }

    info.period = pos - 2;
    info.zero_pos = zero_pos;
    return info;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    const int k_max = 100000;
    vector<PisanoInfo> pisano_cache(k_max + 1);

    for(int i=0;i<=k_max;i++) {
        pisano_cache[i].period = 0;
    }

    while(t--){
        ll n;
        int k;
        cin >> n >> k;

        if(pisano_cache[k].period == 0){
            pisano_cache[k] = compute_pisano(k);
        }

        PisanoInfo info = pisano_cache[k];
        int period = info.period;

        vector<int> &zero_pos = info.zero_pos;
        int count_zero = zero_pos.size();

        ll c = (n - 1) / count_zero;
        int r = (n - 1) % count_zero;

        ll c_mod = c % MOD;
        ll term1 = (c_mod * (ll)period) % MOD;
        ll term2 = zero_pos[r];
        ll ans = (term1 + term2) % MOD;
        cout << ans << "\n";
    }
}