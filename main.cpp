#include "bits/stdc++.h"
using namespace std;
 
#define rep(i, a, b) for(int i=a; i<=b; i++)
#define trav(a, x) for(auto& a:x)
#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define f first
#define s second
#define nl "\n"
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int MOD=1e9+7;
template<class T> using pqg=priority_queue<T, vector<T>, greater<T>>;

template <ll Mod>
struct ModInt {
  ll n;

  ModInt(ll x = 0) : n(x) {
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

constexpr ll mod = 1000000007; //check!
using mint = ModInt<mod>;
mint operator"" _mi(unsigned long long n) { return mint(n); }

int n, m;
ll dp[2000001]; //??

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("input.txt", "r", stdin); 
  // freopen("output.txt", "w", stdout);

  cin >> n >> m;
  ll hold=0;
  dp[n]=1;
  for(int i=n; i>=1; i--){
    int cur=0;
    cout << "old " << dp[i] << nl;
    dp[i]+=hold;
    dp[i]%=m;
    cout << "dp[" << i << "] " << dp[i] << nl;
    hold+=dp[i]; hold%=m;
    for(int j=1; j*j<=i; j++){
      if(i/j!=cur && i/j!=i){
        // cout << "dp[" << i/j << "] += " << dp[i] << nl;
        dp[i/j]+=dp[i];
        dp[i/j]%=m;
        cur=i/j;
      }
      if(i/j==j) break;
      // is j acheivable as i/k?
      int l =i/(j+1);
      int r=i/j;
      if(r>l){
        // cout << "dp[" << j << "] += " << dp[i] << nl;
        dp[j]+=ll(r-l)*dp[i], dp[j]%=m;
      }
    }
  }
  cout << dp[1];
}