#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve(int n, vector<vector<ll>> &M, vector<vector<ll>> &S, vector<vector<ll>> &Sr, vector<vector<ll>> &Sc) {
    for(int r=1; r<=n; ++r){
        for(int c=1; c<=n; ++c){
            S[r][c] = S[r-1][c] + S[r][c-1] - S[r-1][c-1] + M[r][c];
            Sr[r][c] = Sr[r-1][c] + Sr[r][c-1] - Sr[r-1][c-1] + (ll)r * M[r][c];
            Sc[r][c] = Sc[r-1][c] + Sc[r][c-1] - Sc[r-1][c-1] + (ll)c * M[r][c];
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n, q;
        cin >> n >> q;

        vector<vector<ll>> M(n+1, vector<ll>(n+1, 0));
        for(int r=1; r<=n; ++r){
            for(int c=1; c<=n; ++c){
                cin >> M[r][c];
            }
        }

        vector<vector<ll>> S(n+1, vector<ll>(n+1, 0));
        vector<vector<ll>> Sr(n+1, vector<ll>(n+1, 0));
        vector<vector<ll>> Sc(n+1, vector<ll>(n+1, 0));

        solve(n, M, S, Sr, Sc);

        string output = "";
        for(int i=0; i<q; ++i){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int width = y2 - y1 +1;

            ll sum_S = S[x2][y2] - S[x1-1][y2] - S[x2][y1-1] + S[x1-1][y1-1];
            ll sum_Sr = Sr[x2][y2] - Sr[x1-1][y2] - Sr[x2][y1-1] + Sr[x1-1][y1-1];
            ll sum_Sc = Sc[x2][y2] - Sc[x1-1][y2] - Sc[x2][y1-1] + Sc[x1-1][y1-1];

            ll term1 = (ll)width * (sum_Sr - (ll)x1 * sum_S);
            ll term2 = sum_Sc - (ll)(y1 -1) * sum_S;
            ll total = term1 + term2;
            output += to_string(total) + " ";
        }
        cout << output << "\n";
    }
}