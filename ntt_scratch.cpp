#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

template <ll Mod>
struct ModInt {
  ll n;

  ModInt(const ll x = 0) : n(x) {
    while (n < 0) n += Mod;
    n %= Mod;
  }
  explicit operator int() const { return n; }
  inline ModInt operator+(const ModInt r) const noexcept { return ModInt(*this) += r; }
  inline ModInt operator-(const ModInt r) const noexcept { return ModInt(*this) -= r; }
  inline ModInt operator*(const ModInt r) const noexcept { return ModInt(*this) *= r; }
  inline ModInt operator/(const ModInt r) const noexcept { return ModInt(*this) /= r; }
  inline ModInt &operator+=(const ModInt r) noexcept {
    n += r.n;
    if (n >= Mod) n -= Mod;
    return *this;
  }
  inline ModInt &operator-=(const ModInt r) noexcept {
    if (n < r.n) n += Mod;
    n -= r.n;
    return *this;
  }
  inline ModInt &operator*=(const ModInt r) noexcept {
    n = n * r.n % Mod;
    return *this;
  }
  inline ModInt &operator/=(const ModInt r) noexcept { return *this *= r.inv(); }

  inline ModInt pow(ll x) const noexcept {
    ModInt<Mod> ret(1), tmp(*this);
    while (x) {
      if (x&1) ret *= tmp;
      tmp *= tmp;
      x >>= 1;
    }
    return ret;
  }
  inline ModInt inv() const noexcept { return pow(Mod-2); }

  friend ostream& operator<<(ostream& os, const ModInt& obj) { return os << obj.n; }
  friend istream& operator>>(istream& is, ModInt& obj) {
    ll t;
    is >> t;
    obj = ModInt(t);
    return is;
  }
};
const ll mod = (119<<23)+1; //check!
using mi = ModInt<mod>;
mi operator"" _mi(unsigned long long n) { return mi(n); }

const int N=1<<20;
int n,m;
mi w=3;
mi a[N], b[N], c[N], temp[N];
mi root[N];
mi inv[21];

void dft(mi *y, mi *A, int n, int skip, bool invert){
	// evaluates A at 2^n th roots of unity: y
	if(n==0){
		y[0]=A[0];
		return;
	}
	dft(y, A, n-1, skip*2, 0);
	dft(y+skip, A+skip, n-1, skip*2, 0);
	for(int i=0; i<(1<<(n-1)); i++){
		mi a=y[2*i*skip], b=root[i*skip]*y[2*i*skip+skip];
		temp[i]=(a+b)*(invert?inv[n]:1);
		temp[i+(1<<(n-1))]=(a-b)*(invert?inv[n]:1);
	}
	for(int i=0; i<(1<<n); i++){
		y[i*skip]=temp[i];
	}
}

void ntt(int n){
	inv[n]=mi(1)/(1<<n);
	for(int i=n-1; i>=0; i--) inv[i]=inv[i+1]*2;
	mi r=w.pow(int(mi(-1)/(1<<n)));
	root[0]=1;
	for(int i=1; i<(1<<n); i++) root[i]=root[i-1]*r;
	mi ya[1<<n], yb[1<<n];
	dft(ya, a, n, 1, 0);
	dft(yb, b, n, 1, 0);
	mi y[1<<n];
	for(int i=0; i<(1<<n); i++) y[i]=ya[i]*yb[i];
	r=mi(1)/r;
	for(int i=1; i<(1<<n); i++) root[i]=root[i-1]*r;
	dft(c, y, n, 1, 1);
}

int main(){
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> m;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<m; i++) cin >> b[i];

	int k=0;
	while((1<<k)<n+m) k++;
		
	ntt(k);

	for(int i=0; i<n+m-1; i++){
		cout << c[i] << " ";
	}
}
// https://judge.yosupo.jp/problem/convolution_mod (945 ms)