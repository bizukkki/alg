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

void dfs(Graph &g, int now, int p, std::vector<bool> &visited, std::vector<int> &parents, std::vector<int> &count_v) {
    visited[now] = true;
    parents[now] = p;
    for (auto i : g.GetChildren(now)) {
        if (!visited[i]) {
            dfs(g, i, now, visited, parents, count_v);
        }
    }
    for (auto i : g.GetChildren(now)) {
        if (i != p){
            count_v[now] += count_v[i];
        }
    }

}
int main() {
    int n;
    std::cin >> n;
    Graph g(n);
    for (int i = 0; i < n - 1; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        g.AddEdge(v1, v2);
        g.AddEdge(v2, v1);
    }
    std::vector<bool> visited(n + 1, false);
    std::vector<int> count_vertex(n + 1, 1);
    std::vector<int> parents(n + 1, 0);
    dfs(g, 1, 0, visited, parents, count_vertex);
    int answer = -1;
    for (int i = 1; i < n+1; ++i){
        bool flag = true; 
        if (i == 1) {
            if (g.GetChildren(i).size() > 1) {
                for (size_t ch = 1; ch < g.GetChildren(i).size(); ch++) {
                    if (count_vertex[g.GetChildren(i)[ch]] != count_vertex[g.GetChildren(i)[ch-1]]){
                        flag = false;
                        break;
                    }
                }
            } else flag = false;
        } else {
            int comp = 0;
            for(auto ch : g.GetChildren(i)) {
                if (ch == parents[i]) continue;
                if (!comp) comp = count_vertex[ch];
                if (comp != count_vertex[ch]){
                    flag = false;
                    break;
                }
            }
            if (n - count_vertex[i] != comp) flag = false;

        }
        if (flag){
            answer = i;
            break;
        }
    }
    std::cout << answer;
}
