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
    std::string get(int k) {
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
};

int main() {
    int n;
    std::cin >> n;
    Tree tree;
    std::string s;
    std::cin >> s;
    for (int i = 1; i < n; i++) {
        std::
        for (int j = 0; j < i; j++){

        }
    }
}
