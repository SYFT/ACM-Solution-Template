#define foreach(x, y) for(__typeof((y).begin()) x = (y).begin(); x != (y).end(); ++x)

// points up to 2 * n, edges will up to n * m
const int N = 1010, M = 5000010;
int st[M], ed[M], val[M];
vector<int> valid_edges, valid_points, tpoints, tedges;
int n, m, origin_n, origin_m;
int pre[N], path[N], len, belong[N], deactivate[M], activate[M];
int visit[N];
bool mark[M];

void insert(int u, int v, int w, int deact = -1, int act = -1) {
	st[m] = u, ed[m] = v, val[m] = w;
	deactivate[m] = deact, activate[m] = act;
	++m;
}

void solve() {
	origin_n = n, origin_m = m;

	for(int i = 0; i < m; ++i) valid_edges.push_back(i);
	for(int i = 0; i < n; ++i) valid_points.push_back(i);
	int answer = 0;
	int root = 0;
    bool impossible = false;
	while(true) {
		foreach(point, valid_points) pre[*point] = -1;
		foreach(e, valid_edges) {
			int v = ed[*e];
			if(pre[v] == -1 || val[pre[v]] > val[*e]) pre[v] = *e;
		}
		pre[root] = -1;

		foreach(point, valid_points)
			visit[*point] = -1, belong[*point] = *point;
		tpoints.clear(), tedges.clear();
		bool flag = false;
		foreach(point, valid_points) {
			int u = *point;
			if(visit[u] != -1) continue;
			len = 0;
			for(len = 0; visit[u] == -1; u = st[pre[u]]) {
				path[len++] = u, visit[u] = *point;
				if(pre[u] == -1) break;
			}
			if(pre[u] == -1 || visit[u] != *point) {
				for(int i = 0; i < len; ++i) tpoints.push_back(path[i]);
			} else {
                int start = 0;
                while(path[start] != u) tpoints.push_back(path[start++]);
				flag = true;
				int p = n++;
				for(int i = start; i < len; ++i) {
					int u = path[i];
					belong[u] = p;
                    mark[pre[u]] = true, answer += val[pre[u]];
				}
				tpoints.push_back(p);
			}
		}
		if(!flag) {
            int cnt_nopre = 0;
			foreach(point, valid_points)
				if(pre[*point] == -1) ++cnt_nopre;
                else answer += val[pre[*point]], mark[pre[*point]] = true;
            if(cnt_nopre > 1) impossible = true;
			break;
		}
		foreach(edge, valid_edges) {
			int u = st[*edge], v = ed[*edge], w = val[*edge];
			if(belong[u] == belong[v]) continue;
			if(belong[u] == u && belong[v] == v) tedges.push_back(*edge);
			else {
				insert(
						belong[u], belong[v], 
						belong[v] == v ? w : w - val[pre[v]], 
						belong[v] == v ? -1 : pre[v],
						*edge
						);
				tedges.push_back(m - 1);
			}
		}

		root = belong[root];
		valid_points = tpoints, valid_edges = tedges;
	}

	for(int i = m - 1; i >= 0; --i)
		if(mark[i]) {
			if(deactivate[i] != -1) mark[deactivate[i]] = false;
			if(activate[i] != -1) mark[activate[i]] = true;
		}

    if(impossible) puts("-1");
    else {
        vector<int> ans;
        for(int i = 0; i < origin_m; ++i)
            if(mark[i]) ans.push_back(i + 1);
        sort(ans.begin(), ans.end());
        assert(origin_n - 1 == (int) ans.size());
        printf("%d\n", (int) ans.size());
        for(int i = 0, s = (int) ans.size(); i < s; ++i) {
            printf(i == s - 1 ? "%d\n" : "%d ", ans[i]);
        }
        // printf("%d\n", answer);
    }
}
