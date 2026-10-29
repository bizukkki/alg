#include <iostream>
#include <vector>


struct Apple{
    int x;
    int y;
    int z;
    int r;
};

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

int dist (Apple i, Apple j) {
    int x = (i.x - j.x) * (i.x - j.x);
    int y = (i.y - j.y) * (i.y - j.y);
    return x + y;

}
void dfs(Graph &g, int now, std::vector<bool> &v) {
    v[now] = true;
    for (int i : g.GetChildren(now)) {
        if (!v[i]) dfs(g, i, v);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Apple> apples(n+1);
    for (int i = 1; i < n + 1; i++) {
        Apple a;
        std::cin >> a.x >> a.y >> a.z >> a.r;
        apples[i] = a;
    }
    Graph g(n);
    for (int i = 1; i < n +1; i++) {
        for (int j = 1; j < n+1; j++) {
            int r1 = apples[i].r;
            int r2 = apples[j].r;
            if ((dist(apples[i], apples[j]) <= (r1 + r2) * (r1 + r2) ) && apples[i].z >= apples[j].z) {
                g.AddEdge(i, j);
            }
        }
    }
    std::vector<bool> visited(n+1, false);
    dfs(g, 1, visited);
    std::vector<int> answer;
    for (int i = 0; i < n + 1; ++i) {
        if (visited[i]) answer.push_back(i);
    }
    std::cout << answer.size() << std::endl;
    for (int i : answer) {
        std::cout<< i << " ";
    }
}