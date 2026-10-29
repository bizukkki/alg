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

bool is_parent(int a, int b,std::vector<std::vector<int>> &up, std::vector<int> &depth, int l) {
    if (depth[b] <= depth[a]) return false;
    for (int i = l - 1; i >= 0; --i) {
        if (up[b][i] != 0 && depth[up[b][i]] > depth[a]) {
            b = up[b][i];
        }
    }
    return up[b][0] == a;

}
int main () {
    int n;
    std::cin >> n;
    Graph g(n);
    int root;
    int p;
    for (int i = 1; i < n + 1; i++) {
        std::cin >> p;
        if (p == 0) root = i;
        else g.AddEdge(p, i);
    }
    std::vector<int> parents(n+1);
    std::vector<bool> vis(n+1, false);
    std::vector<int> depth(n+1, 0);
    dfs(g, root, 0, parents, depth, 0, vis);
    std::vector<int> parent(n);
    int l = int(log2(n)) + 1;
    std::vector<std::vector<int>> up(n+1, std::vector<int> (l, 0));
    for (int i = 1; i < n +1; i++) {
        up[i][0] = parents[i];
    }
    for (int k = 1; k < l; k++) {
        for (int i = 1; i < n + 1; i++){
            up[i][k] = up[up[i][k-1]][k-1];
        }
    }
    int k;
    std::cin >> k;
    int a, b;
    std::vector<int> answer;
    for (int i = 0; i < k; i++){
        std::cin >> a >> b;
        if (is_parent(a, b, up, depth, l)) answer.push_back(1);
        else answer.push_back(0);
    }
    for (auto a : answer) std::cout << a << "\n";

}