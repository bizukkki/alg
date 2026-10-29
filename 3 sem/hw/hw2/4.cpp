#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <array>

struct Node {
    std::array<int, 26> to{};
    int link = 0;
    int exit = 0;
    std::vector<int> numbers;
};

class AhoCor {
private:
    std::vector<Node> nodes;
public:
    AhoCor() {
        nodes.emplace_back();
    }
    void add(std::string s, int number) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nodes[v].to[c] == 0) {
                nodes[v].to[c] = nodes.size();
                nodes.emplace_back();
            }
            v = nodes[v].to[c];
        }
        nodes[v].numbers.push_back(number);
    }

    void build() {
        std::queue<int> q;
        for (int c = 0; c < 26; c++) {
            int u = nodes[0].to[c];
            if (u != 0) {
                nodes[u].link = 0;
                q.push(u);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int c = 0; c < 26; c++) {
                int u = nodes[v].to[c];
                if (u != 0) {
                    nodes[u].link = nodes[nodes[v].link].to[c];
                    if (!nodes[nodes[u].link].numbers.empty()) {
                        nodes[u].exit = nodes[u].link;
                    } else {
                        nodes[u].exit = nodes[nodes[u].link].exit;
                    }
                    q.push(u);
                } else {
                    nodes[v].to[c] = nodes[nodes[v].link].to[c];
                }
            }
        }
    }

    void find(std::string s, std::vector<std::vector<int>>& answer, std::vector<std::string>& patterns) {
        int v = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            v = nodes[v].to[c];
            int u = v;
            while (u != 0) {
                if (!nodes[u].numbers.empty()) {
                    for (int number : nodes[u].numbers) {
                        int start = i - patterns[number].size() + 2;
                        answer[number].push_back(start);
                    }
                }
                u = nodes[u].exit;
            }
        }
    }
};

int main() {
    std::string s;
    std::cin >> s;
    int n;
    std::cin >> n;
    std::vector<std::string> patterns(n);
    AhoCor aho;
    for (int i = 0; i < n; i++) {
        std::cin >> patterns[i];
        aho.add(patterns[i], i);
    }
    aho.build();
    std::vector<std::vector<int>> answer(n);
    aho.find(s, answer, patterns);
    for (int i = 0; i < n; i++) {
        std::cout << answer[i].size();
        for (int position : answer[i]) {
            std::cout << ' ' << position;
        }
        std::cout << '\n';
    }
}