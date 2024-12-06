#include <bits/stdc++.h>
using namespace std;

int solve(int a, int m) {
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string n;
        cin >> n;

        int smod = 0;
        int cnt2 = 0, cnt3 = 0;
        for (char ch : n) {
            int digit = ch - '0';
            smod = (smod + digit) % 9;

            if (digit == 2) cnt2++;
            if (digit == 3) cnt3++;
        }

        int tamod = (9 - smod) % 9;
        bool found = false;
        int inv2 = 5;
        int rym[3] = {0, 6, 3};

        for (int r1 = 0; r1 <= 8; r1++) {
            int x0 = (inv2 * r1) % 9;

            if (x0 > cnt2) continue;

            for (int ymd = 0; ymd < 3; ymd++) {
                int r2 = rym[ymd];
                int tmod = (r1 + r2) % 9;

                if (tmod == tamod) {
                    int y0 = ymd;
                    if (y0 > cnt3) continue;


                    if (x0 <= cnt2 && y0 <= cnt3) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) break;
        }

        cout << (found ? "YES\n" : "NO\n");
    }

    return 0;
}