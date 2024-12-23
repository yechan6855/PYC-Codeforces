#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while(t--){
        int n;
        cin >> n;
        
        vector<int> a(n);
        
        for(auto &x: a) {
            cin >> x;
        }

        vector<int> b(n);
        
        for(auto &x: b) {
            cin >> x;
        }
        
        long long res = a[n-1];
        
        for(int i=0;i<n-1;i++){
            if(a[i] > b[i+1]){
                res += (a[i] - b[i+1]);
            }
        }
        cout << res << "\n";
    }
}