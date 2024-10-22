#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int n, vector<int>& arr) {
    if (n == 2) {
        if (arr[0] == arr[1]) return 0;
        return 1;
    }

    int f = 1, b = 1;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i + 1] == arr[i]) f++;
        else break;
    }

    for (int i = n - 1; i >= 1; i--) {
        if (arr[i - 1] == arr[i]) b++;
        else break;
    }

    if (f == n) return 0;

    int result;
    if (arr[0] == arr[n - 1]) result = f + b;
    else result = max(f, b);

    return (n - result);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int num;
        cin >> num;
        vector<int> arr(num);
        for (int i = 0; i < num; i++) cin >> arr[i];
        cout << solve(num, arr) << endl;
    }
    return 0;
}
