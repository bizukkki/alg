#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

struct Node {
    char ch = '\0';
    int freq = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(char c, int f) : ch(c), freq(f) {}
    Node(int f, Node* l, Node* r) : freq(f), left(l), right(r) {}
};

struct CompareNodes {
    bool operator()(Node* const& n1, Node* const& n2) {
        return n1->freq > n2->freq; 
    }
};

class HuffTree {
public:
    void build_from_text(const std::string& text) {
        if (text.empty()) return;
        std::map<char, int> freqs;
        for (char c : text) {
            freqs[c]++;
        }
        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
        for (auto const& [ch, freq] : freqs) {
            pq.push(new Node(ch, freq));
        }
        if (pq.size() == 1) {
            Node* lone_leaf = pq.top();
            pq.pop();
            root = new Node(lone_leaf->freq, lone_leaf, nullptr);
            return;
        }
        while (pq.size() > 1) {
            Node* left_child = pq.top();
            pq.pop();
            Node* right_child = pq.top();
            pq.pop();
            Node* parent = new Node(left_child->freq + right_child->freq, left_child, right_child);
            pq.push(parent);
        }

        root = pq.top();
    }


    void print_codes() {
        std::vector<std::string> answer;
        std::string current_code;
        get_codes_dfs(root, current_code, answer);
        std::cout << "size" << answer.size() << '\n';
        for (const std::string& s : answer) {
            std::cout << s << '\n';
        }
    }

private:
    Node* root = nullptr;

    void get_codes_dfs(Node* current, std::string& current_code, std::vector<std::string>& answer) {
        if (current == nullptr) return;
        if (current->left == nullptr && current->right == nullptr) {
            std::string result = "'";
            result += current->ch;
            result += "': ";
            result += current_code;
            answer.push_back(result);
            return;
        }
        current_code.push_back('0');
        get_codes_dfs(current->left, current_code, answer);
        current_code.back() = '1';
        get_codes_dfs(current->right, current_code, answer);
        current_code.pop_back();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (std::cin >> n) {
        std::string text;
        std::getline(std::cin, text);
        for (int i = 0; i < n; i++) {
            std::getline(std::cin, text);
            std::cout << " " << i + 1 << " " << '\n';
            HuffTree tree;
            tree.build_from_text(text);
            tree.print_codes();
            std::cout << '\n';
        }
    }
    return 0;
}