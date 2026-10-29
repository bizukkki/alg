#include <iostream> 
#include <vector>

std::pair<int, int> dfs(std::vector<std::vector<int>> &g, int now, std::vector<bool> &visited, std::vector<int>& parent) {
    for (auto i : visited){
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (auto i : parent){
        std::cout << i << " ";
    }
    std::cout << "\n";
    visited[now] = true;
	for (int i : g[now]) {
		if (i != now) {
			parent[i] = now;
			if (visited[i] == false) {
				auto res = dfs(g, i, visited, parent);
                if (res.first !=0) {
                    return res;
                }
			} else return {now, i};
		}
	}
	return {0,0};
}

int main() 
{
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> g(n + 1);
	for (int i = 1; i < n +1; i++) {
		for (int j = 1; j < n +1; j++) {
			int v;
			std::cin >> v;
			if (v) {
				g[i].push_back(j);
			}
		}
	}
	std::vector<bool> visited(n+1, false);
	std::vector<int> parent(n+1, -1);
	for (int i = 1; i < n+1; i++) {
		if (!visited[i]) {
			std::pair<int, int> v = dfs(g, i, visited, parent);
			if(v.first != 0) {
				std::vector<int> answer;
                std::cout << v.first << " " << v.second << "\n";
				answer.push_back(v.first);
				int p = v.first;
				while(p != v.second) {
					p = parent[p];
					answer.push_back(p);
				}
				std::cout << "YES" << "\n";
				std::cout << answer.size() << "\n";
				for (auto j : answer) {
					std::cout << j << " ";
				}
                return 0;
			}
		}
	}
    std::cout << "NO" << "\n";
    for (auto i : visited){
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (auto i : parent){
        std::cout << i << " ";
    }
	return 0;
    
}