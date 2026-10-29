#include <iostream>
#include <string>
#include <map>
int main() 
{
    std::string s1, s2;
    std::cin >> s1 >> s2;
    if (s1.size() != s2.size()){
        std::cout << 0;
        return 0;
    }
    std::map<char, std::pair<int, int>> map_1;
    for (char c : "qwertyuiopasdfghjklzxcvbnm"){
        map_1.insert({c, {0, 0}});
    }
    for (int i = 0; i < s1.size(); ++i) {
        map_1[s1[i]].fist+=1;
        map_1[s2[i]].second+=1;
    }
    for (char c : "qwertyuiopasdfghjklzxcvbnm"){
        if (map_1[c].first != map_1[c].second) {
            std::cout << 0;
            return 0;
        }
    }
    std::cout << 1;
	return 0;
}