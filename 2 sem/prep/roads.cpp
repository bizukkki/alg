#include <iostream>
#include <vector>
#include <queue>

long long Abs(long long a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> towns(n+1);
    std::vector<std::vector<int>> neib(n+1);
    for (int i = 1; i < n +1; i++) {
        int x, y;
        std::cin >> x >> y;
        towns[i] = {x,y};
    }
    int k, start, finish;
    std::cin >> k >> start >> finish;
    for (int i = 1; i < n + 1; i++){
        int x1 = towns[i].first;
        int y1 = towns[i].second;
        for (int j = 1; j < i; j++){
            int x2 = towns[j].first;
            int y2 = towns[j].second;
            if ((x1 - x2) * (x1 - x2) + (y1-y2) * (y1-y2) <= k*k) {
                neib[i].push_back(j);
                neib[j].push_back(i);
            }
        }
    }
    std::vector<bool> used(n+1);
    std::vector<int> dist(n+1, -1);
    dist[start] = 0;
    std::queue<int> q;
    q.push(start);
    used[start] = true;
    while (!q.empty()){
        int now = q.front();
        q.pop();
        for (int i : neib[now]) {
            if (!used[i]){
                q.push(i);
                used[i] = true;
                dist[i] = dist[now] + 1;
                if (i == finish) break;
            }
        }
    }
    std::cout<<dist[finish] << "\n";
}