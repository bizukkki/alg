#include <iostream>
#include <vector>
#include <string>

struct Node {
    std::vector<Node*> to;
    int cnt = 0;
    bool terminal = false;
    Node() {
        to.resize(26, nullptr);
    }
};

class Tree {
private:
    Node* root;
public:
    Tree() {
        root = new Node;
    }
    void add(std::string s) {
        Node* runner = root;
        for (size_t i = 0; i < s.size(); i++) {
            int ch = s[i] - 'a';
            if (runner->to[ch] == nullptr) {
                runner->to[ch] = new Node;
            }
            runner = runner->to[ch];
            runner->cnt++;
        }
        runner->terminal = true;
    }
    std::string get_k(int k) {
        Node* runner = root;
        std::string answer;
        while (true) {
            if (runner->terminal) {
                if (k == 1) {
                    return answer;
                }
                k--;
            }
            for (int ch = 0; ch < 26; ch++) {
                Node* next = runner->to[ch];
                if (next == nullptr) {
                    continue;
                }
                if (next->cnt < k) {
                    k -= next->cnt;
                } else {
                    answer += char('a' + ch);
                    runner = next;
                    break;
                }
            }
        }
    }
    Node* get_root() {
        return root;
    }
};

int main() {
    int n;
    std::cin >> n;
    Tree tree;
    std::vector<Node*> v(n + 1);
    v[1] = tree.get_root();
    int answer = 0;
    for (int i = 1; i < n + 1; i++) {
        int p;
        char c;
        std::cin >> p >> c;
        int ch = c - 'a';
        Node* runner = v[p];
        if (runner->to[ch] == nullptr) {
            runner->to[ch] = new Node;
            answer++;
        }
        v[i + 1] = runner->to[ch];
        std::cout << answer << '\n';
    }
}
