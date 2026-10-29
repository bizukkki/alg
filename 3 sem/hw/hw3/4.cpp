#include <iostream>
#include <vector>
#include <string>

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
};

class HuffTree {
public:
    void build(const std::string& s) {
        root = new Node;
        Node* current = root;

        for (char c : s) {
            if (c == 'D') {
                current->left = new Node;
                current->left->parent = current;
                current = current->left;
            } else {
                while (current->parent != nullptr && current->parent->right == current) {
                    current = current->parent;
                }
                if (current->parent != nullptr) {
                    current = current->parent;
                    current->right = new Node;
                    current->right->parent = current;
                    current = current->right;
                }
            }
        }
    }

    void get_codes() {
        std::vector<std::string> answer;
        std::string code;
        get_codes(root, code, answer);
        std::cout << answer.size() << '\n';
        for (std::string s : answer) {
            std::cout << s << '\n';
        }
    }

private:
    Node* root = nullptr;
    void get_codes(Node* tree, std::string& code, std::vector<std::string>& answer) {
        if (tree == nullptr) {
            return;
        }
        if (tree->left == nullptr && tree->right == nullptr) {
            answer.push_back(code);
            return;
        }
        code.push_back('0');
        get_codes(tree->left, code, answer);

        code.back() = '1';
        get_codes(tree->right, code, answer);

        code.pop_back();
    }
};

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        HuffTree tree;
        tree.build(s);
        tree.get_codes();
    }
}
