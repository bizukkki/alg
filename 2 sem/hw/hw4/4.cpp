#include <iostream>
#include <vector>
#include <queue>

struct Edge {
    int from;
    int to;
    int weight;
};

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<Edge>> g(n+1);
    for (int i = 1; i < k + 1; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        g[a].push_back({a, b, w});
        g[b].push_back({b, a, w});
    }
    int s, f;
    std::cin >> s >> f;
    long long inf = 1e11;
    std::vector<long long> dist(n+1, inf);
    std::vector<int> prev(n+1, -1);
    prev[s] = 0;
    dist[s] = 0;
    std::priority_queue<std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>> > min_heap;
    min_heap.push({0, s});
    while(!min_heap.empty()) {
        auto now = min_heap.top();
        min_heap.pop();
        int d = now.first;
        int v = now.second;
        if (d > dist[v]) continue;
        for (auto ch : g[now.second]) {
            if (dist[ch.to] > dist[v] + ch.weight) {
                dist[ch.to] = dist[v] + ch.weight;
                 prev[ch.to] = v;
                min_heap.push({dist[ch.to], ch.to});
            }
        }
    }
    if (dist[f] != inf) {
        std::cout << dist[f] << "\n";
        std::vector<int> answer;
        answer.push_back(f);
        int p = prev[f];
        while (p != 0) {
            answer.push_back(p);
            p = prev[p];
        }
        std::reverse(answer.begin(), answer.end());
        std::cout << answer.size() << "\n";
        for (auto i : answer) std::cout << i << " ";
    } else std::cout << -1;
}