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

int main() {
    std::string p, t, s, rp, rt, rs;
    std::cin >> p >> t;
    s = p + "#" + t;
    std::reverse(p.begin(), p.end());
    std::reverse(t.begin(), t.end());
    rs = p + "#" + t;
    std::vector<int> z = z_fun(s);
    std::vector<int> rz = z_fun(rs);

    int n = p.size();
    int m = t.size();
    std::vector<int> answer;

    for (int i = 0; i <= m - n; i++) {
        if (z[n + 1 + i] + rz[m + n + 1 - (i + n)] + 1 >= n) {
            answer.push_back(i + 1);
        }
    }
    std::cout << answer.size() << "\n";
    for (auto a : answer) std::cout << a << " ";
}