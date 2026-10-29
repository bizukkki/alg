// #include <iostream>
// #include <vector>

// void rec(std::vector<int>& vec, int n, int k, int pos, int prev) {
//     if (pos == k) {
//         for (int i : vec) std::cout << i << " ";
//         std::cout << '\n';
//         return;
//     }
//     for (int i = prev - 1; i > 0; i--) {
//         vec[pos] = i;
//         rec(vec, n, k, pos + 1, i);
//     }
// }

// int main() {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     int n, k;
//     std::cin >> n >> k;
//     std::vector<int> vec(k);
//     std::vector<int> alf;
//     rec(vec, n, k, 0, 2);
// }

#include <iostream>
#include <vector>

void rec(std::vector<int>& vec, int n, int k, int pos, int prev) {
    if (pos == k) {
        for (int i : vec) std::cout << i << " ";
        std::cout << '\n';
        return;
    }
    if (pos == 0){
        for (int i = 1; i <= n; i++) {
            vec[0] = i;
            rec(vec, n, k, pos + 1, i);
        }
    } else {
       for (int i = prev - 1; i > 0; i++) {
             vec[pos] = i;
             rec(vec, n, k, pos + 1, i);
         }
     }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> vec(k);
    rec(vec, n, k, 0, 0);
}