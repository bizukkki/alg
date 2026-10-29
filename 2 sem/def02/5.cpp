#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    std::vector<int> pref(n);
    char ch;
    std::cin>>ch;
    if (ch == 'a') pref[0] = 0;
    else pref[0] = 1; 
    for (int i = 1; i < n; i++) {
        char a;
        std::cin >> a;
        if (a == 'a') pref[i] = pref[i-1];
        else pref[i] = pref[i-1] + 1;
    }
    //for(int a : pref) std::cout << a << " ";
    //std::cout << "\n";
    int answ = 0;
    int i = 0;
    while (i < n - 1) {
        int j = i + 1;
        while (j < n){
            int count;
            if (i == 0) count = pref[j];
            else count = pref[j] - pref[i - 1];
            int len = j - i + 1;
            if (count!=0 && len%count == 0 && len / count == 2) answ+=1;
            if (count > (n - i)/2) j = n;
            if ((len - count) > (n - i)/2) j = n;
            j+=2;
        }
        i++;
    }
    std::cout << answ;
}