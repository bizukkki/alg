#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string s;
    s = "12345";
    int i = 1;
    do {
        if (i== 77) std::cout << s << '\n';
        i++;
    } while (std::next_permutation(s.begin(), s.end()));
} 