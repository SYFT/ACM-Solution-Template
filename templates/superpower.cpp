inline int superPower(int k, int p) {
	/**
	 * 1. k^X mod p = k^(X mod phi(p) + phi(p)) mod p  X = k^k^k.....
	 * 2. fastpow(x, y, z) x^y mod z
	 * */
	if(p == 1) return 0;
	int powers = superPower(k, phi[p]) + phi[p];
	return fastpow(k, powers, p);
}

