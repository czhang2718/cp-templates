const int MAXN=500000;
ll fac[MAXN+5];

fac[0]=1;
for(ll i=1; i<=MAXN; i++) fac[i]=(fac[i-1]*i)%MOD;

// extended euclidean gcd
ll gcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) {
      x = 1;
      y = 0;
      return a;
  }
  ll x1, y1;
  ll d = gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

// inverse of a mod MOD
ll inv(ll a){
  ll x, y;
  gcd(a, (ll)MOD, x, y);
  return x = (x % MOD + MOD) % MOD;
}

ll choose(ll n, ll, k){
  if(k>n) return 0;
  return (((fac[n]*inv(fac[k]))%MOD)*inv([n-k]))%MOD;
}

