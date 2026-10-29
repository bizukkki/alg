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

int main() {
    int n;
    std::cin >> n;
    std::string name;
    std::cin >> name;
    int m = name.length();
    Graph g(m);
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        for (int pos = 0; pos < m; ++pos) {
            for (int k = 0; k < 6; ++k) {
                if (s[k] == name[pos]) {
                    g.AddEdge(pos + 1, i);
                    break;
                }
            }
        }
    }
    auto result = FindMatch(g, n);
    if (result.size() == m) {
        std::cout << "YES\n";
        std::vector<int> ans(m + 1);
        for (auto e : result) {
            ans[e.first] = e.second;
        }
        for (int i = 1; i <= m; ++i) {
            std::cout << ans[i] << " ";
        }
    } else {
        std::cout << "NO";
    }
}