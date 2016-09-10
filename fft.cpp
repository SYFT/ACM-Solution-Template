class Complex {
	public :
		double real, image;

		Complex(double real = 0., double image = 0.):real(real), image(image) {}
		Complex(const Complex &t):real(t.real), image(t.image) {}

		Complex operator +(const Complex &t) const {
			return Complex(real + t.real, image + t.image);
		}

		Complex operator -(const Complex &t) const {
			return Complex(real - t.real, image - t.image);
		}

		Complex operator *(const Complex &t) const {
			return Complex(real * t.real - image * t.image, 
						real * t.image + t.real * image);
		}
};

const int N = 300010, MOD = 313;
const double PI = acos(-1.);

class FFT {
	/**
	 * 1. Need define PI
	 * 2. Need define class Complex
	 * 3. tmp is need for fft, so define a N suffice it
	 * 4. dig[30] -> (1 << 30) must bigger than N
	 * */
	private :
		static Complex tmp[N];
		static int revNum[N], dig[30];

	public :
		static void init(int n) {
			int len = 0;
			for(int t = n - 1; t; t >>= 1) ++len;
			for(int i = 0; i < n; i++) {
				revNum[i] = 0;
				for(int j = 0; j < len; j++) dig[j] = 0;
				for(int idx = 0, t = i; t; t >>= 1) dig[idx++] = t & 1;
				for(int j = 0; j < len; j++)
					revNum[i] = (revNum[i] << 1) | dig[j];
			}
		}

		static int rev(int x) {
			return revNum[x];
		}

		static void fft(Complex a[], int n, int flag) {
			/**
			 * flag = 1 -> DFT
			 * flag = -1 -> IDFT
			 * */
			for(int i = 0; i < n; ++i) tmp[i] = a[rev(i)];
			for(int i = 0; i < n; ++i) a[i] = tmp[i];
			for(int i = 2; i <= n; i <<= 1) {
				Complex wn(cos(2 * PI / i), flag * sin(2 * PI / i));
			   for(int k = 0, half = i / 2; k < n; k += i) {
				   Complex w(1., 0.);
				   for(int j = k; j < k + half; ++j) {
					   Complex x = a[j], y = w * a[j + half];
					   a[j] = x + y, a[j + half] = x - y;
					   w = w * wn;
				   }
			   }
			}
			if(flag == -1) {
				for(int i = 0; i < n; ++i) a[i].real /= n;
			}
		}

		static void dft(Complex a[], int n) {
			fft(a, n, 1);
		}

		static void idft(Complex a[], int n) {
			fft(a, n, -1);
		}
};
Complex FFT::tmp[N];
int FFT::revNum[N], FFT::dig[30];

