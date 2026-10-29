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


void allowed_colors(char old_c, char &alt1, char &alt2) {
    if (old_c == 'R') { alt1 = 'G'; alt2 = 'B'; }
    else if (old_c == 'G') { alt1 = 'R'; alt2 = 'B'; }
    else if (old_c == 'B') { alt1 = 'R'; alt2 = 'G'; }
}

bool bfs(Graph &g, int start_v, char start_c, const std::string &old, std::vector<char> &ans) {
    std::vector<int> q;
    std::vector<int> changed; 
    ans[start_v] = start_c;
    q.push_back(start_v);
    changed.push_back(start_v);
    int head = 0;
    while (head < q.size()) {
        int u = q[head++];
        char u_color = ans[u];
        for (int ch : g.GetChildren(u)) {
            if (ans[ch] != 0) {
                if (ans[ch] == u_color) {
                    for (int v : changed) ans[v] = 0;
                    return false;
                }
                continue;
            }
            char alt1, alt2;
            allowed_colors(old[ch - 1], alt1, alt2);
            if (u_color == alt1) {
                ans[ch] = alt2;
                q.push_back(ch);
                changed.push_back(ch);
            } else if (u_color == alt2) {
                ans[ch] = alt1;
                q.push_back(ch);
                changed.push_back(ch);
            }
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m;
    std::cin >> n >> m;
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
    std::vector<char> ans(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == 0) {
            char alt1, alt2;
            allowed_colors(old[i - 1], alt1, alt2);
            if (bfs(g, i, alt1, old, ans)) {
                continue; 
            }
            if (bfs(g, i, alt2, old, ans)) {
                continue;
            }
            std::cout << "Impossible\n";
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i];
    }
    return 0;
}
