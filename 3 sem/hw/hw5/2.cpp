#include <iostream>
#include <vector>
#include <string>

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

bool can_color(Graph &g, int v, char c, std::vector<char> &ans) {
    for (int ch : g.GetChildren(v)) {
        if (ans[ch] == c) {
            return false;
        }
    }
    return true;
}


bool backtrack(Graph &g, int idx, std::vector<int> &order, std::string &old, std::vector<char> &ans) {
    if (idx >= order.size()) {
        return true;
    }

    int v = order[idx];
    char old_c = old[v - 1]; 
    char colors[] = {'R', 'G', 'B'};
    for (char c : colors) {
        if (c == old_c) continue;
        if (can_color(g, v, c, ans)) {
            ans[v] = c;
            if (backtrack(g, idx + 1, order, old, ans)) {
                return true;
            }
            ans[v] = 0;
        }
    }
    return false;
}

void build_order(Graph &g, int v, std::vector<bool> &visited, std::vector<int> &order) {
    visited[v] = true;
    order.push_back(v);
    for (int ch : g.GetChildren(v)) {
        if (!visited[ch]) {
            build_order(g, ch, visited, order);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    std::string old;
    std::cin >> old;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        if (u != v) {
            g.AddEdge(u, v);
            g.AddEdge(v, u);
        }
    }
    std::vector<int> order;
    std::vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            build_order(g, i, visited, order);
        }
    }
    std::vector<char> ans(n + 1, 0);
    if (backtrack(g, 0, order, old, ans)) {
        for (int i = 1; i <= n; ++i) {
            std::cout << ans[i];
        }
    } else {
        std::cout << "Impossible";
    }
    return 0;
}
