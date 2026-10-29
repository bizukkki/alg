
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

struct Edge {
    int to;
    int capacity;
    int flow;
    int back;
};

void add_edge(int u, int v, int capacity, std::vector<std::vector<Edge>>& graph) {
    int u_size = graph[u].size();
    int v_size = graph[v].size();
    graph[u].push_back({v, capacity, 0, v_size});
    graph[v].push_back({u, 0, 0, u_size});
}

bool bfs(int start, int finish, std::vector<std::vector<Edge>>& graph, std::vector<int>& level) {
    std::fill(level.begin(), level.end(), -1);
    std::queue<int> q;
    q.push(start);
    level[start] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < graph[v].size(); ++i) {
            Edge& edge = graph[v][i];
            if (edge.capacity - edge.flow > 0 &&
                level[edge.to] == -1) {
                level[edge.to] = level[v] + 1;
                q.push(edge.to);
            }
        }
    }

    return level[finish] != -1;
}

int dfs(int v, int finish, int pushed, std::vector<std::vector<Edge>>& graph, std::vector<int>& level, std::vector<int>& ptr) {
    if (v == finish || pushed == 0) {
        return pushed;
    }
    for (int& i = ptr[v]; i < graph[v].size(); ++i) {
        Edge& edge = graph[v][i];
        if (level[edge.to] != level[v] + 1 ||
            edge.capacity - edge.flow <= 0) {
            continue;
        }
        int flow = dfs(edge.to, finish, std::min(pushed, edge.capacity - edge.flow), graph, level, ptr);
        if (flow > 0) {
            edge.flow += flow;
            graph[edge.to][edge.back].flow -= flow;
            return flow;
        }
    }
    return 0;
}

int get_flow(int start, int finish, std::vector<std::vector<Edge>>& graph) {
    int n = graph.size();
    int max_flow = 0;
    std::vector<int> level(n);
    std::vector<int> ptr(n);
    while (bfs(start, finish, graph, level)) {
        std::fill(ptr.begin(), ptr.end(), 0);
        while (true) {
            int flow = dfs(start, finish, 1000000000, graph, level, ptr);
            if (flow == 0) {
                break;
            }
            max_flow += flow;
        }
    }
    return max_flow;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> cards(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> cards[i];
    }
    std::string s;
    std::cin >> s;
    int m = s.size();
    int start = 0;
    int letters = 1;
    int card_start = letters + 26;
    int finish = card_start + n;
    std::vector<std::vector<Edge>> graph(finish + 1);
    std::vector<int> count(26, 0);
    for (char c : s) {
        count[c - 'a']++;
    }
    for (int c = 0; c < 26; c++) {
        if (count[c] > 0) {
            add_edge(start, letters + c, count[c], graph);
        }
    }
    for (int i = 1; i <= n; i++) {
        int card = card_start + i - 1;
        int a = cards[i][0] - 'a';
        int b = cards[i][1] - 'a';
        if (count[a] > 0) {
            add_edge(letters + a, card, 1, graph);
        }
        if (b != a && count[b] > 0) {
            add_edge(letters + b, card, 1, graph);
        }
        add_edge(card, finish, 1, graph);
    }
    if (get_flow(start, finish, graph) != m) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }
    std::vector<std::vector<int>> used(26);
    for (int c = 0; c < 26; c++) {
        int v = letters + c;
        for (Edge& edge : graph[v]) {
            if (edge.to >= card_start && edge.to < finish && edge.flow == 1) {
                used[c].push_back(edge.to - card_start + 1);
            }
        }
    }
    std::vector<int> answer(m);
    for (int i = 0; i < m; i++) {
        int c = s[i] - 'a';
        int card = used[c].back();
        used[c].pop_back();
        if (cards[card][0] == s[i]) {
            answer[i] = card;
        } else {
            answer[i] = -card;
        }
    }
    for (int i = 0; i < m; i++) {
        std::cout << answer[i] << " ";
    }
}