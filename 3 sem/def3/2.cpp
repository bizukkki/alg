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
    std::cin >> n;
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        int k;
        std::cin >> k;
        v.push_back(k);
    }
    std::string s = "q";
    std::string alf = "qwertyuiopasdfghjklzxcvbnm";
    int i = 1;
    int let = 1;
    while (i < n) {
        if(v[i] == 0) {
            s += alf[let];
            let++;
            i++;
        } else {
            int j = v[i];
            for (int k = 0; k < j; k++) {
                if (s.size() < n){
                    s += s[k];
                    i++;
                }
                else break;
            }
        }
    }
    std::cout << s << "\n";
    std::vector<int> z = z_fun(s);
    for (auto a : z) std::cout << a << " ";
}