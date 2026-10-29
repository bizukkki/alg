#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

struct Node {
    std::map<char, int> next;
    std::vector<int> to;
    int link = 0;
    int terminal = 0;
    int exit = 0;
    Node() {
        to.resize(26, 0);
    }
};

class Tree {
private:
    std::vector<Node> nodes;
    std::vector<int> used;
    std::vector<int> jump;
public:
    Tree() {
        nodes.push_back(Node());
    }
    int get_root() {
        return 0;
    }
    void add_string(std::string s) {
        int runner = 0;
        for (size_t i = 0; i < s.size(); i++) {
            char ch = s[i];
            if (!nodes[runner].next.count(ch)) {
                nodes[runner].next[ch] = nodes.size();
                nodes.push_back(Node());
            }
            runner = nodes[runner].next[ch];
        }
        nodes[runner].terminal++;
    }
    void build_links() {
        for (char ch = 'a'; ch < 'a' + 26; ++ch) {
            if (nodes[0].next.count(ch)) {
                nodes[0].to[ch - 'a'] = nodes[0].next[ch];
            } else {
                nodes[0].to[ch - 'a'] = 0;
            }
        }
        std::queue<int> q;
        for (auto [ch, u] : nodes[0].next) {
            nodes[u].link = 0;
            q.push(u);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto [ch, u] : nodes[v].next) {
                nodes[u].link =
                    nodes[nodes[v].link].to[ch - 'a'];
                if (nodes[nodes[u].link].terminal > 0) {
                    nodes[u].exit = nodes[u].link;
                } else {
                    nodes[u].exit = nodes[nodes[u].link].exit;
                }
                for (char c = 'a'; c < 'a' + 26; ++c) {
                    if (nodes[u].next.count(c)) {
                        nodes[u].to[c - 'a'] =
                            nodes[u].next[c];
                    } else {
                        nodes[u].to[c - 'a'] =
                            nodes[nodes[u].link].to[c - 'a'];
                    }
                }
                q.push(u);
            }
        }
        used.resize(nodes.size(), 0);
        jump.resize(nodes.size(), 0);
    }

    int get_next_terminal(int v, int number) {
        if (v == 0) {
            return 0;
        }
        if (used[v] != number) {
            return v;
        }
        jump[v] = get_next_terminal(jump[v], number);
        return jump[v];
    }

    int count_in_string(std::string s, int number) {
        int runner = 0;
        int answer = 0;

        for (size_t i = 0; i < s.size(); i++) {
            int ch = s[i] - 'a';
            runner = nodes[runner].to[ch];
            int v;
            if (nodes[runner].terminal > 0) {
                v = runner;
            } else {
                v = nodes[runner].exit;
            }

            while (v != 0) {
                v = get_next_terminal(v, number);
                if (v == 0) {
                    break;
                }
                answer += nodes[v].terminal;
                used[v] = number;
                jump[v] = nodes[v].exit;
                v = nodes[v].exit;
            }
        }

        return answer;
    }
};

int main() {
    int n;
    std::cin >> n;
    Tree tree;
    std::vector<std::string> passwords(n);
    for (int i = 0; i < n; i++) {
        std::cin >> passwords[i];
        tree.add_string(passwords[i]);
    }
    tree.build_links();
    int answer = 0;
    for (int i = 0; i < n; i++) {
        answer += tree.count_in_string(passwords[i], i + 1);
    }
    std::cout << answer << '\n';
}