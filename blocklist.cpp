struct BlockList {
	/**
	1.	indexes -> [1..n].
	2.	each block has at least one element after delete.
	3.	remenber to updata head, tail after each operation.
	*/
	const static int MAXLEN = N * 2;
	
	int l[MAXLEN], r[MAXLEN], val[MAXLEN];
	int n, block_len, blocks/*, startUse*/;
	int head[MAXLEN], tail[MAXLEN], size[MAXLEN];
	
	int space[MAXLEN];
	
	inline void init(int len) {
		/**
		O(len)
		*/
		n = len;
		for(block_len = 2; block_len * block_len <= n; block_len++) ;
		// block_len = 700;
		for(blocks = 1; blocks * block_len < n; blocks++) ;
		for(int i = 1; i <= blocks; i++) size[i] = 0;
		
		int now = 0;
		size[0] = block_len;
		for(int i = 1; i <= n; i++) {
			l[i] = i - 1, r[i] = i + 1;
			val[i] = 0;
			
			if(size[now] >= block_len) head[++now] = i;
			size[now]++, tail[now] = i;
		}
		r[n] = 0;
		l[0] = r[0] = 0;
		
		/*(int i = n + 1; i < MAXLEN - 1; i++) r[i] = i + 1;
		startUse = n + 1;*/
		
		for(int i = 1; i <= blocks; i++)
			space[i] = 1;
	}
	
	inline int getBlockIndex(int x) {
		/**
		return index of the block that xth element belongs to.
		O(sqrt(n))
		*/
		int ret = 1, nowCount = size[1];
		while(ret < blocks && nowCount < x) nowCount += size[++ret];
		return nowCount < x ? -1 : ret;
	}
	
	inline int at(int x) {
		/**
		get xth element of blocklist
		O(sqrt(n))
		*/
		int bindex = getBlockIndex(x), now = 0;
		if(bindex == -1) return -1;
		for(int i = 1; i < bindex; i++) now += size[i];
		int ret = head[bindex];
		for(++now; now < x; ++now) ret = r[ret];
		return ret;
	}
	
	inline int getFirstSpace(int st = 1) {
		int bindex = getBlockIndex(st), x = at(st);
		while(true) {
			if(val[x] == 0) return st;
			if(x == tail[bindex]) break;
			x = r[x], st++;
		}
		
		for(int i = bindex + 1; i <= blocks; i++) {
			if(space[i] != -1) return st + space[i];
			st += size[i];
		}
		return -1;
	}
	
	inline void calcSpace(int bindex) {
		space[bindex] = 1;
		int tab = head[bindex];
		while(true) {
			if(val[tab] == 0) return;
			if(tab == tail[bindex]) break;
			tab = r[tab], space[bindex]++;
		}
		space[bindex] = -1;
	}
	
	inline void set(int pos, int v) {
		/**
		set pos-th element's value as v
		O(sqrt(n))
		*/
		int x = at(pos), bindex = getBlockIndex(pos);
		val[x] = v;
		
		calcSpace(bindex);
	}
	
	inline void move(int pos, int value) {
		int x = at(pos), ypos = getFirstSpace(pos);
		int bix = getBlockIndex(pos), biy = getBlockIndex(ypos);
		int y = at(ypos);
		
		if(pos != ypos) {
			if(l[y]) r[l[y]] = r[y];
			if(r[y]) l[r[y]] = l[y];
			if(tail[biy] == y) tail[biy] = l[y];
			if(head[biy] == y) head[biy] = r[y];
			if(l[x]) r[l[x]] = y;
			l[y] = l[x];
			l[x] = y, r[y] = x;
			if(head[bix] == x) head[bix] = y;
			size[bix]++, size[biy]--;
			
			for(int i = bix + 1; i <= biy; i++) {
				if(val[tail[i - 1]] == 0) space[i] = 1;
				else if(space[i] != -1) space[i]++;
				if(space[i - 1] == size[i - 1]) space[i - 1] = -1;
				head[i] = tail[i - 1];
				tail[i - 1] = l[tail[i - 1]];
				size[i]++, size[i - 1]--;
			}
		}
		
		set(pos, value);
		calcSpace(bix), calcSpace(biy);
	}
	
	inline void getlist(int *ret, int &len) {
		len = 0;
		for(int i = 1; i <= blocks; i++) {
			int tab = head[i];
			while(true) {
				ret[++len] = val[tab];
				if(tab == tail[i]) break;
				tab = r[tab];
			}
		}
	}
} mylist;