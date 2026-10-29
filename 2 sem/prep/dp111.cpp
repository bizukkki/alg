#include <iostream>

int main() 
{
    int n;
    std::cin >> n;
    int dp0 = 1;
    int dp1 = 1;
    int dp11 = 0;
    for (int i = 2; i < n+1; i++) {
        int new0 = dp0 + dp1 + dp11;
        int new1 = dp0;
        int new11 = dp1;
        dp0 = new0;
        dp1 = new1;
        dp11 = new11;
    }
    std::cout << dp0 + dp1 + dp11;
}
