#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n, k;
        string s;

        cin >> n >> k;
        cin >> s;

        vector<ll> arr(n);
        ll maxA = 0;

        for (int i = 0; i < n; i++){
            cin >> arr[i];
            maxA = max(maxA, arr[i]);
        }

        ll low = 0, high = maxA, ans = high;
        while(low <= high){
            ll mid = low + (high - low) / 2;

            int res = 0;
            int i = 0;

            while(i < n){
                if(s[i] == 'R' && arr[i] > mid){
                    i++;
                    continue;
                }

                bool check = false;

                while(i < n && !(s[i] == 'R' && arr[i] > mid)){
                    if(s[i] == 'B' && arr[i] > mid){
                        check = true;
                    }
                    i++;
                }
                if(check){
                    res++;
                }
            }
            if(res <= k){
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        cout << ans << "\n";
    }
}