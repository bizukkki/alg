#include <iostream>
#include <vector>
#include <string>

void coding (std::string &s) {
    int n = s.size();
    int k = 0;
    while (( 1 << k) < n + k + 1) {
        k++;
    }
    int m = k + n;
    std::string new_s(m + 1, '0');

    int j = 0;
    for (int i = 1; i <= m; i++) {
        if ((i & (i - 1)) != 0) {
            new_s[i] = s[j];
            j++;
        }
    }
    for (int p = 1; p <= m; p *= 2) {
        int sum = 0;
        for (int start = p; start <= m; start += 2 * p) {
            for (int i = start; i < start + p && i <= m; i++) {
                sum ^= (new_s[i] - '0');
        }
        new_s[p] = char('0' + sum);
        }
    }
    for (int i = 1; i <= m; i++) {
        std::cout << new_s[i];
    }
    std::cout << "\n";
}

void decoding(std::string &s) {
    s = " " + s;
    int m = s.size() - 1;
    std::string original;
    int error = 0;
    for (int p = 1; p <= m; p *= 2) {
        int sum = 0;
        for (int start = p; start <= m; start += 2 * p) {
            for (int i = start; i < start + p && i <= m; i++) {
                sum ^= (s[i] - '0');
            }
        }
        if (sum) {
            error+=p;
        }
    }
    if (error == 0) std::cout << -1;
    else{
        std::cout << error - 1;
    }
}

int main() {
    std::string s;
    std::cin >> s;
    decoding(s);
}