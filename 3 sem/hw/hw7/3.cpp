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

bool KuhnDfs(int u, Graph& g, std::vector<int>& used, std::vector<int>& w) {
    if (used[u] == 1) return false; 
    used[u] = 1;
    for (int v : g.GetChildren(u)) {
        if (w[v] == -1 || KuhnDfs(w[v], g, used, w)) {
            w[v] = u;
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> FindMatch(Graph& g, int m) {
    int n = g.Size();
    std::vector<int> w(m + 1, -1); 
    std::vector<int> used(n + 1, 0); 
    for (int u = 1; u <= n; ++u) {
        for (int v : g.GetChildren(u)) {
            if (w[v] == -1) {
                w[v] = u;
                break;
            }
        }
    }
    std::vector<bool> matched_A(n + 1, false);
    for (int v = 1; v <= m; ++v) {
        if (w[v] != -1) matched_A[w[v]] = true;
    }
    for (int u = 1; u <= n; ++u) {
        if (!matched_A[u]) {
            used.assign(n + 1, 0);
            KuhnDfs(u, g, used, w); 
        }
    }
    std::vector<std::pair<int, int>> result;
    for (int v = 1; v <= m; ++v) {
        if (w[v] != -1) {
            result.push_back({w[v], v});
        }
    }
    return result;
}

void Reachable(int u, Graph& g, std::vector<int>& w, std::vector<bool>& vis_A, std::vector<bool>& vis_B) {
    vis_A[u] = true;
    for (int v : g.GetChildren(u)) {
        if (!vis_B[v]) {
            vis_B[v] = true;
            if (w[v] != -1 && !vis_A[w[v]]) {
                Reachable(w[v], g, w, vis_A, vis_B);
            }
        }
    }
}

int main() {
    int tests;
    std::cin >> tests;
    while(tests--) {
        int m, n;
        std::cin >> m >> n;
        Graph g(m);
        for (int i = 1; i <= m; ++i) {
            std::vector<bool> knows(n + 1, false);
            int girl;
            std::cin >> girl;
            while (girl != 0) {
                knows[girl] = true;
                std::cin >> girl;
            }
            for (int j = 1; j <= n; j++) {
                if (!knows[j]) {
                    g.AddEdge(i, j);
                }
            }
        }
        auto match_edges = FindMatch(g, n);
        std::vector<int> w(n + 1, -1);
        std::vector<bool> matched_A(m + 1, false);
        for (auto& edge : match_edges) {
            w[edge.second] = edge.first;
            matched_A[edge.first] = true;
        }

        std::vector<bool> vis_A(m + 1, false);
        std::vector<bool> vis_B(n + 1, false);
        for (int u = 1; u <= m; ++u) {
            if (!matched_A[u]) {
                Reachable(u, g, w, vis_A, vis_B);
            }
        }

        std::vector<int> invited_b;
        for (int u = 1; u <= m; ++u) {
            if (vis_A[u]) invited_b.push_back(u);
        }

        std::vector<int> invited_g;
        for (int v = 1; v <= n; ++v) {
            if (!vis_B[v]) invited_g.push_back(v);
        }

        std::cout << invited_b.size() + invited_g.size() << "\n";
        std::cout << invited_b.size() << " " << invited_g.size() << "\n";
        
        for (size_t i = 0; i < invited_b.size(); ++i) {
            std::cout << invited_b[i] << " ";
        }
        std::cout << "\n";
        
        for (size_t i = 0; i < invited_g.size(); ++i) {
            std::cout << invited_g[i] << " ";
        }
        std::cout << "\n";
    }
}