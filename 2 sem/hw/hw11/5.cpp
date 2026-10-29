#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
struct Edge {
    int to;
    int dir;
};
class Graph {
private:
    std::vector<std::vector<Edge>> adj_;
    int size_;
public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
    }
    void AddEdge(int from, int to, int dir) {
        adj_[from].push_back({to, dir});
    }
    std::vector<Edge>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
};

void dfs(Graph &g, int now, int p, std::vector<int> &parents,  std::vector<int> &depth, std::vector<int> &down, std::vector<int> &up_dir) {
    parents[now] = p;
    for (auto e : g.GetChildren(now)) {
        int ch = e.to;
        if (ch == p) {
            continue;
        }
        depth[ch] = depth[now] + 1;
        down[ch] = down[now];
        up_dir[ch] = up_dir[now];
        if (e.dir == 1) {
            down[ch]++;
        } else {
            up_dir[ch]++;
        }
        dfs(g, ch, now, parents, depth, down, up_dir);
    }
}

int lca(int a, int b, std::vector<std::vector<int>> &up, std::vector<int> &depth, int l) {
    if (depth[a] > depth[b]) {
        std::swap(a, b);
    }
    for (int i = l - 1; i >= 0; --i) {
        if (depth[up[b][i]] >= depth[a]) {
            b = up[b][i];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = l - 1; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

int main() {
    int n;
    std::cin >> n;
    Graph g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        g.AddEdge(a, b, 1);
        g.AddEdge(b, a, 0);
    }
    std::vector<int> parents(n + 1, 0);
    std::vector<int> depth(n + 1, 0);
    std::vector<int> down(n + 1, 0);
    std::vector<int> up_dir(n + 1, 0);
    dfs(g, 1, 1, parents, depth, down, up_dir);
    int l = int(log2(n)) + 1;
    std::vector<std::vector<int>> up(n + 1, std::vector<int>(l, 1));
    for (int i = 1; i <= n; i++) {
        up[i][0] = parents[i];
    }
    for (int k = 1; k < l; k++) {
        for (int i = 1; i <= n; i++) {
            up[i][k] = up[up[i][k - 1]][k - 1];
        }
    }
    int m;
    std::cin >> m;
    std::vector<int> answer;
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        int c = lca(x, y, up, depth, l);
        if (down[x] - down[c] == 0 && up_dir[y] - up_dir[c] == 0) {
            answer.push_back(1);
        } else answer.push_back(0);
    }
    for (auto a : answer) {
        if (a) std::cout << "Yes\n";
        else  std::cout << "No\n";
    }
}