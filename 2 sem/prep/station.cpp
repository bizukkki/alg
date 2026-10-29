#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin>>n;
    std::vector<std::pair<int, int>> times;
    int need = n;
    std::vector<int> arr(60*24, 0);
    for (int i = 0; i < n; i++){
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        int m_op = a * 60 + b;
        int m_cl = c * 60 + d;
        if (m_cl != m_op) {
            times.push_back({m_op, 1});
            times.push_back({m_cl, 0});
            if (m_op > m_cl) arr[0]++;
        } else need--;
    }
    std::sort(times.begin(), times.end());
    for (auto a : times) {
        if (a.second) arr[a.first]++;
        else arr[a.first]--;
    }
    int answer = 0;
    int cur =0;
    for (auto i : arr) {
        cur +=i;
        if (cur == need) answer++;
    }
    std::cout << answer;
}