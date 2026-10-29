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

bool KuhnDfs(int u, std::string& str, std::vector<std::vector<int>>& letter_to_cards, std::vector<int>& used, int num, std::vector<int>& w) {
    if (used[u] == num) return false; 
    used[u] = num;
    char need = str[u - 1];
    int idx = need - 'a';
    for (int v : letter_to_cards[idx]) {
        if (w[v] == -1 || KuhnDfs(w[v], str, letter_to_cards, used, num, w)) {
            w[v] = u;
            return true;
        }
    }
    return false;
}

struct Card {
    char face;
    char back;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Card> cards(n + 1);
    std::vector<std::vector<int>> letter_to_cards(26);
    char ch1, ch2;
    for (int i = 1; i <= n; ++i) {
        std::cin >> ch1 >> ch2;
        cards[i] = {ch1, ch2};
        letter_to_cards[ch1 - 'a'].push_back(i);
        if (ch1 != ch2) {
            letter_to_cards[ch2 - 'a'].push_back(i);
        }
    }
    std::string str;
    std::cin >> str;
    int l = str.length();
    std::vector<int> w(n + 1, -1); 
    for (int u = 1; u <= l; ++u) {
        char need = str[u - 1];
        int idx = need - 'a';
        for (int v : letter_to_cards[idx]) {
            if (w[v] == -1) {
                w[v] = u;
                break;
            }
        }
    }
    std::vector<bool> matched_A(l + 1, false);
    int match_count = 0;
    for (int v = 1; v <= n; ++v) {
        if (w[v] != -1) {
            matched_A[w[v]] = true;
            match_count++;
        }
    }
    std::vector<int> used(l + 1, 0); 
    int cur_num = 0;
    for (int u = 1; u <= l; ++u) {
        if (!matched_A[u]) {
            cur_num++;
            if (KuhnDfs(u, str, letter_to_cards, used, cur_num, w)) {
                match_count++;
            }
        }
    }
    if (match_count == l) {
        std::vector<int> ans(l + 1);
        for (int v = 1; v <= n; v++) {
            if(w[v] != -1) {
                int pos = w[v];
                int id = v;
                if (cards[id].face == str[pos - 1]) {
                    ans[pos] = id;
                } else {
                    ans[pos] = -id;
                }
            }
        }
        for (int i = 1; i <= l; ++i) {
            std::cout << ans[i] << " ";
        }
    } else {
        std::cout << "IMPOSSIBLE";
    }
}