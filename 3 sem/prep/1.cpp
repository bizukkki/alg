#include <iostream>
#include <vector>

std::vector<int> z_fun(std::string &s) {
    int n = s.size();
    std::vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = std::min(z[i - l], r - i +1);
        }
        while ( i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}

bool glas(char ch) {
    return ch == 'o' || ch == 'e' || ch == 'i' || ch == 'a' || ch == 'u' || ch == 'y';
}

int main() {
    std::string s, t;
    std::cin >> t >> s;
    for (size_t i = 0; i < t.size(); i++) {
        if (glas(t[i])) {
            t[i] = '1';
        } else t[i] = '0';
    }
    for (size_t i = 0; i < s.size(); i++) {
        if (glas(s[i])) {
            s[i] = '1';
        } else s[i] = '0';
    }
    std::string both = s + '#' + t;
    std::vector<int> z = z_fun(both);
    int n = s.size();
    for (auto a : z) std::cout << a << " ";
    std::cout << '\n';
    for (int i = n + 1; i < z.size(); i++) {
        if (z[i] == n) std::cout << i - n - 1;
    }
}