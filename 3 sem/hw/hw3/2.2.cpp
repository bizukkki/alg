#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

void write_code(std::vector<int>& bytes, int code, int bits,
                int& buffer, int& count) {
    buffer |= code << count;
    count += bits;

    while (count >= 8) {
        bytes.push_back(buffer & 255);
        buffer >>= 8;
        count -= 8;
    }
}

void pack(std::string& s) {
    std::unordered_map<std::string, int> dict;

    for (int i = 0; i < 256; i++) {
        dict[std::string(1, char(i))] = i;
    }

    dict.reserve(500000);

    int next_code = 256;

    std::vector<int> codes;

    std::string current;

    for (char c : s) {
        std::string next = current + c;

        if (dict.count(next)) {
            current = next;
        } else {
            codes.push_back(dict[current]);

            dict[next] = next_code;
            next_code++;

            current = std::string(1, c);
        }
    }

    if (!current.empty()) {
        codes.push_back(dict[current]);
    }

    std::vector<int> bytes;

    int buffer = 0;
    int count = 0;
    int bits = 8;

    for (int i = 0; i < (int)codes.size(); i++) {
        write_code(bytes, codes[i], bits, buffer, count);

        // После каждого выведенного кода LZW добавляет новое слово,
        // кроме последнего.
        if (i + 1 < (int)codes.size()) {
            next_code++;

            if (next_code == (1 << bits)) {
                bits++;
            }
        }
    }

    if (count > 0) {
        bytes.push_back(buffer & 255);
    }

    // Сколько бит реально записано.
    int bit_count = 0;
    next_code = 256;
    bits = 8;

    for (int i = 0; i < (int)codes.size(); i++) {
        bit_count += bits;

        if (i + 1 < (int)codes.size()) {
            next_code++;

            if (next_code == (1 << bits)) {
                bits++;
            }
        }
    }

    // 4 дополнительных байта:
    // записываем количество полезных бит.
    int total_bytes = bytes.size() + 4;

    std::cout << total_bytes << '\n';

    std::cout << (bit_count & 255) << ' ';
    std::cout << ((bit_count >> 8) & 255) << ' ';
    std::cout << ((bit_count >> 16) & 255) << ' ';
    std::cout << ((bit_count >> 24) & 255) << ' ';

    for (int byte : bytes) {
        std::cout << byte << ' ';
    }

    std::cout << '\n';
}

void unpack() {
    int n;
    std::cin >> n;

    std::vector<int> bytes(n);

    for (int i = 0; i < n; i++) {
        std::cin >> bytes[i];
    }

    // Первые 4 байта — количество полезных бит.
    int bit_count = 0;

    bit_count |= bytes[0];
    bit_count |= bytes[1] << 8;
    bit_count |= bytes[2] << 16;
    bit_count |= bytes[3] << 24;

    std::vector<std::string> dict(256);

    for (int i = 0; i < 256; i++) {
        dict[i] = std::string(1, char(i));
    }

    int next_code = 256;
    int bits = 8;

    std::vector<int> codes;

    int buffer = 0;
    int count = 0;
    int used_bits = 0;

    for (int i = 4; i < n; i++) {
        buffer |= bytes[i] << count;
        count += 8;

        while (count >= bits && used_bits + bits <= bit_count) {
            int code = buffer & ((1 << bits) - 1);

            codes.push_back(code);

            buffer >>= bits;
            count -= bits;
            used_bits += bits;

            if (used_bits < bit_count && next_code == (1 << bits)) {
                bits++;
            }
        }
    }

    if (codes.empty()) {
        std::cout << '\n';
        return;
    }

    std::string previous = dict[codes[0]];
    std::string answer = previous;

    for (int i = 1; i < (int)codes.size(); i++) {
        int code = codes[i];

        std::string current;

        if (code < next_code) {
            current = dict[code];
        } else {
            current = previous + previous[0];
        }

        answer += current;

        dict.push_back(previous + current[0]);
        next_code++;

        previous = current;
    }

    std::cout << answer << '\n';
}

int main() {
    std::string mode;
    std::cin >> mode;

    if (mode == "pack") {
        std::string s;
        std::cin >> s;

        pack(s);
    } else {
        unpack();
    }
}