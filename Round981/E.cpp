#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        vector<int> p(n);

        for(int &x: p) {
            cin >> x;
        }

        for(int i=0;i<n;i++) {
            p[i] -=1;
        }

        vector<bool> visited(n, false);

        ll swap_count =0;

        for(int i=0;i<n;i++){
            if(!visited[i]){
                int cnt=0;
                int j=i;

                while(!visited[j]){
                    visited[j]=true;
                    cnt++;
                    j = p[j];
                }

                if(cnt >=3){
                    swap_count += (cnt -1)/2;
                }
            }
        }
        cout << swap_count << "\n";
    }
}