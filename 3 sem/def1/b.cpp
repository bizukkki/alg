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
    std::string s = "abaababaab";
    std::vector<int> z = z_fun(s);
    for (auto a : z) std::cout << a << " ";

}