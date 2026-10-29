#include <iostream>
#include <vector>

std::vector<int> z_fun(std::string &s) {
    int n = s.size();
    std::vector<int> z(n, 0);
    int l, r = 0;
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

int main() {
    int n;
    std::vector<std::string> vec;
    std::string t;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        vec.push_back(s);
    }
    std::cin >> t;
    int res = -1;
    for (auto s1 : vec) {
        std::string tmp = s1 + '#' + t;
        std::vector<int> z = z_fun(tmp);
        for (auto a : z) std::cout << a << " ";
        std::cout << '\n';
        int l = s1.size();
        std::cout << l << "\n";
        for (int i = l + 1; i < tmp.size(); i++) {
            if (tmp[i] == l) {
                if (res == -1) {
                    res+=1;
                }
                res += (i - (l + 1));
                std::cout << res << "\n";
            }
        }
        std::cout << 1 << " " << res << "\n";
        if (res != -1) {
            std::cout << res;
            break;
        }
    }
}