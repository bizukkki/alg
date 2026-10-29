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

// Твой BFS (добавлен std:: перед fill)
bool bfs(int start, int finish, std::vector<std::vector<Edge>>& graph, std::vector<int>& p_vert, std::vector<int>& p_edge) {
    std::fill(p_vert.begin(), p_vert.end(), -1);
    std::fill(p_edge.begin(), p_edge.end(), -1);
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

// Твой get_flow
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

// Вспомогательная структура, чтобы помнить оригинальный номер карты при группировке
struct CardInfo {
    int id;
    char face;
    char back;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    
    // Группируем карточки по парам букв (всего не более 26 * 26 = 676 типов)
    std::vector<std::vector<CardInfo>> card_groups(676);
    for (int i = 1; i <= n; ++i) {
        char c1, c2;
        std::cin >> c1 >> c2;
        int u = c1 - 'a';
        int v = c2 - 'a';
        int min_val = std::min(u, v);
        int max_val = std::max(u, v);
        int group_idx = min_val * 26 + max_val;
        card_groups[group_idx].push_back({i, c1, c2});
    }

    std::string str;
    std::cin >> str;
    int l = str.length();
    
    std::vector<int> need(26, 0);
    for (char c : str) {
        need[c - 'a']++;
    }
    
    // Собираем только те типы карточек, которые у нас реально есть на руках
    std::vector<int> active_groups;
    for (int i = 0; i < 676; ++i) {
        if (!card_groups[i].empty()) {
            active_groups.push_back(i);
        }
    }
    
    int num_groups = active_groups.size();
    int start = 0;
    int letter_offset = num_groups;
    int finish = num_groups + 26 + 1; // Уникальный ID для стока
    
    std::vector<std::vector<Edge>> graph(finish + 1);
    
    // 1 & 2. Строим правильные ребра: Исток -> Группы карточек -> Буквы
    for (int g = 0; g < num_groups; ++g) {
        int group_idx = active_groups[g];
        int count = card_groups[group_idx].size();
        int group_node = g + 1;
        
        // Исток -> Группа карточек (вместимость = сколько таких карточек)
        int u_size = graph[start].size();
        int v_size = graph[group_node].size();
        graph[start].push_back({group_node, count, 0, v_size});
        graph[group_node].push_back({start, 0, 0, u_size});
        
        int c1 = group_idx / 26;
        int c2 = group_idx % 26;
        
        // Группа карточек -> Буква 1
        int b1_node = letter_offset + c1 + 1;
        u_size = graph[group_node].size();
        v_size = graph[b1_node].size();
        graph[group_node].push_back({b1_node, count, 0, v_size});
        graph[b1_node].push_back({group_node, 0, 0, u_size});
        
        // Группа карточек -> Буква 2 (если буквы на карточке разные)
        if (c1 != c2) {
            int b2_node = letter_offset + c2 + 1;
            u_size = graph[group_node].size();
            v_size = graph[b2_node].size();
            graph[group_node].push_back({b2_node, count, 0, v_size});
            graph[b2_node].push_back({group_node, 0, 0, u_size});
        }
    }
    
    // 3. Буквы -> Сток
    for (int i = 0; i < 26; ++i) {
        if (need[i] > 0) {
            int b_node = letter_offset + i + 1;
            int u_size = graph[b_node].size();
            int v_size = graph[finish].size();
            graph[b_node].push_back({finish, need[i], 0, v_size});
            graph[finish].push_back({b_node, 0, 0, u_size});
        }
    }
    
    // Считаем максимальный поток
    int total_flow = get_flow(start, finish, finish, graph);
    
    if (total_flow == l) {
        std::vector<std::vector<int>> letters(26);
        
        // Распределяем карточки по буквам на основе реального потока
        for (int g = 0; g < num_groups; ++g) {
            int group_idx = active_groups[g];
            int group_node = g + 1;
            auto& list_of_cards = card_groups[group_idx];
            
            int c1 = group_idx / 26;
            int c2 = group_idx % 26;
            
            int flow_to_c1 = 0;
            int flow_to_c2 = 0;
            
            for (const auto& edge : graph[group_node]) {
                if (edge.to == letter_offset + c1 + 1) {
                    flow_to_c1 = edge.flow;
                } else if (edge.to == letter_offset + c2 + 1) {
                    flow_to_c2 = edge.flow;
                }
            }
            
            int card_ptr = 0;
            // Забираем карточки под нужды первой буквы
            for (int k = 0; k < flow_to_c1; ++k) {
                CardInfo card = list_of_cards[card_ptr++];
                if (card.face - 'a' == c1) letters[c1].push_back(card.id);
                else letters[c1].push_back(-card.id);
            }
            // Забираем карточки под нужды второй буквы
            for (int k = 0; k < flow_to_c2; ++k) {
                CardInfo card = list_of_cards[card_ptr++];
                if (card.face - 'a' == c2) letters[c2].push_back(card.id);
                else letters[c2].push_back(-card.id);
            }
        }
        
        // Теперь пулы букв гарантированно заполнены верно, выводим ответ без RE
        for (int i = 0; i < l; ++i) {
            int idx = str[i] - 'a';
            int card_id = letters[idx].back();
            letters[idx].pop_back();
            std::cout << card_id << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}