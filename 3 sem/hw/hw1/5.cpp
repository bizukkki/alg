#include <iostream>
#include <vector>

std::vector<int> prefix_fun(std::string &s) {
    int n = s.size();
    std::vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        int k = p[i-1];
        while (s[i] != s[k] && k > 0) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            p[i] = k + 1;
        }
    }
    return p;
}

int main() {
    int n, a, k;
    std::cin >> n >> a >> k;
    std::string s;
    std::cin >> s;
    std::vector<int> p = prefix_fun(s);
    std::vector<std::vector<int>> go(n, std::vector<int>(a, 0));
    for (int i = 0; i < a; ++i) {
        char ch = char('a' + i);
        if (ch == s[0]) {
            go[0][i] = 1;
        } else {
            go[0][i] = 0;
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < a; ++j) {
            char ch = char('a' + j);
            if (ch == s[i]) {
                go[i][j] = i + 1;
            } else {
                go[i][j] = go[p[i - 1]][j];
            }
        }
    }
    int d = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j< a; ++j) {
            d = std::max(d, i - go[i][j]);
        }
    }
    long long answer = n + k * d;
    std::cout << answer << '\n';
    return 0;
}