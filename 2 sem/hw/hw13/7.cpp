#include <iostream>
#include <vector>

long long place(int n, int k) {
    long long answ = 1;
    for (int i = 0; i < k; i++) {
        answ *= n - i;
    }
    return answ;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> vec(k);
    for (int i = 0; i < k; i++) {
        std::cin >> vec[i];
    }
    std::vector<int> used(n + 1, false);
    long long answer = 1;
    for (int pos = 0; pos < k; pos++) {
        long long base = place(n - pos - 1, k - pos - 1);
        int cnt = 0;
        for (int i = 1; i < vec[pos]; i++) {
            if (!used[i]) {
                cnt++;
            }
        }
        answer += cnt * base;
        used[vec[pos]] = true;
    }
    std::cout << answer;
}