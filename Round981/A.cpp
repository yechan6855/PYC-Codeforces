#include <bits/stdc++.h>
using namespace std;

int f(int n) {
    int p = 0, i = 1;
    while (abs(p) <= n) {
        if (i % 2 == 1) p -= 2 * i - 1;
        else p += 2 * i - 1;
        i++;
    }
    return i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n;
    cin >> t;
    
    while (t--) {
        cin >> n;

        int m = f(n);

        if (m % 2 == 1) {
            cout << "Kosuke\n";
        }
        else {
            cout << "Sakurako\n";
        }
    }
}