#include <iostream>
#include <string>

void rec(std::string& s, int n, int pos) {
    if (pos == n) {
        std::cout << s << '\n';
        return;
    }
    s[pos] = '0';
    rec(s, n, pos + 1);
    s[pos] = '1';
    rec(s, n, pos + 1);
}

int main() {
    int n;
    std::cin >> n;
    std::string s(n, '0');
    rec(s, n, 0);
}