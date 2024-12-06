#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    
    int n = s.size();
    vector<int> digits(n);
    
    for(int i=0;i<n;i++) digits[i] = s[i]-'0';
    
    for(int i=1; i<n; ++i){
        int j = i;
        
        while(j >=1 && digits[j] >0 && digits[j]-1 > digits[j-1]){
            digits[j] -=1;
            
            swap(digits[j], digits[j-1]);
            j--;
        }
    }
    
    for(auto d: digits) {
        cout << d;
    }
    
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while(t--){
        solve();
    }
}