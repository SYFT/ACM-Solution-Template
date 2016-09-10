/**
Create By yzx - stupidboy
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <ctime>
#include <iomanip>
using namespace std;
typedef long long LL;
typedef double DB;
#define MIT (2147483647)
#define INF (1000000001)
#define MLL (1000000000000000001LL)
#define sz(x) ((int) (x).size())
#define clr(x, y) memset(x, y, sizeof(x))
#define puf push_front
#define pub push_back
#define pof pop_front
#define pob pop_back
#define mk make_pair

inline int Getint()
{
	int Ret = 0;
	char Ch = ' ';
	bool Flag = 0;
	while(!(Ch >= '0' && Ch <= '9'))
	{
		if(Ch == '-') Flag ^= 1;
		Ch = getchar();
	}
	while(Ch >= '0' && Ch <= '9')
	{
		Ret = Ret * 10 + Ch - '0';
		Ch = getchar();
	}
	return Flag ? -Ret : Ret;
}

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

int main()
{
	freopen("a.in", "r", stdin);
	/*string _str1, _str2;
	string str1, str2;
	cin >> _str1 >> _str2;
	bool neg1 = false, neg2 = false;
	if(_str1[0] == '-') str1 = _str1.substr(1, _str1.length() - 1), neg1 = true;
	else str1 = _str1;
	if(_str2[0] == '-') str2 = _str2.substr(1, _str2.length() - 1), neg2 = true;
	else str2 = _str2;
	BigNum a(str1);
	BigNum b(str2);
	BigNum c;
	if(neg1 == false && neg2 == false) c = a + b;
	else if(neg1 == false) {
	    if(b > a) printf("-"), c = b - a;
	    else c = a - b;
	} else if(neg2 == false) {
	    if(a > b) printf("-"), c = a - b;
	    else c = b - a;
	} else printf("-"), c = a + b;
	c.Out();*/
	string str;
	BigNum a = 0; 
	while(cin >> str) {
		BigNum b(str);
		a = a + b; 
		//if(str == "0") break;
	}	   
	a.Out();
	return 0;
}

