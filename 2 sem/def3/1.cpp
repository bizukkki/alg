#include <iostream>
#include <vector>
#include <cmath>

class Graph {
private:
    std::vector<std::vector<int>> adj_;
    std::vector<std::vector<int>> weight_;
    int size_;
public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
        weight_.resize(n + 1);
        for (auto i : weight_) {
            i.resize(n + 1);
        }
    }
    void AddEdge(int from, int to) {
        adj_[from].push_back(to);
    }
    std::vector<int>& GetChildren(int v) {
        return adj_[v];
    }
    int get_edge(int a, int b) {
        return weight_[a][b];
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

int lsa(int a, int b,std::vector<std::vector<int>> &up, std::vector<int> &depth, int l,
    long long len, std::vector<std::vector<int>> &weight) {
    if (depth[a] > depth[b]) std::swap(a, b);
    for (int i = l - 1; i >= 0; --i) {
        if (depth[up[b][i]] >= depth[a]) {
            len = len + weight[b][up[b][i]];
            b = up[b][i];
        }
    }
    if (a == b) {
        return len;
    }
    for (int i = l - 1; i >= 0; --i) {
        if (up[b][i] != up[a][i]) {
            len = len + weight[b][up[b][i]];
            len = len + weight[a][up[a][i]];
            b = up[b][i];
            a = up[a][i];
        }
    }
    return len;    

}
int main () {
    int n;
    std::cin >> n;
    Graph g(n);
    int p, w;
    std::vector<std::vector<int>> weight(n + 1, std::vector<int>(n+1, 0));
    for (int i = 2; i < n + 1; i++) {
        std::cin >> p >> w;
        g.AddEdge(p, i);
        weight[p][i] = w;
        //std::cout <<  weight[p][i] << "\n";
    }
    std::vector<int> parents(n + 1, 0);
    std::vector<bool> vis(n + 1, false);
    std::vector<int> depth(n + 1, 0);

    dfs(g, 1, 0, parents, depth, 0, vis);
    int l = int(log2(n)) + 1;
    std::vector<std::vector<int>> up(n, std::vector<int> (l, 0));
    for (int i = 1; i < n + 1; i++) {
        up[i][0] = parents[i];
    }
    for (int k = 1; k < l; k++) {
        for (int i = 1; i < n + 1; i++){
            up[i][k] = up[up[i][k-1]][k-1];
        }
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int v1, v2;
        std::cin >> v1 >> v2;
        int len  = lsa(v1, v2, up, depth, l, 0, weight);
        std::cout << len << "\n";
    }
}



