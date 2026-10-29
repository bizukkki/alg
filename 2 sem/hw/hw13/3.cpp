#include <iostream>
#include <string>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::string s;
    for (char i = '1'; int(i) <= int('1') + (n - 1); i++) {
        s += i;
    }
    do {
        std::cout << s << '\n';
    } while (std::next_permutation(s.begin(), s.end()));
}   