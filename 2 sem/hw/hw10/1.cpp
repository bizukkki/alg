#include <iostream>
#include <vector>

int main() {
    long long n;
    std::cin>>n;
    std::vector<long long> pref(n);
    int mod = 1000000007;
    std::cin>> pref[0];
    pref[0] %=  mod;
    long long a;
    for(int i = 1; i < n; i++){
        std::cin >> a;
        pref[i] = a + pref[i-1];
    }
    int q;
    long long x1;
    std::cin >> q >> x1;
    long long x2 = (11173 * x1 + 1) % mod;
    long long answ = 0;
    long long l, r;
    for (int i = 0; i < q; i++) {
        l = std::min(x1 % n, x2 % n);
        r = std::max(x1%n, x2%n);
        if (l == 0) {
            answ+=pref[r];
        } else {
            answ+= (pref[r] - pref[l-1]);
        }
        answ%=mod;
        x1 = (11173 * x2 + 1) % mod;
        x2 = (11173 * x1 + 1) % mod;
    }
    std::cout << answ;
}