#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

void pack_dict(std::unordered_map<std::string, int>& dict, int& next_code) {
    dict.clear();
    for (int i = 0; i < 26; i++) {
        dict[std::string(1, char('a' + i))] = i;
    }
    next_code = 26;
}

void pack(const std::string& s) {
    std::unordered_map<std::string, int> dict;
    int next_code;
    pack_dict(dict, next_code);
    std::vector<int> codes;
    std::string cur;
    for (char c : s) {
        std::string next = cur + c;
        if (dict.count(next)) {
            cur = next;
        } else {
            codes.push_back(dict[cur]);
            if (next_code < 4096) {
                dict[next] = next_code++;
            } else {
                pack_dict(dict, next_code);
            }
            cur = std::string(1, c);
        }
    }
    if (!cur.empty()) {
        codes.push_back(dict[cur]);
    }
    std::vector<int> bytes;
    for (size_t i = 0; i < codes.size(); i += 2) {
        if (i + 1 < codes.size()) {
            int a = codes[i];
            int b = codes[i + 1];
            bytes.push_back((a >> 4) & 255);
            bytes.push_back(((a & 15) << 4) | ((b >> 8) & 15));
            bytes.push_back(b & 255);
        } else {
            int a = codes[i];
            bytes.push_back((a >> 4) & 255);
            bytes.push_back((a & 15) << 4);
        }
    }
    std::cout << bytes.size() << '\n';
    for (int b : bytes) {
        std::cout << b << ' ';
    }
    std::cout << std::endl;
}

void unpack_dict(std::vector<std::string>& dict, int& next_code) {
    dict.resize(26);
    for (int i = 0; i < 26; i++) {
        dict[i] = std::string(1, char('a' + i));
    }
    next_code = 26;
}

void unpack() {
    int n;
    std::cin >> n;
    std::vector<int> bytes(n);
    for (int i = 0; i < n; i++) {
        std::cin >> bytes[i];
    }
    std::vector<int> codes;
    for (size_t i = 0; i < bytes.size(); i += 3) {
        if (i + 2 < bytes.size()) {
            int b1 = bytes[i];
            int b2 = bytes[i + 1];
            int b3 = bytes[i + 2];
            int a = (b1 << 4) | (b2 >> 4);
            int b = ((b2 & 15) << 8) | b3;
            codes.push_back(a);
            codes.push_back(b);
        } else if (i + 1 < bytes.size()) {
            int b1 = bytes[i];
            int b2 = bytes[i + 1];
            int a = (b1 << 4) | (b2 >> 4);
            codes.push_back(a);
        }
    }
    if (codes.empty()) return;
    std::vector<std::string> dict;
    int next_code;
    unpack_dict(dict, next_code);
    std::string prev = dict[codes[0]];
    std::string answer = prev;
    for (size_t i = 1; i < codes.size(); i++) {
        int code = codes[i];
        std::string cur;
        if (code < next_code) {
            cur = dict[code];
        } else if (code == next_code) {
            cur = prev + prev;
        }
        answer += cur;
        if (next_code < 4096) {
            if (dict.size() <= (size_t)next_code) {
                dict.push_back(prev + cur);
            } else {
                dict[next_code] = prev + cur;
            }
            next_code++;
        }
        if (next_code >= 4096) {
            if (i + 1 < codes.size()) {
                unpack_dict(dict, next_code);
                prev = dict[codes[i + 1]];
                answer += prev;
                i++;
            }
            continue;
        }
        prev = cur;
    }
    std::cout << answer << '\n';
}

int main() {
    std::string type;
    if (std::cin >> type) {
        if (type == "pack") {
            std::string s;
            std::cin >> s;
            pack(s);
        } else if (type == "unpack") {
            unpack();
        }
    }
    return 0;
}