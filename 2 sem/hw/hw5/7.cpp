#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    int inf = 1e9;
    std::vector<int> dist(n+1, inf);
    dist[1] = 0;
    for (int to = 2; to < n + 1; to++) {
        for(int from = 1; from < to; from++) {
            int w = (179 * from + 719 * to)%1000 - 500;
            if (dist[to] > dist[from] + w){
                dist[to] = dist[from] + w;
            }
        }
    }
    std::cout << dist[n];
}  