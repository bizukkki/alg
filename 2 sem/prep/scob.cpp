#include <iostream>
#include <map>
#include <string>
#include <stack>
int main() 
{
    std::string s;
    std::cin >> s;
    std::stack<char> st;
    std::map<char, char> cl_op = {{']','['}, {'}', '{'}, {')', '('} };
    std::string open = "([{";
    for (char ch : s) {
        if (open.find(ch) == std::string::npos) {
            if (st.empty()) {
                std::cout << "no";
                return 0;
            }
            char pr = st.top();
            st.pop();
            if (pr != cl_op[ch]) {
                std::cout << "no";
                return 0;
            }
        } else {
            st.push(ch);
        }
    }
    if (!st.empty()) {
        std::cout << "no";
    } else std::cout<< "yes";
}