#include <bits/stdc++.h>
using namespace std;

long long power_limit(long long k, int n, long long limit) {
    if (n == 0) return 1;
    long long result = 1;
    for(int i=0;i<n;i++) {
        if (result > limit / k) return -1;
        result *= k;
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        long long k, l1, r1, l2, r2;
        cin >> k >> l1 >> r1 >> l2 >> r2;

        long long count = 0;

        for(int n=0; n<=60; n++){
            long long kn = power_limit(k, n, r2);

            if(kn == -1) break;

            long long x_min = (kn ==0)? l1 : (l2 + kn -1)/kn;
            long long x_max;

            if(kn ==0){
                continue;
            }
            else{
                x_max = r2 / kn;
            }

            long long start = max(l1, x_min);
            long long end = min(r1, x_max);
            
            if(start > end) continue;
            
            count += (end - start +1);
        }
        cout << count << "\n";
    }
}