#include <iostream>
#include <map>

using namespace std;

#define int long long

signed main() {
    int a;
    cin >> a;
    while (a--) {
        int b, c, d;
        cin >> b >> c >> d;
        int e[b];
        for (int j = 0; j < b; j++) {
            cin >> e[j];
        }
        map<pair<int, int>, int> f;
        int g = 0;
        for (int j = 0; j < b; j++) {
            int h = e[j] % c;
            int i = e[j] % d;
            g += f[{c-h,i}];
            if (h == 0) {
                h = c;
            }
            f[{h,i}]++;
        }
        cout << g << "\\n";
    }
}
