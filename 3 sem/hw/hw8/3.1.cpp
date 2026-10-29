#include <iostream>
#include <vector>
#include <queue>
#include <string>

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
    }
    return max_flow;
}

struct Card {
    char face;
    char back;
    bool used;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<Card> cards(n + 1);
    std::vector<int> chars(26, 0);
    for (int i = 1; i <= n; ++i) {
        char c1, c2;
        std::cin >> c1 >> c2;
        cards[i] = {c1, c2, false};
        chars[c1 - 'a']++;
        if (c1 != c2) {
            chars[c2 - 'a']++;
        }
    }

    std::string str;
    std::cin >> str;
    int l = str.length();
    std::vector<int> need(26, 0);
    for (char c : str) {
        need[c - 'a']++;
    }
    int start = 0;
    int finish = 27;
    std::vector<std::vector<Edge>> graph(finish + 1);
    for (int i = 0; i < 26; ++i) {
        if (chars[i] > 0) {
            int u_size = graph[start].size();
            int v_size = graph[i + 1].size();
            graph[start].push_back({i + 1, chars[i], 0, v_size});
            graph[i + 1].push_back({start, 0, 0, u_size});
        }
        if (need[i] > 0) {
            int u_size = graph[i + 1].size();
            int v_size = graph[finish].size();
            graph[i + 1].push_back({finish, need[i], 0, v_size});
            graph[finish].push_back({i + 1, 0, 0, u_size});
        }
    }
    int total_flow = get_flow(start, finish, finish + 1, graph);
    if (total_flow == l) {
        std::vector<int> take_count(26, 0);
        for (int i = 0; i < 26; ++i) {
            for (const auto& edge : graph[i + 1]) {
                if (edge.to == finish) {
                    take_count[i] = edge.flow;
                }
            }
        }
        std::vector<std::vector<int>> letters(26);
        for (int i = 1; i <= n; ++i) {
            int idx = cards[i].face - 'a';
            if (take_count[idx] > 0) {
                take_count[idx]--;
                letters[idx].push_back(i);
                cards[i].used = true;
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (cards[i].used) continue;
            int idx = cards[i].back - 'a';
            if (take_count[idx] > 0) {
                take_count[idx]--;
                letters[idx].push_back(-i);
                cards[i].used = true;
            }
        }
        for (int i = 0; i < l; ++i) {
            int idx = str[i] - 'a';
            int card_id = letters[idx].back();
            letters[idx].pop_back();
            std::cout << card_id << " ";
        }
    } else {
        std::cout << "IMPOSSIBLE\n";
    }
}