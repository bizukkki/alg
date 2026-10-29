#include <iostream>
#include <string>
#include <map>
#include <stack>

void rec(std::string& s, std::stack<char>& st, std::map<char, char>& close, int n, int pos, int opened) {
    if (pos == n) {
        if (st.empty()) {
            std::cout << s << '\n';
        }
        return;
    }
    std::string chars = "([)]";
    for (char c : chars) {
        if (c == '(' || c == '[') {
            if (opened < n / 2) {
                s[pos] = c;
                st.push(c);
                rec(s, st, close, n, pos + 1, opened + 1);
                st.pop();
            }
        } else {
            if (!st.empty() && st.top() == close[c]) {
                s[pos] = c;
                char prev = st.top();
                st.pop();
                rec(s, st, close, n, pos + 1, opened);
                st.push(prev);
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    if (n % 2 == 1) {
        return 0;
    }
    std::map<char, char> close = {{')', '('}, {']','['}};
    std::string s(n, ' ');
    std::stack<char> st;
    rec(s, st, close, n, 0, 0);
}