#include <iostream>
#include <vector>

struct Box {
    int num;
    long long l;
    long long d;
    long long h;
};

void rec(int max_l, int max_d, int cur_sum, int &sum, std::vector<Box> &cur_answer, std::vector<Box> &answer,
        std::vector<std::vector<Box>> &variants, std::vector<int> &used) {
    if (cur_sum > sum) {
        sum = cur_sum;
        answer = cur_answer;
    }
    int bound = 0;
    for (size_t i = 0; i < used.size(); i++) {
        if (!used[i]) {
            long long best_h = 0;
            for (Box b : variants[i]) {
                if (b.l <= max_l && b.d <= max_d) {
                    if (b.h > best_h) {
                        best_h = b.h;
                    }
                }
            }
            bound += best_h;
        }
    }
    if (cur_sum + bound <= sum) {
        return;
    }
    for (size_t i = 0; i < used.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            for (Box b : variants[i]) {
                if (b.l <= max_l && b.d <= max_d) {
                    cur_answer.push_back(b);
                    rec(b.l, b.d, cur_sum + b.h, sum, cur_answer, answer, variants, used);
                    cur_answer.pop_back();
                }
            }
            used[i] = false;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<Box>> variants(n);
    std::vector<int> used(n, false);
    std::vector<Box> cur_answer;
    std::vector<Box> answer;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        long long a, b, c;
        std::cin >> a >> b >> c;
        variants[i].push_back({i + 1, std::max(a, b), std::min(a, b), c});
        variants[i].push_back({i + 1, std::max(a, c), std::min(a, c), b});
        variants[i].push_back({i + 1, std::max(b, c), std::min(b, c), a});
    }
    rec(1e9, 1e9, 0, sum, cur_answer, answer, variants, used);
    std::cout << sum << '\n';
    std::cout << answer.size() << '\n';
    for (Box b : answer) {
        std::cout << b.num << " " << b.l << " " << b.d << " " << b.h << '\n';
    }
}