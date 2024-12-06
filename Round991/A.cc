#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        long long S = 0, sum_odd = 0, sum_even = 0;
        
        for (int i = 1; i <= n; i++) {
            long long a;
            
            cin >> a;
            
            S += a;
            
            if (i % 2) sum_odd += a;
            else sum_even += a;
        }
        if (S % n != 0) {
            cout << "NO\n";
            continue;
        }
        
        long long x = S / n;
        bool ok = true;

        if (n % 2 == 0) {
            if (sum_odd != (x * (n / 2)) || sum_even != (x * (n / 2))) ok = false;
        } else {
            if (sum_odd != (x * ((n + 1) / 2)) || sum_even != (x * (n / 2))) ok = false;
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
}