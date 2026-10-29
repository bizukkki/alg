#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    long long n, k;
    std::cin >> n >> k;
     std::vector<std::pair<long long, long long>> del;
    for (int i = 2; i*i <= k; i++) {
        if (k % i == 0){
            long long deg = 1;
            k/=i;
            while(k%i == 0) {
                k/=i;
                deg++;
            }
            del.push_back({i, deg});
        }
    }
    if (k > 1) {
        del.push_back({k, 1});
    }
    long long answer = 1e18;
    for (auto elem : del) {
        long long p = elem.first;
        long long deg = elem.second;
        long long cnt = 0;
        long long tmp = p;
        while (tmp <= n) {
            cnt += n / tmp;
            tmp*=p;
        }
        long long zeros = cnt / deg;
        if (zeros < answer) {
            answer = zeros;
        }
    }
    std::cout << answer;
}