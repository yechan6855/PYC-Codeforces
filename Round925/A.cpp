#include <iostream>
using namespace std;

string get_word(int encoded_sum) {
    for (int i = 1; i <= 26; ++i) {
        for (int j = 1; j <= 26; ++j) {
            for (int k = 1; k <= 26; ++k) {
                if (i + j + k == encoded_sum) {
                    string word = "";
                    word += char(i + 96);
                    word += char(j + 96);
                    word += char(k + 96);
                    return word;
                }
            }
        }
    }
    return "";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int encoded_sum;
        cin >> encoded_sum;
        cout << get_word(encoded_sum) << endl;
    }
    return 0;
}
