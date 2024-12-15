#include <bits/stdc++.h>
using namespace std;

vector<long long> getDivisors(long long x) {
    vector<long long> divisors;
    if (x == 0) {
        return divisors;
    }
    long long abs_x = abs(x);
    for (long long i = 1; i * i <= abs_x; ++i) {
        if (abs_x % i == 0) {
            if (i * i == abs_x) {
                divisors.emplace_back(i);
                divisors.emplace_back(-i);
            } else {
                divisors.emplace_back(i);
                divisors.emplace_back(x / i);
                divisors.emplace_back(-i);
                divisors.emplace_back(-(x / i));
            }
        }
    }
    return divisors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long long> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    long long sum_a = 0;
    for (auto val: a) {
        sum_a += val;
    }

    long long sum_b = 0;
    for (auto val: b) {
        sum_b += val;
    }

    vector<long long> a1_list(n);
    for (int i = 0; i < n; ++i) {
        a1_list[i] = sum_a - a[i];
    }

    sort(a1_list.begin(), a1_list.end());
    a1_list.erase(unique(a1_list.begin(), a1_list.end()), a1_list.end());

    vector<long long> a2_list(m);
    for (int i = 0; i < m; ++i) {
        a2_list[i] = sum_b - b[i];
    }

    sort(a2_list.begin(), a2_list.end());
    a2_list.erase(unique(a2_list.begin(), a2_list.end()), a2_list.end());

    while (q--) {
        long long x;
        cin >> x;
        vector<long long> divisors = getDivisors(x);
        bool found = false;
        for (auto d1: divisors) {
            long long d2 = x / d1;

            if (binary_search(a1_list.begin(), a1_list.end(), d1) &&
                binary_search(a2_list.begin(), a2_list.end(), d2)) {
                found = true;
                break;
            }
        }
        if (found) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}