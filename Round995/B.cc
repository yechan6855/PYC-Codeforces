#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while(t--){
        ll n, a, b, c;
        cin >> n >> a >> b >> c;

        ll cs = a + b + c;
        ll k = (n - 1) / cs;
        ll to = k * cs;
        ll rem = n - to;
        ll ans = k * 3;
        
        if(rem <= a){
            ans +=1;
        }
        else if(rem <= a + b){
            ans +=2;
        }
        else{
            ans +=3;
        }
        cout << ans << "\n";
    }
}