#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>


std::vector<int> lzw_coding(std::string& s) {
    std::unordered_map<std::string, int> dict;
    for (int i = 0; i < 26; ++i) {
        std::string str;
        str = 'a' + i;
        dict[str] = i;
    }
    std::vector<int> codes;
    std::string current;
    int last_num= 26;
    for (char c : s) {
        std::string next = current + c;
        if (dict.find(next) != dict.end()) {
            current = next;
        } else {
            codes.push_back(dict[current]);
            if (last_num < 4096) {
                dict[next] = last_num;
                ++last_num;
            }
            current = "";
            current.push_back(c);
        }
    }
    if (!current.empty()) {
        codes.push_back(dict[current]);
    }
    return codes;
}


std::vector<unsigned char> pack_codes(std::vector<int>& codes) {
    std::vector<unsigned char> result;
    for (int i = 0; i < codes.size(); i += 2) {
        int a = codes[i];
        result.push_back(a / 16);
        if (i + 1 < codes.size()) {
            int b = codes[i+1];
            result.push_back((a % 16) * 16 + b / 256);
            result.push_back(b % 256);
        } else {
            result.push_back((a % 16) * 16);
        }
    }
    return result;
}


std::vector<int> unpack_codes(std::vector<unsigned char>& bytes) {
    std::vector<int> codes;
    for (int i = 0; i < bytes.size(); i += 3) {
        int a = bytes[i] * 16 + bytes[i + 1] / 16;
        codes.push_back(a);
        if (i + 2 < bytes.size()) {
            int b = (bytes[i + 1] % 16) * 256 + bytes[i + 2];
            codes.push_back(b);
        }
    }
    return codes;
}



std::string lzw_decoding(std::vector<int>& codes) {
    std::vector<std::string> dict(4096);
    for (int i = 0; i < 26; ++i) {
        std::string str = "";
        str.push_back('a' + i);
        dict[i] = str;
    }
    if (codes.empty()) {
        return "";
    }
    int last_num = 26;
    std::string answ = dict[codes[0]];
    std::string prev = dict[codes[0]];

    for (int i = 1; i < codes.size(); ++i) {
        int code = codes[i];
        std::string current;
        if (code < last_num && !dict[code].empty()) {
            current = dict[code];
        } else {
            current = prev + prev[0];
        }
        answ += current;
        if (last_num < 4096) {
            dict[last_num] = prev + current[0];
            ++last_num;
        }
        prev = current;
    }
    return answ;
}


int main() {
    std::string kom;
    std::cin >> kom;
    if (kom == "pack") {
        std::string s;
        std::cin >> s;
        std::vector<int> codes = lzw_coding(s);
        std::vector<unsigned char> bytes = pack_codes(codes);
        std::cout << bytes.size() << '\n';
        for (int i = 0; i < bytes.size(); ++i) {
            std::cout << int(bytes[i]);
            if (i + 1 < bytes.size()) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    if (kom == "unpack") {
        int n;
        std::cin >> n;
        std::vector<unsigned char> bytes(n);

        for (int i = 0; i < n; ++i) {
            int a;
            std::cin >> a;
            bytes[i] = a;
        }
        std::vector<int> codes = unpack_codes(bytes);
        std::string answer = lzw_decoding(codes);
        std::cout << answer << '\n';
    }
}