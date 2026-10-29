// #include <iostream>
// #include <vector>
// #include <string>

// void rec(std::vector<std::string>& vec, int n, int k, int pos, int prev, std::string alf,  
//          std::vector<std::string>& answ) {
//     if (pos == k) {
//         answ.push_back(vec);
//         return;
//     }
//     for (int i = prev + 1; i <= n - (k - pos) + 1; i++) {
//         vec[pos] = i;
//         rec(vec, n, k, pos + 1, i, alf, answ);
//     }
// }

// int main() {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     int n, k;
//     std::cin >> n >> k;
//     std::vector<int> vec(k);
//     std::string alf = "0123456789abcdefghijklmnopqrstuvwxyz";
//     std::reverse(alf.begin(), alf.end());
//     std::vector<std::string> answ;
//     rec(vec, n, k, 0, 0);
// }

#include <iostream>
#include <vector>

void rec(std::vector<int>& vec, int n, int k, int pos, int prev, 
    std::vector<std::vector<int>>& answ) {
    if (pos == k) {
        answ.push_back(vec);
        return;
    }
    for (int i = prev + 1; i <= n - (k - pos) + 1; i++) {
        vec[pos] = i;
        rec(vec, n, k, pos + 1, i, answ);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> answ;
    std::vector<int> vec(k);
    rec(vec, n, k, 0, -1, answ);
    std::string alf = "0123456789abcdefghijklmnopqrstuvwxyz";
    std::reverse(alf.begin(), alf.end());
    
}  