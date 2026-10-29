#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

int GetMask(const std::string& s, int m) {
    int mask = 0;
    for (int i = 0; i < m; ++i) {
        if (s[i] != '?') {
            mask |= (1 << i);
        }
    }
    return mask;
}

long long GetLetters(const std::string& s, int submask, int m) {
    long long code = 0;
    for (int i = 0; i < m; ++i) {
        if (submask & (1 << i)) {
            code = code * 26 + (s[i] - 'a');
        }
    }
    return code;
}

long long MakeKey(int mask, int submask, const std::string& s, int m, long long base) {
    long long letters_code = GetLetters(s, submask, m);
    long long key = mask;
    key = key * 64 + submask;
    key = key * base + letters_code;
    return key;
}

int main() {
    int n;
    int m;
    std::cin >> n >> m;
    long long base = pow(26, m);
    std::unordered_map<long long, long long> dict;
    long long answer = 0;
    int total_masks = 1 << m;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        int mask = GetMask(s, m);
        for (int prev_mask = 0; prev_mask < total_masks; ++prev_mask) {
            int common = mask & prev_mask;
            long long key = MakeKey(prev_mask, common, s, m, base);
            if (dict.find(key) != dict.end()) {
                answer += dict[key];
            }
        }
        int submask = mask;
        while (true) {
            long long key = MakeKey(mask, submask, s, m, base);
            dict[key]++;
            if (submask == 0) {
                break;
            }
            submask = (submask - 1) & mask;
        }
    }
    std::cout << answer;
}