#include <iostream>
#include <vector>
#include <cmath>

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

void dfs (Graph &g, int now, int p, std::vector<int> &parents, std::vector<int> &depth, int d, std::vector<bool> &vis) {
    vis[now] = true;
    parents[now] = p;
    depth[now] = d;
    for (int ch : g.GetChildren(now)) {
        if (!vis[ch]) dfs(g, ch, now, parents, depth, d+1, vis);
    }
}

int lsa(int a, int b,std::vector<std::vector<int>> &up, std::vector<int> &depth, int l) {
    if (depth[a] > depth[b]) std::swap(a, b);
    for (int i = l - 1; i >= 0; --i) {
        if (depth[up[b][i]] >= depth[a]) {
            b = up[b][i];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = l - 1; i >= 0; --i) {
        if (up[b][i] != up[a][i]) {
            b = up[b][i];
            a = up[a][i];
        }
    }
    return up[b][0];    

}
int main () {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    int v1, v2;
    for (int i = 1; i < n; i++) {
        std::cin >> v1 >> v2;
        g.AddEdge(v1, v2);
    }
    std::vector<int> parents(n + 1, 0);
    std::vector<bool> vis(n + 1, false);
    std::vector<int> depth(n + 1, 0);
    dfs(g, 1, 0, parents, depth, 0, vis);
    int l = int(log2(n)) + 1;
    std::vector<std::vector<int>> up(n + 1, std::vector<int> (l, 0));
    for (int i = 1; i < n + 1; i++) {
        up[i][0] = parents[i];
    }
    for (int k = 1; k < l; k++) {
        for (int i = 1; i < n + 1; i++){
            up[i][k] = up[up[i][k-1]][k-1];
        }
    }
    for (int i = 0; i < m; i++) {
        std::cin >> v1 >> v2;
        std::cout << depth[v1] + depth[v2] - 2 * depth[lsa(v1, v2, up, depth, l)] << "\n";
    }
}