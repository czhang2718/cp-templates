long long bpow(long long a, long long b, long long mod){
  if(b==0) return 1;
  __int128 x=bpow(a, b/2, mod);
  x=(x*x)%mod;
  if(b&1) x=(x*a)%mod;
  return ll(x);
}

// miller rabin 
// test if ll is prime
// for int, prefer sqrt or testing precomputed primes
// O(log n) 
bool isPrime(long long n){
  if(n==1) return 0;
  if(n==2) return 1;
  if(!(n&1)) return 0;
  for(ll a:{2, 7, 61, 325, 9375, 28178, 450775, 9780504, 1795265022}){
    // ll a=uniform_int_distribution<ll>(1, x-1)(rng);
    if(n<=a) break;
    ll q=n-1;
    if(bpow(a, q, n)!=1) return 0;
    while(!(q&1)){
      q>>=1;
      ll k=bpow(a, q, n);
      if(k!=1 && k!=n-1) return 0;
      if(k==n-1) break;
    }
  }
  return 1;
}



// https://crypto.stanford.edu/pbc/notes/numbertheory/millerrabin.html