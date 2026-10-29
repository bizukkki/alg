#include<iostream>
#include <vector>
#include <queue>

int main() {
    int s, f;
    std::cin >> s >> f;
    std::vector<std::vector<int>> graf(10003);
    std::vector<int> parent(10000, -1);
    std::queue<int> q;
    q.push(s);
    parent[s] = 0;
    while(!q.empty()) {
        int num  = q.front();
        q.pop();
            if (num == f) break;
            int num1 = 0;
            int num2 = 0;
            int num3 = 0;
            int num4 = 0;
            if (num / 1000 != 9){
                num1 = num + 1000;
                if (parent[num1] == -1) {
                    parent[num1] = num;
                    q.push(num1);
                }
            }
            if (num%10 != 1){
                num2 = num - 1;
                if (parent[num2] == -1) {
                    parent[num2] = num;
                    q.push(num2);
                }
            } 
            num3 = (num / 10) +(num %10) * 1000;
            num4 = (num % 1000) * 10 + num / 1000;
            if (parent[num3] == -1) {
                    parent[num3] = num;
                    q.push(num3);
            }
            if (parent[num4] == -1) {
                    parent[num4] = num;
                    q.push(num4);
            }

        }
    std::vector<int> answer;
    answer.push_back(f);
    int prev = f;
    if (parent[f]!=-1) {
    while (prev != s){
        prev = parent[prev];
        answer.push_back(prev);
    }
    std::reverse(answer.begin(), answer.end());
    for (auto v : answer) {
        std::cout << v << "\n";
    }
}
}