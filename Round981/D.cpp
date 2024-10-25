#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<vector<int>> &a){
    vector<int> d(2*n-1, 0);
    
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            d[i-j+n-1] = max(d[i-j+n-1], a[i][j] < 0 ? -a[i][j] : 0);
        }
    }
    int s=0;
    
    for(auto x:d) {
        s += x;
    }
    
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while(t--){
        int n;
        cin >> n;
        
        vector<vector<int>> a(n, vector<int>(n));
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                cin >> a[i][j];
            }
        }
        cout << solve(n, a) << "\n";
    }
}