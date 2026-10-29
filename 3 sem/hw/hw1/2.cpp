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
    std::string s;
    std::cin >> s;
    std::vector<int> p = prefix_fun(s);
    int n = s.size();
    std::cout << "\n" << n - p[n- 1];
}