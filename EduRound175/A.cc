#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    while(t--){
        ll n;
        cin >> n;
        
        ll q = n / 15;
        ll r = n % 15;
        ll ans = 3 * q + min(3LL, r + 1);
        
        cout << ans << "\n";
    }
}