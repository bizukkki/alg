#include <iostream>
#include <vector>
#include <cmath>
struct Edge{
    int to;
    int cost;
};

class Graph {
private:
    std::vector<std::vector<Edge>> adj_;
    int size_;
public:
    Graph(int n) : size_(n) {
        adj_.resize(n+1);
    }
    void AddEdge(int from, int to, int cost) {
        adj_[from].push_back({to, cost});
    }
    std::vector<Edge>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
};

void dfs (Graph &g, int now, int p, std::vector<int> &parents, std::vector<int> &depth, int d, std::vector<int> &cost_p) {
    parents[now] = p;
    depth[now] = d;
    for (auto ch : g.GetChildren(now)) {
        cost_p[ch.to] = ch.cost;
        dfs(g, ch.to, now, parents, depth, d+1, cost_p);
    }
}

int get_min(int a, int b, std::vector<std::vector<int>> &up, std::vector<int> &depth, int l, std::vector<std::vector<int>> &mn) {
    if (depth[a] > depth[b]) std::swap(a, b);
    int answ = 1e9;
    for (int i = l - 1; i >= 0; --i) {
        if (depth[up[b][i]] >= depth[a]) {
            answ = std::min(answ, mn[b][i]);
            b = up[b][i];
        }
    }
    if (a == b) {
        return answ;
    }
    for (int i = l - 1; i >= 0; --i) {
        if (up[b][i] != up[a][i]) {
            answ = std::min(answ, mn[b][i]);
            answ = std::min(answ, mn[a][i]);
            b = up[b][i];
            a = up[a][i];
        }
    }
    answ = std::min(answ, mn[a][0]);
    answ = std::min(answ, mn[b][0]);
    return answ;    

}
int main () {
    int n;
    std::cin >> n;
    Graph g(n);
    int p, cost;
    for (int i = 2; i < n + 1; i++) {
        std::cin >> p >> cost;
        g.AddEdge(p, i, cost);
    }
    std::vector<int> parents(n + 1, 0);
    std::vector<int> depth(n + 1, 0);
    std::vector<int> cost_p(n+1, 1e9);
    dfs(g, 1, 1, parents, depth, 0, cost_p);
    int l = int(log2(n)) + 1;
    std::vector<std::vector<int>> up(n + 1, std::vector<int> (l, 0));
    std::vector<std::vector<int>> mn(n + 1, std::vector<int> (l, 1e9));
    for (int i = 1; i < n + 1; i++) {
        up[i][0] = parents[i];
        mn[i][0] = cost_p[i];
    }
    for (int k = 1; k < l; k++) {
        for (int i = 1; i < n + 1; i++){
            up[i][k] = up[up[i][k-1]][k-1];
            mn[i][k] = std::min( mn[i][k - 1], mn[up[i][k - 1]][k - 1]);
        }
    }
    int m;
    std::cin >> m;
    int x, y;
    std::vector<int> answer;
    for (int i = 0; i < m; i++){
        std::cin >> x >> y;
        answer.push_back(get_min(x, y, up, depth, l, mn));
    }
    for (auto a : answer) std::cout << a << "\n";
}