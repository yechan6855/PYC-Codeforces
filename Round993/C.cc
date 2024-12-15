#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        ll m, a, b, c;
        cin >> m >> a >> b >> c;

        ll sa = min(a, m);
        ll sb = min(b, m);

        ll rw1 = m - sa;
        ll rw2 = m - sb;
        ll tot = rw1 + rw2;

        ll sc = min(c, tot);
        ll ts = sa + sb + sc;

        cout << ts << "\n";
    }

    return 0;
}
