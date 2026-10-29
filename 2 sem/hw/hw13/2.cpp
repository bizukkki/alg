#include <iostream>
#include <string>
#include <algorithm>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::string s;
    for (int i = 0; i < n - k; i++) s += '0';
    for (int i = 0; i < k; i++) s += '1';
    do {
        std::cout << s << '\n';
    } while (std::next_permutation(s.begin(), s.end()));
}