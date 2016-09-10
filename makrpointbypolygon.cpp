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
#define mk make_pair
#define sz(x) ((int) (x).size())
#define foreach(it, x) for(__typeof((x).begin()) it = (x).begin(); it != (x).end(); it++)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) (x).begin(), (x).end()
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

const int N = 610, M = 8010 * 2;
const double EPS = 1e-7;
struct Point {
	int x, y;

	Point() {}
	Point(int x, int y):x(x), y(y) {}

	inline Point operator +(const Point &t) const {
		return Point(x + t.x, y + t.y);
	}

	inline Point operator -(const Point &t) const {
		return Point(x - t.x, y - t.y);
	}

	inline ll operator *(const Point &t) const {
		return x * t.x + y * t.y;
	}

	inline ll operator %(const Point &t) const {
		return x * t.y - y * t.x;
	}

	inline bool operator <(const Point &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}

	inline void read() {
		scanf("%d%d", &x, &y);
	}
} cap[N], p[M * 2];
double arg[M * 2];
typedef vector<int> Poly;
int n, m;
map<Point, vector<int> > graph;
map<int, int> ofPoly;
int father[N], bel[N];
vector<int> cover[N];
Poly poly[M];
int totPoly, con[M];
double area[M];
vector<int> ans[N];
bool visit[M];
int idx[N];

inline void init() {
	graph.clear(), ofPoly.clear();
	for(int i = 0; i < n; ++i) cover[i].clear();
	for(int i = 0; i < n; ++i) ans[i].clear();
	clr(visit, 0), totPoly = 0;
}

inline int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}

inline double getArg(const Point &a) {
	return atan2(a.y, a.x);
}

inline bool cmpByArg(int a, int b) {
	return arg[a] < arg[b];
}

inline bool cmpByArea(int a, int b) {
	return area[a] < area[b];
}

inline bool cmpByOfPolyArea(int x, int y) {
	return area[bel[x]] < area[bel[y]];
}

inline int getNextEdge(int x) {
	int rank = lower_bound(all(graph[p[x ^ 1]]), x ^ 1, cmpByArg) - 
				graph[p[x ^ 1]].begin();
	return rank ? graph[p[x ^ 1]][rank - 1] : graph[p[x ^ 1]].back(); 
}

inline double getArea(const Poly &n) {
	double ret = 0.;
	for(int i = 1; i < sz(n) - 1; ++i)
		ret += (p[n[i]] - p[n[0]]) % (p[n[i + 1]] - p[n[0]]);
	return ret / 2.;
}

inline bool pointInPoly(const Point &x, const Poly &n) {
	int cross = 0;
	for(int i = 0; i < sz(n); ++i) {
		Point v1 = p[n[i]] - x, v2 = p[n[(i + 1) % sz(n)]] - x;
		int c = sgn(v1 % v2), d = sgn(v1 * v2);
		if(!c && d <= 0) return 0;
		int d1 = sgn(v1.y), d2 = sgn(v2.y);
		if(c > 0 && d1 <= 0 && d2 > 0) ++cross;
		if(c < 0 && d2 <= 0 && d1 > 0) --cross;
	}
	return cross > 0;
}

inline void solve() {
	// build graph by angle
	for(int i = 0; i < 2 * m; ++i) arg[i] = getArg(p[i ^ 1] - p[i]);
	for(int i = 0; i < 2 * m; ++i) graph[p[i]].pub(i);
	foreach(it, graph) sort(all(it->second), cmpByArg);

	// get all polygons
	for(int i = 0; i < 2 * m; ++i) {
		if(visit[i]) continue;
		Poly t;
		t.clear();
		int now = i;
		do {
			visit[now] = true, t.pub(now);
			now = getNextEdge(now); 
		} while(now != i);
		area[totPoly] = getArea(t);
		if(sgn(area[totPoly]) <= 0) continue;
		poly[totPoly] = t;
		foreach(it, t) ofPoly[*it] = totPoly;
		for(int j = 0; j < n; ++j)
			if(pointInPoly(cap[j], t)) cover[j].pub(totPoly);
		++totPoly;
	}

	for(int i = 0; i < n; ++i) sort(all(cover[i]), cmpByArea);
	for(int i = 0; i < n; ++i) con[bel[i] = cover[i][0]] = i;
	for(int i = 0; i < 2 * m; i += 2)
		if(ofPoly.count(i) && ofPoly.count(i ^ 1)) {
			int x = con[ofPoly[i]], y = con[ofPoly[i ^ 1]];
			// printf("%d %d\n", x, y);
			ans[x].pub(y), ans[y].pub(x);
		}

	for(int i = 0; i < n; ++i) idx[i] = i;
	sort(idx, idx + n, cmpByOfPolyArea);
	for(int i = 0; i < n; ++i) {
		bool flag = true;
		foreach(e, poly[bel[idx[i]]])
			if(ofPoly.count(*e ^ 1) == 0) {
				flag = false;
				break;
			}
		if(!flag) {
			for(int j = i + 1; j < n; ++j)
				if(pointInPoly(cap[idx[i]], poly[bel[idx[j]]])) {
					ans[idx[i]].pub(idx[j]), ans[idx[j]].pub(idx[i]);
					break;
				}
		}
	}

	for(int i = 0; i < n; ++i) {
		sort(all(ans[i]));
		ans[i].erase(unique(all(ans[i])), ans[i].end());
		printf("%d", sz(ans[i]));
		for(int j = 0; j < sz(ans[i]); ++j)
			printf(" %d", ans[i][j] + 1);
		puts("");
	}
}

int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	while(scanf("%d%d", &n, &m) == 2 && n + m != 0) {
		init();
		for(int i = 0; i < n; ++i) cap[i].read();
		for(int i = 0; i < 2 * m; ++i) p[i].read();
		solve();
	}
	return 0;
}

