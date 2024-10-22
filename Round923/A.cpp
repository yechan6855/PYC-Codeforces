#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        string s;
        cin >> s;

        int start = -1, end = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'B') {
                if (start == -1) {
                    start = i;
                }
                end = i;
            }
        }
        int minLength = end - start + 1;

        cout << minLength << endl;
    }

    return 0;
}
