#include <iostream>
#include <vector>
#include <map>

bool Isnum(std::string& s) {
    for (char c : s) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}
class DSU {
private:
    std::map<std::string, std::string> parent_;
    std::map<std::string, int> weight_;
    std::map<std::string, int> value_;

public:
    DSU(std::vector<std::string>& data) {
        for (auto s : data) {
            if (parent_.find(s) == parent_.end()) {
                parent_[s] = s;
                weight_[s] = 1;
                if (Isnum(s)) {
                    value_[s] = std::stoi(s);
                } else {
                    value_[s] = 0;
                }
            }
        }
    }
    std::string Leader(std::string v) {
        if (parent_[v] == v) {
            return v;
        }
        parent_[v] = Leader(parent_[v]);
        return parent_[v];
    }
    bool Unite(std::string a, std::string b) {
        a = Leader(a);
        b = Leader(b);
        if (a == b) return true;
        if (value_[a] != 0 && value_[b] != 0 && value_[a] != value_[b]) {
            return false;
        }
        if (weight_[a] < weight_[b]) std::swap(a, b);
        parent_[b] = a;
        weight_[a] += weight_[b];
        if (value_[a] == 0) {
            value_[a] = value_[b];
        }
        return true;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> data_1;
    std::vector<std::string> data_2;
    std::vector<std::string> data_all;

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s; 
        data_1.push_back(s);
        data_all.push_back(s);
    }

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s; 
        data_2.push_back(s);
        data_all.push_back(s);
    }
    DSU dsu(data_all);
    for (int i = 0; i < n; ++i) {
        if (!dsu.Unite(data_1[i], data_2[i])) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}