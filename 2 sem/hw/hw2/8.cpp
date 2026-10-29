#include<iostream>
#include<vector>
#include <queue>

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

int main() {
    int n;
    std::cin>>n;
    Graph g(n);
    std::vector<int> out(n+1, 0);
    for (int v = 1; v < n + 1; v++){
        int k;
        std::cin >> k;
        for (int i = 0; i < k; i++) {
            int u;
            std::cin >> u;
            g.AddEdge(v, u);
            out[u]++;
        }
    }
    std::priority_queue<int> max_heap;
    for (int i = 1; i < n+1; i++) {
        if (out[i] == 0){
            max_heap.push(i);
        }
    }
    std::vector<int> answer;
    while(!max_heap.empty()) {
        int v = max_heap.top();
        max_heap.pop();
        answer.push_back(v);
        for (auto u : g.GetChildren(v)) {
            out[u]--;
            if (out[u] == 0) {
                max_heap.push(u);
            }
        } 
    }
    std::reverse(answer.begin(), answer.end());
    for(auto v : answer) std::cout << v << " ";
}