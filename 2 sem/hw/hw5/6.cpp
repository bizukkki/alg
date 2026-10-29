#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
};
int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    int inf = -1e9;
    std::vector<std::vector<int>> dist(n+1, std::vector<int>(n+1, inf));
    std::vector<Edge> edges(1);
    std::vector<std::vector<int>> next_edge(n+1, std::vector<int>(n+1, 0));
    for(int i = 1; i < m + 1; i++){
        int v, u, w;
        std::cin >> v >> u >> w;
        edges.push_back({v, u}); 
        dist[v][u] = w;
        next_edge[v][u] = i;
    }
    for (int i= 1; i < n + 1; ++i) {
        for (int from = 1; from < n + 1; ++from) {
            for (int to = 1; to < n + 1; ++to) {
                if (dist[from][i] != inf && dist[i][to] != inf && dist[from][to] < dist[from][i] + dist[i][to]) {
                    dist[from][to] = dist[from][i] + dist[i][to];
                    next_edge[from][to] = next_edge[from][i];
                }
            }
        }
    }

    std::vector<int> concerts(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> concerts[i];
    }
    int start = concerts[0];
    int finish = concerts[k-1];
    for (int v = 1; v < n + 1; v++) {
        if (dist[v][v] > 0 && dist[start][v] != inf && dist[v][finish] != inf) {
            std::cout << "infinitely kind";
            return 0;
        }
    }
    std::vector<int> answer;
    for (int i = 0; i < k - 1; ++i) {
        int s = concerts[i];
        int f = concerts[i + 1];
        int cur = s;
        while (cur != f) {
            int id = next_edge[cur][f];
            answer.push_back(id);
            cur = edges[id].to;
        }
    }
    std::cout << answer.size() << "\n";
    for (int i : answer) {
        std::cout << i << " ";
    }
}  
