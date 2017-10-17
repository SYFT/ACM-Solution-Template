#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <deque>
using namespace std;
#define INF (1000000001)
#define MLL (1000000000000000001LL)
#define puf push_front
#define pub push_back
#define pof pop_front
#define pob pop_back
#define sz(x) ((int) (x).size())
typedef long long ll;
typedef unsigned long long ull;

template<class T>
inline T read() {
	char ch = ' ';
	T ret = (T) 0;
	bool positive = 1;
	while(!(ch >= '0' && ch <= '9')) {
		if(ch == '-') positive ^= 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		ret = ret * ((T) 10) + ((T) (ch - '0'));
		ch = getchar();
	}
	return positive ? ret : -ret;
}

template<class T>
inline void print(T x) {
    static int a[24];
	int n = 0;
    while(x > 0) {
        a[n++] = x % 10;
        x /= 10;
    }
    if(n == 0) a[n++] = 0;
    while(n--) putchar('0' + a[n]);
}

const int N = 110, M = 100 * 100 + 10;
int n, m;
int dis[N][N];
struct EdgeNode {
	int u, v, c;
	EdgeNode() {}
	EdgeNode(int u, int v, int c):u(u), v(v), c(c) {}

	inline void read() {
		scanf("%d%d%d", &u, &v, &c);
	}
} edges[M];

inline void solve() {
	for(int i = 0; i < m; i++) edges[i].u--, edges[i].v--;

	for(int i = 0; i < n; i++) dis[0][i] = INF;
	dis[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < n; j++)
			dis[i][j] = INF;

		for(int j = 0; j < m; j++)
			if(dis[i][edges[j].v] > dis[i - 1][edges[j].u] + edges[j].c)
				dis[i][edges[j].v] = dis[i - 1][edges[j].u] + edges[j].c;
	}

	double ans = INF;
	for(int i = 0; i < n; i++) {
		if(dis[n][i] >= INF) continue;
		double now = -INF;
		for(int j = 0; j < n; j++)
			if(dis[j][i] < INF)
				now = max(now, (dis[n][i] - dis[j][i]) / (1. * (n - j)));
		if(now > -INF) ans = min(ans, now);
	}

	printf("%lf\n", ans);
}

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) edges[i].read();
	solve();
	return 0;
}

