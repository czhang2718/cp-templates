template <ll Mod>
struct ModInt {
  ll n;

  ModInt(const ll x = 0) : n(x) {
    while (n < 0) n += Mod;
    n %= Mod;
  }
  explicit operator int() const { return n; }
  inline constexpr ModInt operator+(const ModInt r) const noexcept { return ModInt(*this) += r; }
  inline constexpr ModInt operator-(const ModInt r) const noexcept { return ModInt(*this) -= r; }
  inline constexpr ModInt operator*(const ModInt r) const noexcept { return ModInt(*this) *= r; }
  inline constexpr ModInt operator/(const ModInt r) const noexcept { return ModInt(*this) /= r; }
  inline constexpr ModInt &operator+=(const ModInt r) noexcept {
    n += r.n;
    if (n >= Mod) n -= Mod;
    return *this;
  }
  inline constexpr ModInt &operator-=(const ModInt r) noexcept {
    if (n < r.n) n += Mod;
    n -= r.n;
    return *this;
  }
  inline constexpr ModInt &operator*=(const ModInt r) noexcept {
    n = n * r.n % Mod;
    return *this;
  }
  inline constexpr ModInt &operator/=(const ModInt r) noexcept { return *this *= r.inv(); }

  inline constexpr ModInt pow(ll x) const noexcept {
    ModInt<Mod> ret(1), tmp(*this);
    while (x) {
      if (x&1) ret *= tmp;
      tmp *= tmp;
      x >>= 1;
    }
    return ret;
  }
  inline constexpr ModInt inv() const noexcept { return pow(Mod-2); }

  friend ostream& operator<<(ostream& os, const ModInt& obj) { return os << obj.n; }
  friend istream& operator>>(istream& is, ModInt& obj) {
    ll t;
    is >> t;
    obj = ModInt(t);
    return is;
  }
};

constexpr ll mod = 998244353; 
using mi = ModInt<mod>;
mi operator"" _mi(unsigned long long n) { return mi(n); }

mi power(mi a, int b){
    mi ans = 1;
    while(b > 0) {
        if(b % 2 == 1) {
            ans = ans * a;
        }
        a = a * a;
        b /= 2;
    }
    return ans;
}

void fft(vector<mi> & a, bool invert) {
    ll n = a.size();
    mi root = power(3, (mod - 1) / n);
    mi inv = power(root, mod - 2);
    for (ll i = 1, j = 0; i < n; i++) {
        ll b = n >> 1;
        for (; j & b; b >>= 1)
            j ^= b;
        j ^= b;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        mi wlen = invert ? inv : root;
        for (ll i = len; i < n; i <<= 1)
            wlen = wlen * wlen;

        for (ll i = 0; i < n; i += len) {
            mi w = 1;
            for (ll j = 0; j < len / 2; j++) {
                mi u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w = w * wlen;
            }
        }
    }

    if (invert) {
        mi n_1 = power(n, mod - 2);
        for (mi & x : a) {
            x = x * n_1;
        }
    }
}

vector<mi> multiply(vector<mi> a, vector<mi> b) {
    vector<mi> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < (ll) a.size() + (ll) b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (ll i = 0; i < n; i++)
        fa[i] = fa[i] * fb[i];
    fft(fa, true);
    return fa;
}