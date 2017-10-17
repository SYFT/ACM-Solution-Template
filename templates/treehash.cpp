const int PRIMESTOT = 7;
const unsigned int PRIMES[PRIMESTOT] = {
	313,
	5483, 
	85017, 
	451883, 
	6459271,
	37562047,
	142859339
};

struct cmpByHashCode {
	unsigned int *keys;
	cmpByHashCode(unsigned int *keys):keys(keys) {}
	inline bool operator ()(const int a, const int b) const {
		return keys[a] < keys[b];
	}
};

struct TreeHash {
	/**
	 * 1. It will find tree's barycentre firstly and treat it as root.
	 * 2. If it has two barycentres, it will add a new nodes between them.
	 * 3. Then Hash Every nodes by it subtree's structure.
	 * 4. O(n * number of primes).
	 * 5. Choose several primes as keys to hash.
	 * 6. The number of primes determine the accuracy of hash.
	 * */

	static unsigned int factor[N];

	static void prepare(int N) {
		unsigned int tmp[PRIMESTOT];
		for(int i = 0; i < PRIMESTOT; ++i) tmp[i] = PRIMES[i];
		for(int i = 0; i < N; ++i) {
			factor[i] = tmp[i % PRIMESTOT];
			tmp[i % PRIMESTOT] *= tmp[i % PRIMESTOT];
		}
	}

	int head[N], son[N * 2], nex[N * 2], tot;
	int n;
	int rot, bfsList[N], father[N], size[N], maxSubtree[N];
	unsigned int hashCode[N];
	vector<int> child[N];

	inline void init(int m) {
		n = m;
		for(int i = 0; i < n; ++i) head[i] = -1;
		tot = 0;
	}

	inline void addEdge(int u, int v) {
		son[tot] = v, nex[tot] = head[u];
		head[u] = tot++;
	}

	inline void bfs(int st) {
		int len = 0;
		bfsList[len++] = st, father[st] = -1;
		for(int idx = 0; idx < len; ++idx) {
			int u = bfsList[idx];
			for(int tab = head[u], v; tab != -1; tab = nex[tab])
				if(father[u] != (v = son[tab]))
					father[v] = u, bfsList[len++] = v;
		}
	}

	inline int getBarycentre() {
		bfs(0);

		for(int i = 0; i < n; ++i) size[i] = 0;
		for(int i = n - 1; i >= 0; --i) {
			int u = bfsList[i];
			++size[u];
			if(father[u] != -1) size[father[u]] += size[u];

			maxSubtree[u] = n - size[u];
			for(int tab = head[u], v; tab != -1; tab = nex[tab])
				if(father[u] != (v = son[tab]))
					maxSubtree[u] = max(maxSubtree[u], size[v]);
		}

		int rot = 0;
		for(int i = 1; i < n; ++i)
			if(maxSubtree[rot] > maxSubtree[i]) rot = i;
		int anotherRot = -1;
		for(int i = 0; i < n; ++i)
			if(i != rot && maxSubtree[rot] == maxSubtree[i]) {
				anotherRot = i;
				break;
			}

		if(anotherRot != -1) {
			int newRot = n++;
			head[newRot] = -1;
			addEdge(newRot, rot), addEdge(newRot, anotherRot);

			for(int tab = head[rot]; tab != -1; tab = nex[tab])
				if(son[tab] == anotherRot) {
					son[tab] = newRot;
					break;
				}
			for(int tab = head[anotherRot]; tab != -1; tab = nex[tab])
				if(son[tab] == rot) {
					son[tab] = newRot;
					break;
				}

			rot = newRot;
		}
		return rot;
	}

	inline int hashTree() {
		int rot = getBarycentre();
		bfs(rot);

		for(int i = n - 1; i >= 0; --i) {
			int u = bfsList[i];

			child[u].clear(), hashCode[u] = 1;
			for(int tab = head[u], v; tab != -1; tab = nex[tab])
				if(father[u] != (v = son[tab])) child[u].push_back(v);
			sort(all(child[u]), cmpByHashCode(hashCode));
			for(int idx = 0; idx < sz(child[u]); ++idx)
				hashCode[u] += factor[idx] * hashCode[child[u][idx]];
		}
		return rot;
	}
};
unsigned int TreeHash::factor[N];

