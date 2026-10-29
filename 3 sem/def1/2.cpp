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
    int k = 0;
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
                k++;
            }
            runner = runner->to[ch];
            runner->cnt++;
        }
        runner->terminal = true;
    }
    int get_k() {
        return k;
    }
    
};

int main() {
    int n;
    std::cin >> n;
    Tree tree;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        tree.add(s);
        sum += s.size();
    }
    int k = tree.get_k();
    std::cout << sum << " " << k << " " << sum - k;
}