#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int INF = 1e9;

int solve(const string &a, const string &b, const string &c) {
    int n = a.size();
    int m = b.size();

    vector<int> previous(m + 1, INF);
    vector<int> current(m + 1, INF);

    previous[0] = 0;
    for(int j = 1; j <= m; ++j){
        if(j > c.size()) break;
        previous[j] = previous[j-1] + (b[j-1] != c[j-1]);
    }

    for(int i = 1; i <= n; ++i){
        current[0] = previous[0] + (a[i-1] != c[i-1]);
        for(int j = 1; j <= m; ++j){
            if(i + j -1 >= c.size()) {
                current[j] = INF;
                continue;
            }
            int cost_a = previous[j] + (a[i-1] != c[i + j -1]);
            int cost_b = current[j-1] + (b[j-1] != c[i + j -1]);

            current[j] = min(cost_a, cost_b);
        }
        previous = current;
    }

    return previous[m];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        string a, b, c;
        cin >> a >> b >> c;

        cout << solve(a, b, c) << "\n";
    }
}