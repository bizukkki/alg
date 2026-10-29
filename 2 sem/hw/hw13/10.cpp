#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

void rec(std::vector<int>& part, std::vector<int>& best_part, std::vector<Edge>& edges, int n, int pos, long long& max_sum) {
    if (pos == n) {
        long long sum = 0;
        for (Edge e : edges) {
            if (part[e.from] != part[e.to]) {
                sum += e.weight;
            }
        }
        if (sum > max_sum) {
            max_sum = sum;
            best_part = part;
        }
        return;
    }
    part[pos] = 1;
    rec(part, best_part, edges, n, pos + 1, max_sum);
    part[pos] = 2;
    rec(part, best_part, edges, n, pos + 1, max_sum);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            std::cin >> x;
            if (j > i && x != 0) {
                edges.push_back({i, j, x});
            }
        }
    }
    std::vector<int> part(n);
    std::vector<int> best_part(n);
    long long max_sum = -1;
    part[0] = 1;
    rec(part, best_part, edges, n, 1, max_sum);
    std::cout << max_sum << '\n';
    for (int i : best_part) std::cout << i << " ";
}