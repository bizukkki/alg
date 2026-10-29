#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    int n, m;
    std::cin >> n >> m;
    int start, finish;
    std::cin >> start >> finish;
    double inf = 1000000000.0;
    std::vector<std::vector<double>> dist(n+1, std::vector<double>(n+1, inf));
    for(int i = 1; i < m + 1; i++){
        int v, u;
        double p;
        std::cin >> v >> u >> p;
        dist[v][u] = p / 100.0;
        dist[u][v] = p / 100.0;
        
    }
    for (int i = 1; i < n + 1; i++){
        dist[i][i] = 0.0;
    }
    for (int k = 1; k < n + 1; k++) {
        for (int from = 1; from < n + 1; from++) {
            for (int to = 1; to < n + 1; to++) {
                if (dist[from][k] != inf && dist[k][to] != inf) {
                    dist[from][to] = std::min(dist[from][to], dist[from][k] + (1.0 - dist[from][k]) * dist[k][to]);
                }
            }
        }
    }
    std::cout << std::fixed << std::setprecision(3)<< dist[start][finish];
} 
