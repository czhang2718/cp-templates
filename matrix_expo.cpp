// Matrix Exponentiation
// - for nxn matrices only
// - requires ModInt
vector<vector<mint>> mult(vector<vector<mint>> a, vector<vector<mint>> b, int n){ 
  vector<vector<mint>> ans(n, vector<mint>(n));
  rep(i, 0, n-1){
    rep(j, 0, n-1){
      rep(k, 0, n-1){
        ans[i][j]+=a[i][k]*b[k][j];
      }
    }
  }
  return ans;
}

vector<vector<mint>> exp(vector<vector<mint>> v, int k, int n){ 
  vector<vector<mint>> bpow(n, vector<mint>(n));
  vector<vector<mint>> ans(n, vector<mint>(n));
  rep(i, 0, n-1) ans[i][i]=1; 
  rep(i, 0, 30){ //max log_2(k)
    if((1<<i)>k) break;
    if(k&(1<<i)) ans=mult(v, ans, n);
    v=mult(v, v, n);
  }
  return ans;
}