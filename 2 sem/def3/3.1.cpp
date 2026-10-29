#include <iostream>
#include <string>

void rec(std::string& s, int n, int pos, std::string alf) {
    if (pos == n) {
        std::cout << s << '\n';
        return;
    }
    for (char ch : alf) {
        s[pos] = ch;
        rec(s, n, pos + 1, alf);
    }

}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::string s(n, 0);
    std::string al = "0123456789abcdefghijklmnopqrstuvwxyz";
    std::string alf;
    for (int i = 0; i < k; i++){
        alf +=al[i];
    }
    std::reverse(alf.begin(), alf.end());
    rec(s, n, 0, alf);
}