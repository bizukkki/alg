#include <iostream>
#include <vector>
#include <cmath>

class Graph {
private:
    std::vector<std::vector<int>> adj_;
    int size_;
public:
    Graph(int n) : size_(n) {
        adj_.resize(n);
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
    int p;
    for (int i = 1; i < n; i++) {
        std::cin >> p;
        g.AddEdge(p, i);
    }
    std::vector<int> parents(n, 0);
    std::vector<bool> vis(n, false);
    std::vector<int> depth(n, 0);
    dfs(g, 0, 0, parents, depth, 0, vis);
    int l = int(log2(n)) + 1;
    std::vector<std::vector<int>> up(n, std::vector<int> (l, 0));
    for (int i = 1; i < n; i++) {
        up[i][0] = parents[i];
    }
    for (int k = 1; k < l; k++) {
        for (int i = 1; i < n; i++){
            up[i][k] = up[up[i][k-1]][k-1];
        }
    }
    long long a1, a2, x, y, z;
    std::cin >> a1 >> a2>> x >> y >> z;
    long long answer = 0;
    long long prev = 0;
    for (int i = 0; i < m; i++) {
        int v1 = (a1 + prev) % n;
        int v2 = a2;
        prev = lsa(v1, v2, up, depth, l);
        answer+=prev;
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }
    std::cout << answer;
}