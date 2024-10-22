#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        map<int, vector<char>> m;
        string s = "";
        int cnt = 0;

        for (auto c : v) {
            if (m[c].size() == 0) {
                m[c].push_back('a');
                s += 'a';
            } else {
                m[c].push_back(m[c][m[c].size() - 1] + 1);
                s += m[c][m[c].size() - 1];
            }
        }

        cout << s << "\\n";
    }

    return 0;
}
