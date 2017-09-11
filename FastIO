namespace FastIO {
    /**
     * Defaultly, can deal with negative number.
     * Only for reading integers, modify for specify problems.
     * Throws int exception if nothing to read.
     * */
    const int S = 2000000;
    char s[S], *h = s+S, *t = h;
    inline char getchr(void) {
        if(h == t) {
            if(t != s + S) return -1;
            t = s + fread(s, 1, S, stdin), h = s;
        }
        return *h++;
    }
    inline int getint(void) throw(int) {
        char c = ' ';
        bool positive = true;
        for (; !isdigit(c); c = getchr()) {
            if(c == -1) throw(-1);
            positive ^= (c == '-');
        }
        int x = 0;
        for (; isdigit(c); c = getchr()) x = x * 10 + c - '0';
        return positive ? x : -x;
    }
}
using FastIO::getint;
