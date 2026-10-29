#include <iostream>
#include <vector>

class PersisStack {
private:
    struct Node {
        int prev;
        long long sum;
    };
    std::vector<Node> tree_nodes;
    std::vector<int> version_roots;
    long long global_sum;
public:
    PersisStack(int n) {
        tree_nodes.reserve(n + 1);
        version_roots.reserve(n + 1);
        tree_nodes.push_back({0, 0}); 
        version_roots.push_back(0);   
        global_sum = 0;
    }  
    
    long long get_sum() {
        return global_sum;
    }
    void push(int parent_id, int weight) {
        int parent_node = version_roots[parent_id];
        Node new_node;
        new_node.prev = parent_node;
        new_node.sum = tree_nodes[parent_node].sum + weight;
        global_sum += new_node.sum;
        tree_nodes.push_back(new_node);
        version_roots.push_back(tree_nodes.size() - 1);
    }

    void pop(int parent_id) {
        int parent_node = version_roots[parent_id];
        int new_head = tree_nodes[parent_node].prev;
        version_roots.push_back(new_head);
        global_sum += tree_nodes[new_head].sum;
    }
};



int main() {
    int n;
    std::cin >> n;
    PersisStack snowman(n);
    for (int i = 1; i <= n; ++i) {
        int t, m;
        std::cin >> t >> m;
        if (m > 0) {
            snowman.push(t, m);
        } else {
            snowman.pop(t);
        }
    }
    std::cout << snowman.get_sum();
}