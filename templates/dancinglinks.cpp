struct DLX {
	/**
	1.	node coordinate (1...r, 1...c)
	2.	the order of adding nodes should be 
		from up to down, from left to right
	*/
	static const int ROWS = 125 * 5 + 10., COLS = 125 + 10;
	static const int N = ROWS * COLS + ROWS + COLS;
	int rows, cols;
	int u[N], d[N], l[N], r[N], rowIndex[N], colIndex[N], nodes;
	int countCols[N];
	
	inline void init(int _rows, int _cols) {
		rows = _rows, cols = _cols;
		nodes = 0;
		for(int i = 0; i <= cols; i++) {
			int now = nodes++;
			u[now] = d[now] = now;
			l[now] = i == 0 ? cols : i - 1;
			r[now] = i == cols ? 0 : i + 1;
			rowIndex[now] = 0, colIndex[now] = i;
		}
		for(int i = 1; i <= rows; i++) {
			int now = nodes++;
			u[now] = i == 1 ? rows + cols : i - 1 + cols;
			d[now] = i == rows ? 1 + cols : i + 1 + cols;
			l[now] = r[now] = now;
			rowIndex[now] = i, colIndex[now] = 0;
		}
		for(int i = 0; i <= cols; i++) countCols[i] = 0;
	}
	
	inline void addNode(int x, int y) {
		int now = nodes++;
		u[now] = u[y], d[u[y]] = now;
		d[now] = y, u[y] = now;
		l[now] = l[cols + x], r[l[cols + x]] = now;
		r[now] = cols + x, l[cols + x] = now;
		countCols[y]++;
		rowIndex[now] = x, colIndex[now] = y;
	}
	
	inline void del(int x) {
		/**
		the current del node x will be delete first or
		never show as a real node and act as a virtual node
		*/
		if(!x) return;
		r[l[x]] = r[x], l[r[x]] = l[x];
		for(int row = d[x]; row != x; row = d[row])
			for(int col = r[row]; col != row; col = r[col]) {
				u[d[col]] = u[col], d[u[col]] = d[col];
				countCols[colIndex[col]]--;
			}
	}
	
	inline void resume(int x) {
		if(!x) return;
		for(int row = u[x]; row != x; row = u[row])
			for(int col = l[row]; col != row; col = l[col]) {
				u[d[col]] = col, d[u[col]] = col;
				countCols[colIndex[col]]++;
			}
		r[l[x]] = l[r[x]] = x;
	}
	
	inline void dance(bool *ans, int *size, int used, int remain) {
		/**
		change here
		*/
		ans[used + remain] = true;
		
		int p = 0, maxx = -INF;
		for(int tab = r[0]; tab != 0; tab = r[tab])
			if(countCols[tab] > maxx)
				maxx = countCols[p = tab];
		
		if(!p) return;
		del(p);
		for(int row = d[p]; row != p; row = d[row]) {
			for(int col = r[row]; col != row; col = r[col])
				del(colIndex[col]);
			dance(ans, size, used + 1, remain - size[rowIndex[row]]);
			for(int col = l[row]; col != row; col = l[col])
				resume(colIndex[col]);
		}
		resume(p);
	}
} dlk;