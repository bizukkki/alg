#include <iostream>
#include <queue>
#include <vector>

struct Volumes {
    int a, b, c;
};

int main() {
    int A, B, C;
    std::cin >> A >> B >> C;
    int V;
    std::cin >> V;
    std::queue<Volumes> q;
    std::vector<std::vector<std::vector<int>>> dist(A + 1, std::vector<std::vector<int>>(B + 1, std::vector<int>(C + 1, -1)));
    q.push({0, 0, 0});
    dist[0][0][0] = 0;
    while (!q.empty()) {
        Volumes now = q.front();
        q.pop();
        int d = dist[now.a][now.b][now.c];
        if (now.a == V || now.b == V || now.c == V) {
            std::cout << d;
            return 0;
        }

        int a = now.a;
        int b = now.b;
        int c = now.c;
        if (dist[A][b][c] == -1) {
            dist[A][b][c] = d + 1;
            q.push({A, b, c});
        }
        if (dist[a][B][c] == -1) {
            dist[a][B][c] = d + 1;
            q.push({a, B, c});
        }
        if (dist[a][b][C] == -1) {
            dist[a][b][C] = d + 1;
            q.push({a, b, C});
        }

        if (dist[0][b][c] == -1) {
            dist[0][b][c] = d + 1;
            q.push({0, b, c});
        }
        if (dist[a][0][c] == -1) {
            dist[a][0][c] = d + 1;
            q.push({a, 0, c});
        }
        if (dist[a][b][0] == -1) {
            dist[a][b][0] = d + 1;
            q.push({a, b, 0});
        }
        int na, nb, nc;

        int move_ab = std::min(a, B - b);
        na = a - move_ab;
        nb = b + move_ab;
        if (dist[na][nb][c] == -1) {
            dist[na][nb][c] = d + 1;
            q.push({na, nb, c});
        }

        int move_ac = std::min(a, C - c);
        na = a - move_ac;
        nc = c + move_ac;
        if (dist[na][b][nc] == -1) {
            dist[na][b][nc] = d + 1;
            q.push({na, b, nc});
        }

        int move_ba = std::min(b, A - a);
        nb = b - move_ba;
        na = a + move_ba;
        if (dist[na][nb][c] == -1) {
            dist[na][nb][c] = d + 1;
            q.push({na, nb, c});
        }

        int move_bc = std::min(b, C - c);
        nb = b - move_bc;
        nc = c + move_bc;
        if (dist[a][nb][nc] == -1) {
            dist[a][nb][nc] = d + 1;
            q.push({a, nb, nc});
        }

        int move_ca = std::min(c, A - a);
        na = a + move_ca;
        nc = c - move_ca;
        if (dist[na][b][nc] == -1) {
            dist[na][b][nc] = d + 1;
            q.push({na, b, nc});
        }

        int move_cb = std::min(c, B - b);
        nb = b + move_cb;
        nc = c - move_cb;
        if (dist[a][nb][nc] == -1) {
            dist[a][nb][nc] = d + 1;
            q.push({a, nb, nc});
        }
    }
    std::cout << -1;
}