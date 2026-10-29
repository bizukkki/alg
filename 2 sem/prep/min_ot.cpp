#include <iostream>

#include <deque>
int main() 
{
    std::deque<std::pair<int, int>> dq;
    int n, k;
    std::cin >> n >> k;
    int a;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        while (!dq.empty() && dq.front().second < i - k + 1 ) {
            dq.pop_front();
        }
        while (!dq.empty() && dq.back().first >= a) {
            dq.pop_back();
        }
        dq.push_back({a, i});    
        if (i >= k - 1) std::cout << dq.front().first << "\n";
    }
}