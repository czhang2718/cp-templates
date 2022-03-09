// finds factor of n != 1, n
// O(n^{1/4})
// good for N=pq
// if not, see stolen_factorize.cpp
long long pollardRho(long long n){
  int c;
  auto f=[&](long long x)->long long{
    return ((__int128)x*x+c)%n;
  };
  auto rho=[&]()->long long{
    long long x=2, y=2, g=1;
    int i=1, k=2;
    while(g==1){
      x=f(x);
      y=f(f(y)); 
      g=__gcd(abs(x-y), n);
      if(++i==k) k<<=1, x=y; // jump by powers of 2, faster for some reason
    }
    return g;
  };
  long long d=n;
  for(c=1; d==n; c++){ // while cycle finds n (bad)
    d=rho();
  }
  return d;
}