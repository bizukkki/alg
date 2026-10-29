#include <iostream>
#include <vector>

std::vector<int> z_fun(std::vector<int> &s) {
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
    std::vector<int> vec;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        vec.push_back(a);
    }
    std::vector<int> z = z_fun(vec);
    for(auto a : z) std::cout << a << " ";
    std::cout << "\n";
    int answ = -1;
    int i = 0;
    for (int i = 0; i < z.size(); i++) {
        if (z[i] != 0 ) {
            int jump = z[i];
            bool flag = true;
            for (int j = )
        }

    }
    // while (i >= 0) {
    //     if (z[i] != 0){
    //         m = z[i];
    //         break;
    //     }
    //     i--;
    // }
    // std::cout << '\n' << m - 1;

}