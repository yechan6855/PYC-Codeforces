#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        vector<int> c(a);
        for (int i = 0; i < a; i++) {
            cin >> c[i];
        }
        auto length = [&](int c) {
            return int(log10(c) + 1);
        };
        auto pad = [&](int c) {
            int z = 1, r = 0;
            while (c % (z *= 10) == 0) {
                ++r;
            }
            return r;
        };

        sort(c.begin(), c.end(), [&](int i, int j) {
            return pad(i) < pad(j);

        });
        int ans = 0;
        for (int i = a - 1; i >= 0; i--) {
            ans += length(c[i]);
            if (i % 2 == (a - 1) % 2) {
                ans -= pad(c[i]);
            }
        }
        cout << (ans <= b ? "Anna" : "Sasha") << '\\n';
    }
    return 0;
}
