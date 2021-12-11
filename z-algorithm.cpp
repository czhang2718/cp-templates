// 11/11/2021
// computes z function z[0], ..., z[n-1]
// z[i] := largest shared prefix
// find all occurances of t in s with zf(t+s)
// O(n)
// alg: 2 points l, r for rightmost [l, r] which == prefix
vector<int> zf(string str){
  int n=str.size();
  vector<int> z(n);
  int l=-1; int r=-1;
  for(int i=1; i<n; i++){
    if(r<i) l=r=-1;
    if(l==-1){
      if(str[i]==str[0]){
        l=r=i;
        while(r+1<n && str[r+1]==str[r+1-i]) r++;
        z[i]=r-l+1;
      }
      continue;
    }
    int k=i-l;
    if(z[k]<r-i+1) z[i]=z[k];
    else{
      while(r+1<n && str[r+1]==str[r+1-i]) r++;
      l=i;
      z[i]=r-i+1;
    }
  }
  return z;
}