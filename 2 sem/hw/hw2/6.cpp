#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> adj_;
    int size_;

public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
    }
    void AddEdge(int from, int to) {
        adj_[from].push_back(to);
    }
    std::vector<int>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
};

void dfs (Graph &g, int now, std::vector<int> &colors, std::vector<int> &tsort, long long &total, std::vector<int> &cost){
    colors[now] = 1;
    for (auto i : g.GetChildren(now)) {
        if (colors[i] == 0) {
            dfs(g, i, colors, tsort, total, cost);
        }
    }
    colors[now] = 2;
    tsort.push_back(now);
    total+=cost[now];
}
int main() {
    int n;
    std::cin >> n;
    std::vector<int> cost(n + 1, 0);
    for (int i = 1; i < n + 1; ++i){
        std::cin >> cost[i];
    }
    Graph g(n);
    for (int i = 1; i < n + 1; ++i){
        int k;
        std::cin>> k;
        if (k) {
            for(int j=0; j < k; ++j){
                int v;
                std::cin>>v;
                g.AddEdge(i, v);
            }
        }
    }
    std::vector<int> tsort;
    std::vector<int> colors(n+1, 0);
    long long total = 0;
    dfs(g, 1, colors, tsort, total, cost);
    std::cout << total << " " << tsort.size() << std::endl;
    for (auto v : tsort){
        std::cout << v << " ";
    }
}