#include <iostream>
#include <vector>
#include <queue>

struct Edge {
    int to;
    int capacity;
    int flow;
    int back;
};

bool bfs(int start, int finish, std::vector<std::vector<Edge>>& graph, std::vector<int>& p_vert, std::vector<int>& p_edge) {
    fill(p_vert.begin(), p_vert.end(), -1);
    fill(p_edge.begin(), p_edge.end(), -1);
    std::queue<int> q;
    q.push(start);
    p_vert[start] = start; 
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == finish) return true;
        for (int i = 0; i < graph[v].size(); ++i) {
            Edge& edge = graph[v][i];
            if (edge.capacity - edge.flow > 0 && p_vert[edge.to] == -1) {
                p_vert[edge.to] = v;
                p_edge[edge.to] = i;
                q.push(edge.to);
            }
        }
    }
    return p_vert[finish] != -1;
}

int get_flow(int start, int finish, int n, std::vector<std::vector<Edge>>& graph) {
    int max_flow = 0;
    std::vector<int> p_vert(n + 1);
    std::vector<int> p_edge(n + 1);
    while (bfs(start, finish, graph, p_vert, p_edge)) {
        int path_flow = 2e9;
        int cur = finish;
        while (cur != start) {
            int vert = p_vert[cur];
            int edge = p_edge[cur];
            path_flow = std::min(path_flow, graph[vert][edge].capacity - graph[vert][edge].flow);
            cur = vert;
        }
        cur = finish;
        while (cur != start) {
            int vert = p_vert[cur];
            int edge = p_edge[cur];
            graph[vert][edge].flow += path_flow;
            int b_idx = graph[vert][edge].back;
            graph[cur][b_idx].flow -= path_flow;
            cur = vert;
        }
        max_flow += path_flow;
        if (max_flow >= 2) return max_flow;
    }
    return max_flow;
}

void get_path(int start, int finish, std::vector<std::vector<Edge>>& graph, std::vector<int>& path) {
    int cur = start;
    path.push_back(cur);
    while (cur != finish) {
        for (auto& edge : graph[cur]) {
            if (edge.capacity == 1 && edge.flow == 1) {
                edge.flow = 0;
                cur = edge.to;
                path.push_back(cur);
                break;
            }
        }
    }
}

int main() {
    int n, m, a, h;
    std::cin >> n >> m >> a >> h;
    std::vector<std::vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        int u_size = graph[u].size();
        int v_size = graph[v].size();
        graph[u].push_back({v, 1, 0, v_size});
        graph[v].push_back({u, 0, 0, u_size});
    }
    int max_flow =  get_flow(a, h, n, graph);
    if (max_flow >= 2){
        std::cout << "YES\n";
        std::vector<int> path1;
        std::vector<int> path2;
        get_path(a, h, graph, path1);
        get_path(a, h, graph, path2);
        for (int v : path1) {
            std::cout << v << " ";
        }
        std::cout << "\n";
        for (int v : path2) {
            std::cout << v << " ";
        }
    } else std::cout << "NO";
}
