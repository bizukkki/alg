#include <iostream>
#include <vector>
#include <cmath>
///#include <algorithm>

void rebuild(int block, int n, int block_size, std::vector<int>& a, std::vector<int>& jump, 
    std::vector<int>& count_j, std::vector<int>& last) {

    int l = block * block_size + 1;
    int r = std::min(n, (block + 1) * block_size);
    for (int i = r; i >= l; i--) {
        int to = i + a[i];
        if (to > n) {
            jump[i] = n + 1;
            count_j[i] = 1;
            last[i] = i;
        } else if ((to - 1) / block_size != (i - 1)/ block_size) {
            jump[i] = to;
            count_j[i] = 1;
            last[i] = i;
        } else {
            jump[i] = jump[to];
            count_j[i] = count_j[to] + 1;
            last[i] = last[to];
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1);
    std::vector<int> jump(n + 1);
    std::vector<int> count_j(n + 1);
    std::vector<int> last(n + 1);
    int block_size = int(std::sqrt(n));
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    int blocks_count = (n - 1) / block_size + 1;
    for (int block = 0; block < blocks_count; block++) {
        rebuild(block, n, block_size, a, jump, count_j, last);
    }
    for (int q = 0; q < m; q++) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int pos, value;
            std::cin >> pos >> value;
            a[pos] = value;
            int block = (pos - 1) / block_size;
            rebuild(block, n, block_size, a, jump, count_j, last);
        } else {
            int pos;
            std::cin >> pos;
            int answer_last = pos;
            int answer_cnt = 0;
            while (pos <= n) {
                answer_cnt += count_j[pos];
                if (jump[pos] > n) {
                    answer_last = last[pos];
                    break;
                }
                pos = jump[pos];
            }
            std::cout << answer_last << " " << answer_cnt << '\n';
        }
    }
}



// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>

// void rebuild(int block, int n, int block_size, std::vector<int>& a, std::vector<int>& jump, 
//     std::vector<int>& count_j, std::vector<int>& last) {

//     int l = block * block_size + 1;
//     int r = std::min(n, (block + 1) * block_size);
//     for (int i = r; i >= l; i--) {
//         int to = i + a[i];
//         if (to > n) {
//             jump[i] = n + 1;
//             count_j[i] = 1;
//             last[i] = i;
//         } else if ((to - 1) / block_size != (i - 1) / block_size) {
//             jump[i] = to;
//             count_j[i] = 1;
//             last[i] = i;
//         } else {
//             jump[i] = jump[to];
//             count_j[i] = cou[to] + 1;
//             last[i] = last[to];
//         }
//     }
// }

// int main() {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     int n, m;
//     std::cin >> n >> m;
//     std::vector<int> a(n + 1);
//     std::vector<int> jump(n + 1);
//     std::vector<int> count_j(n + 1);
//     std::vector<int> last(n + 1);
//     int block_size = int(std::sqrt(n)) + 1;
//     for (int i = 1; i <= n; i++) {
//         std::cin >> a[i];
//     }
//     int blocks_count = (n - 1) / block_size + 1;
//     for (int block = 0; block < blocks_count; block++) {
//         rebuild(block, n, block_size, a, jump, count_j, last);
//     }
//     for (int q = 0; q < m; q++) {
//         int type;
//         std::cin >> type;
//         if (type == 0) {
//             int pos, value;
//             std::cin >> pos >> value;
//             a[pos] = value;
//             int block = (pos - 1) / block_size;
//             rebuild(block, n, block_size, a, jump, count_j, last);
//         } else {
//             int pos;
//             std::cin >> pos;
//             int answer_last = pos;
//             int answer_cnt = 0;
//             while (pos <= n) {
//                 answer_cnt += count_j[pos];
//                 if (jump[pos] > n) {
//                     answer_last = last[pos];
//                     break;
//                 }
//                 pos = jump[pos];
//             }
//             std::cout << answer_last << " " << answer_cnt << '\n';
//         }
//     }
// }
