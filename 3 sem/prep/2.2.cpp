#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Node {
    std::map<std::string, Node*> to; 
    int cnt = 0;
    bool terminal = false;
};

class Tree {
private:
    Node* root;
public:
    Tree() {
        root = new Node;
    }
    void add(const std::string& path) {
        Node* runner = root;
        std::string current_folder = "";
        for (char ch : path) {
            if (ch == '\\') {
                if (!current_folder.empty()) {
                    if (runner->to.find(current_folder) == runner->to.end()) {
                        runner->to[current_folder] = new Node();
                    }
                    runner = runner->to[current_folder];
                    current_folder = "";
                }
            } else {
                current_folder += ch;
            }
        }
        if (!current_folder.empty()) {
                if (runner->to.find(current_folder) == runner->to.end()) {
                    runner->to[current_folder] = new Node();
                }
                runner = runner->to[current_folder];
            }
    }
    Node* get_root() {
        return root;
    }
    void print_structure() {
        print_dfs(root, 0);\
    }

    void print_dfs(Node* v, int depth) {
        if (v == nullptr) return;
        for (auto [name, next_node] : v->to) {
            for (int i = 0; i < depth; ++i) {
                std::cout << " ";
            }
            std::cout << name << "\n";
            print_dfs(next_node, depth + 1);
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    Tree tree;
    for (int i = 0; i < n; ++i) {
        std::string path;
        std::cin >> path;
        tree.add(path);
    }
    tree.print_structure();
}
