#include <iostream>
#include <vector>

int main() {
    long long n;
    std::cin >> n;
    std::vector<std::vector<long long>> c(100, std::vector<long long>(100, 0));
    for (int i = 0; i < 100; i++) {
        c[i][0] = 1;
        c[i][i] = 1;
    }
    for (int i = 2; i < 100; i++) {
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    int len = 1;
    while (true) {
        long long cnt = c[len + 8][8];
        if (n > cnt) {
            n -= cnt;
            len++;
        } else break;
    }
    std::vector<int> answer;
    int prev = 1;
    for (int pos = 0; pos < len; pos++) {
        for (int d = prev; d <= 9; d++) {
            int left = len - pos - 1;
            long long cnt = c[left + 9 - d][9 - d];
            if (n > cnt) {
                n -= cnt;
            } else {
                answer.push_back(d);
                prev = d;
                break;
            }
        }
    }
    for(int a: answer) std::cout<<a;
}