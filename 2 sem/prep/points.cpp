#include <iostream>
#include <vector>

int LessOrEqual(const std::vector<int>& v, int x) {
    int l = 0;
    int r = v.size();
    while (l < r) {
        int m = l + (r - l) / 2;

        if (v[m] <= x) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

int Less(const std::vector<int>& v, int x) {
    int l = 0;
    int r = v.size();
    while (l < r) {
        int m = l + (r - l) / 2;
        if (v[m] < x) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> start, end;
    for (int i = 0; i < n; i++){
        int a, b;
        std::cin >> a >> b;
        if (a > b) std::swap(a, b);
        start.push_back(a);
        end.push_back(b);
    }
    std::sort(start.begin(), start.end());
    std::sort(end.begin(), end.end());
    for (int i = 0; i < m; i++) {
        int p;
        std::cin >> p;
        int s, f;
        s = LessOrEqual(start, p);
        f = Less(end, p);
        std::cout << s - f << " ";
    }
}