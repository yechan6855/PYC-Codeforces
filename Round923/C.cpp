#include <iostream>
#include <vector>


using namespace std;
int main(){

    int T = 1;
    cin >> T;
    while(T--)
    {
        int n,m,A,B,k;
        int multi = 0;
        cin >> n >> m >> k;
        A = B = k/2;
        vector<int>frqa(k);
        vector<int>frqb(k);
        vector<int>a(n);
        vector<int>b(m);
        for(int i = 0; i < n; i++)
        {
            cin >> a[i];
            if(a[i] <= k) frqa[a[i]-1]++;
        }
        for(int i = 0; i < m; i++)
        {
            cin >> b[i];
            if(b[i] <= k) frqb[b[i]-1]++;
        }


        for(int i = 0; i < k; i++)
        {
            if(frqb[i] && !frqa[i] && B)
            {
                B--;
            }
            else if(!frqb[i] && frqa[i] && A)
            {
                A--;
            }
            else if(frqb[i] && frqa[i])
            {
                multi++;
            }
        }
        if(A+B-multi == 0)
        {
            cout << "YES\\n";
        }
        else
        {
            cout << "NO\\n";
        }
    }
    return 0;
}
