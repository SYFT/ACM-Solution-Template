class BigNum
{
	/*
	you can use BigNum(x) + BigNum(y) to calculate.
	This code doesn't use referrence when working.
	*/
	static const int MAXLENGTH = 10010, M = 100;
	// M -> MOD
public :
	int arr[MAXLENGTH], length;
	// the maximum value -> M * M * MAXLENGTH * MAXLENGTH when calculate *
	
	BigNum()
	{
		length = 0;
		clr(arr, 0);
	}
	
	BigNum(string &str) {
		length = 0, clr(arr, 0);
		int x = 0, now = 1, len = sz(str);
		for(int i = len - 1; i >= 0; i--) {
			x = x + (str[i] - '0') * now;
			now *= 10;
			if(now >= M) {
				arr[++length] = x;
				x = 0, now = 1;
			}
		}
		if(x) arr[++length] = x;
		length = max(length, 1);
	}
	
	inline void operator =(int x)
	{
		length = 0, clr(arr, 0);
		while(x)
		{
			arr[++length] = x % M;
			x /= M;
		}
		if(!length) length++;
	}
	
	BigNum(int x)
	{
		*this = x;
	}
	
	inline BigNum operator -(const BigNum& a)
	{
		BigNum ret;
		for(int i = 1; i <= length; i++) ret.arr[i] = arr[i] - a.arr[i];
		for(int i = 1; i <= length; i++)
			if(ret.arr[i] < 0)
			{
				ret.arr[i + 1]--;
				ret.arr[i] += M;
			}
		ret.length = max(length, a.length);
		while(length > 1 && !ret.arr[ret.length]) ret.length--;
		return ret;
	}
	
	inline BigNum operator +(const BigNum& a)
	{
		BigNum ret;
		ret.length = max(length, a.length);
		for(int i = 1; i <= ret.length; i++) ret.arr[i] = arr[i] + a.arr[i];
		for(int i = 1; i <= ret.length; i++)
			if(ret.arr[i] >= M)
			{
				ret.arr[i + 1]++;
				ret.arr[i] -= M;
			}
		while(ret.arr[ret.length + 1]) ret.length++;
		return ret;
	}
	
	inline BigNum operator *(const BigNum& a)
	{
		BigNum ret;
		for(int i = 1; i <= length; i++)
			for(int j = 1; j <= a.length; j++)
				ret.arr[i + j - 1] += arr[i] * a.arr[j];
		ret.length = length + a.length - 1;
		for(int i = 1; i <= ret.length; i++)
		{
			ret.arr[i + 1] += ret.arr[i] / M;
			ret.arr[i] %= M;
		}
		while(ret.arr[ret.length + 1])
		{
			ret.length++;
			ret.arr[ret.length + 1] += ret.arr[ret.length] / M;
			ret.arr[ret.length] %= M;
		}
		return ret;
	}
	
	inline BigNum operator /(int x)
	{
		BigNum ret = *this;
		for(int i = ret.length; i >= 1; i--)
		{
			if(i > 1) ret.arr[i - 1] += (ret.arr[i] % x) * M;
			ret.arr[i] /= x;
		}
		while(ret.length > 1 && !ret.arr[ret.length])
			ret.length--;
		return ret;
	}
	
	inline bool operator >(BigNum &a)
	{
		if(length != a.length) return length > a.length;
		for(int i = length; i >= 1; i--)
			if(arr[i] != a.arr[i]) return arr[i] > a.arr[i];
		return false;
	}
	
	inline void Out()
	{
		printf("%d", (int) arr[length]);
		for(int i = length - 1; i >= 1; i--)
			printf("%02d", (int) arr[i]);
		printf("\n");
	}
} ;
