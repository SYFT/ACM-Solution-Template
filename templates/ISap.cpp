class ISap {
	/**
	 * Time Complexity: O(N^2*M)
	 * Special Case Time Complexity:
	 *		If the capacity and flow are integer, the time complexity is
	 *		O(min{N^(2/3), M^(1/2)}*M)
	 * Improve:
	 *		Gap, Multiple Augmented, Manual Stack, Active Label
	 * Usage:
	 *		init()
	 *		{addEdge()}
	 *		[preLabel()]
	 *		maxflow()
     *	Attention:
     *	    AddEdge() will add directed edge defaultly.
     *	    If you need undirected edge, please modify it.
	 *	preLabel function is not nessary. But will slower 10% if not use.
     *	In hierarchical graph, preLabel function is nessary.
	 * */
private :
	static const int N = 1001010, M = 3000010, INF = 1000000001;
public :
	int fir[N], nex[M * 2], son[M * 2], cap[M * 2], flow[M * 2], totEdge;
	int gap[N], dep[N], src, des, totPoint;

	void init(int _totPoint) {
		totEdge = 0, totPoint = _totPoint;
		for(int i = 0; i <= totPoint; ++i)
			gap[i] = dep[i] = 0, fir[i] = -1;
	}

	void addEdge(const int u, const int v, const int c) {
        /**
         * Attention, This function is added directed edge defaultly.
         * */
		nex[totEdge] = fir[u], son[totEdge] = v, cap[totEdge] = c, flow[totEdge] = 0;
		fir[u] = totEdge++;
		nex[totEdge] = fir[v], son[totEdge] = u, cap[totEdge] = c, flow[totEdge] = 0;
		fir[v] = totEdge++;
	}

	void preLabel() {
		static int que[N], head, tail;
		head = tail = 0;
		for(int i = 0; i <= totPoint; ++i) dep[i] = totPoint, gap[i] = 0;

		que[tail++] = des, dep[des] = 0, ++gap[0];
		while(head < tail) {
			int u = que[head++];
			for(int tab = fir[u], v; tab != -1; tab = nex[tab]) {
				if(flow[tab ^ 1] >= cap[tab ^ 1]) continue;
				if(dep[v = son[tab]] < totPoint) continue;
				++gap[dep[v] = dep[u] + 1], que[tail++] = v;
			}
		}
	}

	int maxflow() {
		static int cur[N], rev[N];
		int flows = 0;
		for(int i = 0; i <= totPoint; ++i) cur[i] = fir[i];
		for(int u = src; dep[u] < totPoint && dep[src] < totPoint; ) {
			if(u == des) {
				int nowFlow = INF;
				for(int p = src; p != des; p = son[cur[p]])
					nowFlow = min(nowFlow, cap[cur[p]] - flow[cur[p]]);
				for(int p = src; p != des; p = son[cur[p]])
					flow[cur[p]] += nowFlow, flow[cur[p] ^ 1] -= nowFlow;
				flows += nowFlow, u = src;
			}

			int tab;
			for(tab = cur[u]; tab != -1; tab = nex[tab])
				if(cap[tab] > flow[tab] && dep[u] == dep[son[tab]] + 1) break;
			if(tab != -1) {
				cur[u] = tab, rev[son[tab]] = tab ^ 1;
				u = son[tab];
			} else {
				if(--gap[dep[u]] == 0) break;
				cur[u] = fir[u];
				int minDep = totPoint;
				for(tab = fir[u]; tab != -1; tab = nex[tab])
					if(cap[tab] > flow[tab]) minDep = min(minDep, dep[son[tab]]);
				++gap[dep[u] = minDep + 1];
				if(u != src) u = son[rev[u]];
			}
		}
		return flows;
	}
};

