// Updated 9/5/2021
// Verified on codeforces.com/contest/1567/problem/E

struct segtree{
  int n, no_op;
  vector<ll> sum;
  vector<ll> op;

  segtree(int n){
    this->n=n;
    no_op=-1; // *CHECK*
    sum.resize(4*n);
    op.resize(4*n, no_op);
  }

  void push(int x, int lx, int rx){
    if(rx-lx==1 || op[x]==no_op) return;
    op[2*x+1]=op[2*x+2]=op[x];
    int m=(lx+rx)/2;
    sum[2*x+1]=op[x]*(m-lx);
    sum[2*x+2]=op[x]*(rx-m);
    op[x]=no_op;
  }

  void assign(int l, int r, ll v, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r){
      op[x]=v;
      sum[x]=v*(rx-lx);
      push(x, lx, rx); return;
    }
    if(lx>=r || rx<=l) return;
    int m=(lx+rx)/2;
    assign(l, r, v, 2*x+1, lx, m);
    assign(l, r, v, 2*x+2, m, rx);
    sum[x]=sum[2*x+1]+sum[2*x+2];
  }

  void assign(int l, int r, int v){ // [l, r)
  	if(r<=l) return;
    assign(l, r, v, 0, 0, n+1);
  }

  void assign(int i, int v){
    assign(i, i+1, v);
  }

  ll get_sum(int l, int r, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r) return sum[x];
    if(lx>=r || rx<=l) return 0;
    int m=(lx+rx)/2;
    return get_sum(l, r, 2*x+1, lx, m)+get_sum(l, r, 2*x+2, m, rx);
  }

  ll get_sum(int l, int r){
  	if(r<=l) return 0;
    return get_sum(l, r, 0, 0, n+1);
  }

  ll get(int i){
    return get_sum(i, i+1);
  }
};
