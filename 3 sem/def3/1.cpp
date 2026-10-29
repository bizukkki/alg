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
    int n = s.size();
    int max_c = -1;
    int max_len = 0;
    for (int i = 1; i <= s.size(); i++) {
        std::string suf = s.substr(n - i);
        std::string new_s = suf + '#' + s;
        std::vector<int> pref = prefix_fun(new_s);
        int cnt = 0;
        for (int j = suf.size(); j < pref.size(); j++) {
            if (pref[j] == i) cnt++;
        }
        if (cnt < max_c && i > 1) break;
        if (cnt >= max_c && cnt > 1) {
            max_c = cnt;
            max_len = i;
        }
    }
    std::cout << max_len;
}