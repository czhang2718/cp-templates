const ll mod = 998244353;

ll power(ll a, ll b){
    ll ans = 1;
    while(b > 0) {
        if(b % 2 == 1) {
            ans = ans * a % mod;
        }
        a = a * a;
        a %= mod;
        b /= 2;
    }
    return ans;
}

void fft(vector<ll> & a, bool invert) {
    ll n = a.size();
    ll root = power(3, (mod - 1) / n);
    ll inv = power(root, mod - 2);
    for (ll i = 1, j = 0; i < n; i++) {
        ll b = n >> 1;
        for (; j & b; b >>= 1)
            j ^= b;
        j ^= b;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        ll wlen = invert ? inv : root;
        for (ll i = len; i < n; i <<= 1)
            wlen = wlen * wlen % mod;

        for (ll i = 0; i < n; i += len) {
            ll w = 1;
            for (ll j = 0; j < len / 2; j++) {
                ll u = a[i+j], v = a[i+j+len/2] * w % mod;
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = w * wlen % mod;
            }
        }
    }

    if (invert) {
        ll n_1 = power(n, mod - 2);
        for (ll & x : a) {
            x = x * n_1 % mod;
        }
    }
}

vector<ll> multiply(vector<ll> a, vector<ll> b) {
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < (ll) a.size() + (ll) b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (ll i = 0; i < n; i++)
        fa[i] = fa[i] * fb[i] % mod;
    fft(fa, true);
    return fa;
}