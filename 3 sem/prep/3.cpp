#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <array>

struct Node {
    std::array<int, 26> to{};
    int link = 0;
    int exit = 0;
    int terminal = 0;
};

class AhoCor {
private:
    std::vector<Node> nodes;
    std::vector<int> used;
    std::vector<int> jump;

public:
    AhoCor() {
        nodes.emplace_back();
    }

    void add(std::string s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nodes[v].to[c] == 0) {
                nodes[v].to[c] = nodes.size();
                nodes.emplace_back();
            }
            v = nodes[v].to[c];
        }
        nodes[v].terminal++;
    }

    void build() {
        std::queue<int> q;
        for (int c = 0; c < 26; ++c) {
            int u = nodes[0].to[c];
            if (u != 0) {
                nodes[u].link = 0;
                q.push(u);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int c = 0; c < 26; ++c) {
                int u = nodes[v].to[c];
                if (u != 0) {
                    nodes[u].link = nodes[nodes[v].link].to[c];
                    if (nodes[nodes[u].link].terminal > 0) {
                        nodes[u].exit = nodes[u].link;
                    } else {
                        nodes[u].exit =
                            nodes[nodes[u].link].exit;
                    }
                    q.push(u);
                } else {
                    nodes[v].to[c] =
                        nodes[nodes[v].link].to[c];
                }
            }
        }
        used.assign(nodes.size(), 0);
        jump.assign(nodes.size(), 0);
    }

    int next_terminal(int v, int number) {
        if (v == 0) return 0;
        if (used[v] != number) return v;
        jump[v] = next_terminal(jump[v], number);
        return jump[v];
    }

    int count_in_string(std::string s) {
        int v = 0;
        int answer = 0;
        for (int i = 0; i < s.length(); i++) {
            int c = s[i] - 'a';
            v = nodes[v].to[c];
            int u;
            if (nodes[v].terminal > 0) {
                answer+=i;
            } 
        }
        return answer;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> passwords(n);
    AhoCor aho;
    for (int i = 0; i < n; ++i) {
        std::cin >> passwords[i];
        aho.add(passwords[i]);
    }
    aho.build();
    std::string text;
    std::cin >> text;
    std::cout << aho.count_in_string(text);

}