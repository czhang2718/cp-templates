// careful: OVERFLOW
int gcd(int a, int b, int &x, int &y){ // in the end, ax+by=gcd(a, b)
  if(b==0){
    x=1; y=0;
    return a;
  }
  int x1, y1;
  int g=gcd(b, a%b, x1, y1);
  x=y1;
  y=x1-y1*(a/b);
  return g;
}