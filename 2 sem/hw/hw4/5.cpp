#include <iostream>
#include <vector>
#include <queue>

struct Edge {
    int from;
    int to;
    int weight;
};

int main() {
    int n, m, k, c;
    std::cin >> n >> m >> k >> c;
    std::vector<bool> city(n+1, false);
    for (int i = 0; i < k; i++){
        int point;
        std::cin >> point;
        city[point] = true;
    }
    std::vector<std::vector<Edge>> g(n+1);
    for (int i = 1; i < m + 1; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        g[a].push_back({a, b, w});
        g[b].push_back({b, a, w});
    }
    long long inf = 1e18;
    std::vector<long long> dist(n+1, inf);
    dist[c] = 0;
    std::priority_queue<std::pair<long long,int>,
        std::vector<std::pair<long long, int>>,
        std::greater<std::pair<long long, int>> > min_heap;
    min_heap.push({0, c});
    while(!min_heap.empty()) {
        auto now = min_heap.top();
        min_heap.pop();
        long long d = now.first;
        int v = now.second;
        if (d > dist[v]) continue;
        for (auto ch : g[now.second]) {
            if (dist[ch.to] > dist[v] + ch.weight) {
                dist[ch.to] = dist[v] + ch.weight;
                min_heap.push({dist[ch.to], ch.to});
            }
        }
    }
    std::vector<std::pair<long long, int>> answer;
    for(int i = 1; i < n +1; i++) {
        if (city[i]) answer.push_back({dist[i], i});
    }
    std::sort(answer.begin(), answer.end());
    for (int i = 0; i < k; i++){
        std::cout << answer[i].second << " " << answer[i].first << "\n";
    }
}