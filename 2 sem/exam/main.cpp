#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

// bool is_top(std::string s) {
//     std::vector<std::pair<int, int>> v = [(1, 0), (1,0)];
//     v.push_back((0, 1));

// }

int main() {
    std::string s = "12345";
    int i = 1;
    do{
        if (i == 3) std::cout << s << "\n";
        if (i == 90) std::cout << s << "\n";
        i++;
        
    } while(std::next_permutation(s.begin(), s.end()));

} 


// int main() {
//   std::cout << pow(2, 8) + pow(2, 6);
//   std::cout << std::b
// }
// //101000000