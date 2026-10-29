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

void dfs (Graph &g, int now, std::vector<int> &comp, std::vector<int> &tsort, int k) {
    comp[now] = k;
    for (auto i : g.GetChildren(now)) {
        if (comp[i] == 0) {
            dfs(g, i, comp, tsort, k);
        }
    }
    tsort.push_back(now);
}
int main() {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    Graph g_reversed(n);
    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        g.AddEdge(v1, v2);
        g_reversed.AddEdge(v2, v1);
    }
    std::vector<int> comp(n+1, 0);
    int k = 0;
    std::vector<int> topol_sort;
    for (int v = 1; v < n + 1; ++v){
        if (comp[v] == 0) {
            dfs(g, v, comp, topol_sort, 1);
        } 
    }
    std::reverse(topol_sort.begin(), topol_sort.end());
    std::fill(comp.begin(), comp.end(), 0);
    std::vector<int> trash;
    for (auto v : topol_sort) {
        if (comp[v] == 0) {
            k++;
            dfs(g_reversed, v, comp, trash, k);
        }
    }
    std::cout << k << std::endl;
    for (int v = 1; v < n+1; v++) {
        std::cout << comp[v] << " ";
    }
}