#include <iostream>
#include <vector>
#include <queue>

struct Word {
    std::string text;
    int count;
    bool operator> (const Word& other) const {
        if (count != other.count) {
            return count > other.count;
        }
        return text > other.text;
    }
};

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector< std::priority_queue< Word, std::vector<Word>, std::greater<Word>> > words(26);
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        int l = s[0] - 'a';
        words[l].push({s, 0});
    }
    std::vector<std::string> answer;
    for (int i = 0; i < k; ++i) {
        char c;
        std::cin >> c;
        int l = c - 'a';
        Word current = words[l].top();
        words[l].pop();
        answer.push_back(current.text);
        current.count++;
        words[l].push(current);
    }
    for (auto s : answer) std::cout << s << "\n";
}