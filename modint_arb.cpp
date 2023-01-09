typedef long long ll;
ll Mod;
cin >> Mod;

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
using mi = ModInt;
