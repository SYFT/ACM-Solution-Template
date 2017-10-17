struct Trie {
	/**
	 * 1. MAXBIT = max depth
	 * 2. rot = The root of the tr[i](ith Trie)
	 * 3. interface add(val, w) -> val (value)   w (times)
	 *		insert w elements with value val to the trie
	 * 4. remember initialize the Trie::Node::tot = 0
	 * 5. updata -  change it as you want, it will updata each
	 *	node after insert value to its children. In the template,
	 *	it updata f 
	 * */
	static struct Node {
		static int tot;

		int child[2], size;

		int f;

		inline void init() {
			child[0] = child[1] = -1, size = f = 0;
		}

	} tr[N * M * M];

#define child(x, y) tr[x].child[y]
#define lch(x) child(x, 0)
#define rch(x) child(x, 1)
#define size(x) (x == -1 ? 0 : tr[x].size)
#define f(x) tr[x].f

	int rot;

	inline int bruteForce(int u, int v, int d) {
		int ret = 0;
		while(d >= 0) {
			int t = size(lch(v)) == 0;
			int _t = t;
			if(size(child(u, _t)) == 0) _t ^= 1, ret += (1 << d);
			u = child(u, _t), v = child(v, t), --d;
		}
		return ret;
	}

	inline void updata(int u, int d) {
		f(u) = -1;
		if(size(u) > 1) {
			f(u) = 0;
			for(int t = 0; t < 2; ++t) {
				int v = child(u, t);
				if(size(v) > 1) f(u) = max(f(u), f(v));
				else if(size(v) == 1) {
					int xorValue = bruteForce(child(u, t ^ 1), v, d - 1);
					xorValue += (1 << d);
					f(u) = max(f(u), xorValue);
				}
			}
		}
	}

	inline void addVal(int &x, int val, int w, int d) {
		if(x == -1) tr[x = Node::tot++].init();
		tr[x].size += w;
		if(d >= 0) addVal(child(x, (val & (1 << d)) > 0), val, w, d - 1);

		updata(x, d);
	}

	inline void add(int val, int w) {
		addVal(rot, val, w, MAXBIT - 1);
	}

	inline void traverse(int x, int now, int d, Trie &pro) {
		if(x == -1) return;
		if(d < 0) pro.add(now, size(x));
		else {
			if(size(lch(x)) > 0)
				traverse(lch(x), now, d - 1, pro);
			if(size(rch(x)) > 0)
				traverse(rch(x), now + (1 << d), d - 1, pro);
		}
	}

	inline void operator +=(Trie &t) {
		if(size(rot) < size(t.rot)) swap(rot, t.rot);
		t.traverse(t.rot, 0, MAXBIT - 1, *this);
	}

	inline int getAnswer() const {
		return f(rot);
	}

} tr[N];
int Trie::Node::tot;
Trie::Node Trie::tr[N * M * M];

